#pragma once

#include "pe/Client/Client.h"
#include "pe/Client/ServerScene.h"
#include <cstdio>

namespace pe {

class MPClient : public Client {
public:
    constexpr static const char* const sServerIp = "192.168.188.89";

    MPClient()
        : Client(sPackets)
    {
    }

    static MPClient& instance();

    void log(const char* msg);

    template <typename... Args>
    void log(const char* fmt, Args... args)
    {
        size_t size = snprintf(nullptr, 0, fmt, args...);
        char data[size + 1];
        snprintf(data, size, fmt, args...);
        log((const char*)data);
    }

    pe::ServerScene mServerScene;

    void receivePlayerUpdate(u8* data, size_t size);
    void receivePlayerAnimStart(u8* data, size_t size);
    void receivePlayerDisasterTimerUpdate(u8* data, size_t size);
    void receivePlayerConnectionStatus(u8* data, size_t size);
    void receivePlayerGenericPuppetUpdate(u8* data, size_t size);
    void receivePlayerGenericPuppetAnimStart(u8* data, size_t size);

    void tryAddPlayer(u64 id);

private:
    constexpr static Client::receivePacket sPackets[] = {
        &Client::receiveInit,
        &Client::receivePing,
        (Client::receivePacket)&MPClient::receivePlayerUpdate,
        (Client::receivePacket)&MPClient::receivePlayerAnimStart,
        (Client::receivePacket)&MPClient::receivePlayerDisasterTimerUpdate,
        (Client::receivePacket)&MPClient::receivePlayerConnectionStatus,
        (Client::receivePacket)&MPClient::receivePlayerGenericPuppetUpdate,
        (Client::receivePacket)&MPClient::receivePlayerGenericPuppetAnimStart
    };
};

} // namespace fl