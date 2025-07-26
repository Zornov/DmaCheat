#include "Factory.h"

#include <memory>

#include "impl/KmboxBProDriver.h"
#include "impl/KmboxNetDriver.h"


namespace kmbox {

    std::shared_ptr<IKmboxDriver> Factory::Create(const char* ip, const char* port, const char* uuid) {
        return std::make_shared<KmboxNetDriver>(ip, port, uuid);
    }

    std::shared_ptr<IKmboxDriver> Factory::Create(int comPort) {
        return std::make_shared<KmboxBProDriver>(comPort);
    }
}
