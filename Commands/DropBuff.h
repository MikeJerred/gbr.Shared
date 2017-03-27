#pragma once

#include <GWCA/Constants/Skills.h>
#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class DropBuff : public BaseCommand {
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::DropBuff) {}
                    Request(const char* s);

                    GW::Constants::SkillID skillId;
                };

                static void Execute(Request* request);
            };
        }
    }
}