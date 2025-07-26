#pragma once
#include <memory>

#include "IKmboxDriver.h"

namespace kmbox {
    class Factory {
    public:
        static std::shared_ptr<IKmboxDriver> Create(const char* ip, const char* port, const char* uuid);

        static std::shared_ptr<IKmboxDriver> Create(int comPort);
    };
}
