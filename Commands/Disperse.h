#pragma once

#include <GWCA/Utilities/Maybe.h>
#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class Disperse : BaseCommand {
            private:
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::Disperse) {}

                    float x;
                    float y;
                    DWORD zPlane;
                };

                static void Execute(Request* request);
            };
        }
    }
}