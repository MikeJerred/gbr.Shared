#include <json/json.hpp>

#include "MoveTo.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            using json = nlohmann::json;

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

                GW::Gamethread().Enqueue([=]() {
                    GW::Agents().Move(pos);

                    auto agents = GW::Agents().GetAgentArray();
                    const auto adjacentSq = GW::Constants::Range::Adjacent * GW::Constants::Range::Adjacent;
                    for (auto agent : agents) {
                        if (agent && agent->GetIsSignpostType() && agent->pos.SquaredDistanceTo(pos) < adjacentSq) {
                            GW::Agents().GoSignpost(agent);
                            return;
                        }
                    }
                });
            }
        }
    }
}