#include "pe/client/OutPacket.h"
#include <nn/os.h>
#include <nn/socket.h>

namespace pe {

class Client {
    constexpr static size_t sThreadStackSize = 0x15000;
    constexpr static size_t sPacketBufferSize = 0x10000;
    constexpr static int sTimeoutSeconds = 30;
    constexpr static int sPingIntervalSeconds = 10;

    sockaddr_in mServerAddress;
    sockaddr mClientAddress;
    s32 mSocket = -1;

    nn::os::ThreadType mRecvThread { 0 };
    void* mRecvThreadStack = nullptr;
    bool mInited = false;
    bool mConnected = false;
    u64 mLastPingReceived = -1;
    u64 mLastPingSent = -1;

protected:
    typedef void (Client::*receivePacket)(u8* data, size_t len);

    struct ReceivePacketList {
        const Client::receivePacket* packets = nullptr;
        u8 amount = 0;

        template <u8 N>
        constexpr ReceivePacketList(const Client::receivePacket (&packets)[N])
        {
            this->packets = packets;
            amount = N;
        }
    };
    ReceivePacketList mPackets;

public:
    Client(const ReceivePacketList& packets);
    virtual ~Client();

    void connect(const char* address, u16 port);
    void reconnect(const char* address, u16 port);
    void reconnect();
    void ping();

    void sendPacket(OutPacket&);
    void handlePacket(u8* data, size_t size);

    virtual void receiveInit(u8* data, size_t size);
    void receivePing(u8* data, size_t size);

    friend void
    threadFunc(void*);
    friend void pingThreadFunc(void*);

    inline bool isTimedOut()
    {
        nn::time::PosixTime now;
        nn::time::StandardUserSystemClock::GetCurrentTime(&now);
        return now.time - mLastPingReceived > sTimeoutSeconds;
    }

    inline bool isConnected() { return mInited && mConnected && !isTimedOut(); }
};

} // namespace pe
