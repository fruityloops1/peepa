#include "pe/Client/Client.h"
#include "lib.hpp"
#include "nn/account.h"
#include "nn/nifm.h"
#include "nn/os.h"
#include "nn/socket.h"
#include "nn/time.h"

namespace pe {

namespace {
    class Ping : public OutPacket {

    public:
        Ping()
            : OutPacket(1)
        {
        }
    };
}

void Client::ping()
{
    Ping packet;
    sendPacket(packet);
}

void threadFunc(void* c)
{
    Client* client = (Client*)c;
    const nn::TimeSpan wait = nn::TimeSpan::FromNanoSeconds(16000000);
    u8 buf[Client::sPacketBufferSize] { 0 };
    size_t len = 0;

    while (true) {
        len = nn::socket::Recv(client->mSocket, buf, Client::sPacketBufferSize, 0x80);

        client->handlePacket(buf, len);
        nn::os::YieldThread();
        nn::os::SleepThread(wait);
    }
}

Client::Client(const ReceivePacketList& packets)
    : mPackets(packets)
{
    memset(&mClientAddress, 0, sizeof(mClientAddress));
    memset(&mServerAddress, 0, sizeof(mServerAddress));

    mRecvThreadStack = aligned_alloc(0x1000, sThreadStackSize);
}

Client::~Client()
{
    nn::os::SuspendThread(&mRecvThread);
    nn::os::DestroyThread(&mRecvThread);
    free(mRecvThreadStack);
}

namespace {
    class Init : public OutPacket {
        struct {
            nn::account::Uid userId;
            nn::account::Nickname nickname;
            bool isDisconnect;
        } mData;

    public:
        Init(const nn::account::Uid& id, bool disconnect)
            : OutPacket(0)
            , mData { id }
        {
            nn::account::GetNickname(&mData.nickname, mData.userId);
            mData.isDisconnect = disconnect;
        }
        size_t calcSize() { return sizeof(mData); }
        void construct(u8* data) { *(typeof(mData)*)data = mData; }
    };
}

void Client::connect(const char* address, u16 port)
{
    nn::nifm::Initialize();
    nn::nifm::SubmitNetworkRequest();

    while (nn::nifm::IsNetworkRequestOnHold()) { }

    mSocket = nn::socket::Socket(2, 2, 0);
    R_ABORT_UNLESS(mSocket);

    int timeout = 100;
    nn::socket::SetSockOpt(mSocket, 0xffff, 0x1006, (const void*)&timeout, sizeof(timeout));

    mServerAddress.family = 2;
    mServerAddress.port = nn::socket::InetHtons(port);
    nn::socket::InetAton(address, (nn::socket::InAddr*)&mServerAddress.address);

    sockaddr_in client = { 0 };
    client.port = nn::socket::InetHtons(port - 1);
    client.family = 2;
    client.address.data = 0;
    if (R_FAILED(nn::socket::Bind(mSocket, &client, sizeof(client))))
        EXL_ABORT(nn::socket::GetLastErrno());
    nn::os::CreateThread(&mRecvThread, threadFunc, this, mRecvThreadStack, sThreadStackSize, 16, 0);
    nn::os::SetThreadName(&mRecvThread, "pe::Client RecvThread");
    nn::os::StartThread(&mRecvThread);
    mInited = true;

    reconnect();
}

void Client::reconnect()
{
    nn::account::Uid user;
    nn::account::GetLastOpenedUser(&user);
    if (!user.IsValid())
        EXL_ABORT(0x45);
    Init initPacket(user, false);
    sendPacket(initPacket);
}

void Client::reconnect(const char* address, u16 port)
{
    if (!mInited) {
        connect(address, port);
        return;
    }

    nn::os::SuspendThread(&mRecvThread);
    if (mSocket)
        nn::socket::Close(mSocket);

    mSocket = nn::socket::Socket(2, 2, 0);
    R_ABORT_UNLESS(mSocket);

    mServerAddress.family = 2;
    mServerAddress.port = nn::socket::InetHtons(port);
    nn::socket::InetAton(address, (nn::socket::InAddr*)&mServerAddress);

    sockaddr_in client = { 0 };
    client.port = nn::socket::InetHtons(port - 1);
    client.family = 2;
    if (R_FAILED(nn::socket::Bind(mSocket, (sockaddr*)&client, sizeof(client))))
        EXL_ABORT(nn::socket::GetLastErrno());

    nn::os::ResumeThread(&mRecvThread);
    reconnect();
}

void Client::disconnect()
{
    nn::account::Uid user;
    nn::account::GetLastOpenedUser(&user);
    if (!user.IsValid())
        EXL_ABORT(0x45);
    Init initPacket(user, true);
    sendPacket(initPacket);
    mConnected = false;
}

void Client::handlePacket(u8* data, size_t size)
{
    u8 type = data[0];
    if (type != 0 && !mConnected)
        return;

    if (type >= mPackets.amount)
        EXL_ABORT(0x42069, "invalid packet id received (%d)", type);
    (this->*mPackets.packets[type])(data + 1, size - 1);
}

void Client::sendPacket(OutPacket& packet)
{
    if (packet.mId != 0 && !mConnected)
        return;

    u32 size = packet.calcSize();
    u8 data[size + 1];

    data[0] = packet.mId;
    packet.construct(data + 1);
    nn::socket::SendTo(mSocket, data, size + 1, 0, (sockaddr*)&mServerAddress, sizeof(mServerAddress));
}

void Client::receiveInit(u8* data, size_t size)
{
    mConnected = true;
}

void Client::receivePing(u8* data, size_t size)
{
    nn::time::PosixTime now;
    nn::time::StandardUserSystemClock::GetCurrentTime(&now);
    mLastPingReceived = now.time;
}

bool Client::isTimedOut() const
{
    return false;

    nn::time::PosixTime now;
    nn::time::StandardUserSystemClock::GetCurrentTime(&now);
    return now.time - mLastPingReceived > sTimeoutSeconds;
}

} // namespace fl