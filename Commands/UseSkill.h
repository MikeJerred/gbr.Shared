#pragma once

#include <GWCA/Constants/Skills.h>
#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class UseSkill : public BaseCommand {
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::UseSkill) {}
                    Request(const char* s);

                    GW::Constants::SkillID skillId;
                    DWORD targetId;
                    bool ping;
                };

                static void Execute(Request* request);
            };
        }
    }
}