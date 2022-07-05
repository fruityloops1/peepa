#pragma once

#include "pe/client/Client.h"

namespace pe {

class MPClient : public Client {
public:
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

private:
    constexpr static Client::receivePacket sPackets[] = {
        &Client::receiveInit,
        &Client::receivePing
    };
};

} // namespace fl