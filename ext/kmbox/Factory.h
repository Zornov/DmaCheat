#pragma once
#include <memory>

#include "IKmboxDriver.h"

namespace kmbox {
    class Factory {
    public:
        static std::unique_ptr<IKmboxDriver> CreateNetDriver(const char* ip, const char* port, const char* uuid);

        static std::unique_ptr<IKmboxDriver> CreateBProDriver(int comPort);
    };
}
