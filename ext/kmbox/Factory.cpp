#include "Factory.h"

#include <memory>

#include "impl/KmboxBproDriver.h"
#include "impl/KmboxNetDriver.h"


namespace kmbox {

    std::unique_ptr<IKmboxDriver> Factory::CreateNetDriver(const char* ip, const char* port, const char* uuid) {
        return std::make_unique<KmboxNetDriver>(ip, port, uuid);
    }

    std::unique_ptr<IKmboxDriver> Factory::CreateBProDriver(int comPort) {
        return std::make_unique<KmboxBProDriver>(comPort);
    }
}
