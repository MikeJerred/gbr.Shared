#pragma once

#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class ToggleRender : public BaseCommand {
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::ToggleRender) {}
                };

                static void Execute(Request* request);
            };
        }
    }
}