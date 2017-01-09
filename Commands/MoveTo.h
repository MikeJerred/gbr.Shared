#pragma once

#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class MoveTo : public BaseCommand {
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::MoveTo) {}
                    Request(const char* s);

                    float x;
                    float y;
                    DWORD zPlane;
                };

                static void Execute(Request* request);
            };
        }
    }
}