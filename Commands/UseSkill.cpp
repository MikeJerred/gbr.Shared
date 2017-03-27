#include <json/json.hpp>
#include <GWCA/Managers/GameThreadMgr.h>
#include <GWCA/Managers/SkillbarMgr.h>

#include "UseSkill.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            using json = nlohmann::json;

            UseSkill::Request::Request(const char* s) : Request() {
                auto obj = json::parse(s);
                auto skillId = obj["skillId"];
                auto targetId = obj["targetId"];
                auto ping = obj["ping"];

                if (!skillId.is_number_unsigned()
                    || (!targetId.is_number_unsigned() && !targetId.is_null())
                    || !ping.is_boolean()) {

                    throw new std::invalid_argument(std::string("Invalid UseSkill command: { ")
                        + "skillId: " + skillId.get<std::string>()
                        + ", targetId: " + targetId.get<std::string>()
                        + ", ping: " + ping.get<std::string>()
                        + " }");
                }

                this->skillId = static_cast<GW::Constants::SkillID>(skillId.get<DWORD>());
                this->targetId = targetId.get<DWORD>();
                this->ping = ping.get<bool>();
            }

            void UseSkill::Execute(Request* request) {
                GW::GameThread::Enqueue([=]() {
                    GW::SkillbarMgr::UseSkillByID(static_cast<DWORD>(request->skillId), request->targetId, request->ping);
                });
            }
        }
    }
}