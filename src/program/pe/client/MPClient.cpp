#include "pe/client/MPClient.h"
#include <cstring>

namespace pe {

MPClient& MPClient::instance()
{
    static MPClient client;
    return client;
}

namespace {
    class Log : public OutPacket {

        const char* const mData = nullptr;

    public:
        Log(const char* data)
            : OutPacket(2)
            , mData(data)
        {
        }
        size_t calcSize() { return strlen(mData) + 1; }
        void construct(u8* out) { strcpy((char*)out, mData); }
    };
}

void MPClient::log(const char* msg)
{
    Log packet = Log(msg);
    sendPacket(packet);
}

} // namespace fl