#include <json/json.hpp>
#include <GWCA/Managers/EffectMgr.h>

#include "DropBuff.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            using json = nlohmann::json;

            DropBuff::Request::Request(const char* s) : Request() {
                auto obj = json::parse(s);
                auto skillId = obj["skillId"];

                if (!skillId.is_number_unsigned()) {
                    throw new std::invalid_argument(std::string("Invalid DropBuff command: { ")
                        + "skillId: " + skillId.get<std::string>()
                        + " }");
                }

                this->skillId = static_cast<GW::Constants::SkillID>(skillId.get<DWORD>());
            }

            void DropBuff::Execute(Request* request) {
                GW::Gamethread().Enqueue([=]() {
                    auto buff = GW::Effects().GetPlayerBuffBySkillId(request->skillId);
                    if (buff.BuffId != 0)
                        GW::Effects().DropBuff(buff.BuffId);
                });
            }
        }
    }
}