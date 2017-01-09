#pragma once

#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class Resign : public BaseCommand {
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::Resign) {}
                };

                static void Execute(Request* request);
            };
        }
    }
}