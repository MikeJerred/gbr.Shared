#include <json/json.hpp>
#include <GWCA/Managers/AgentMgr.h>
#include <GWCA/Managers/GameThreadMgr.h>
#include <GWCA/Utilities/Maybe.h>

#include "InteractAgent.h"
#include "MoveTo.h"
#include "PlaceSpirit.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            using json = nlohmann::json;

            GW::Maybe<GW::GamePos> MoveTo::currentPos = GW::Nothing<GW::GamePos>();

            MoveTo::Request::Request(const char* s) : Request() {
                auto obj = json::parse(s);
                auto x = obj["x"];
                auto y = obj["y"];
                auto zPlane = obj["zPlane"];

                if (!x.is_number() || !y.is_number() || (!zPlane.is_number_integer() && !zPlane.is_null())) {
                    throw new std::invalid_argument(std::string("Invalid MoveTo command: { ")
                        + "x: " + x.get<std::string>()
                        + ", y: " + y.get<std::string>()
                        + ", zPlane: " + zPlane.get<std::string>()
                        + " }");
                }

                this->x = x.get<float>();
                this->y = y.get<float>();
                this->zPlane = zPlane.is_null() ? 0 : zPlane.get<int>();
            }

            void MoveTo::Execute(Request* request) {
                auto pos = GW::GamePos(request->x, request->y, request->zPlane);
                InteractAgent::ClearAgentId();
                PlaceSpirit::ClearSpiritPos();
                SetPos(pos);

                GW::GameThread::Enqueue([=]() {
                    GW::Agents::Move(pos);
                });
            }

            GW::Maybe<GW::GamePos> MoveTo::GetPos() {
                return currentPos;
            }

            void MoveTo::SetPos(GW::GamePos pos) {
                currentPos = pos;
            }

            void MoveTo::ClearPos() {
                currentPos = GW::Nothing<GW::GamePos>();
            }
        }
    }
}