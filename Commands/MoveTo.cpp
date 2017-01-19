#include <json/json.hpp>
#include <GWCA/Utilities/Maybe.h>

#include "AggressiveMoveTo.h"
#include "MoveTo.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            using json = nlohmann::json;

            GW::Maybe<GW::GamePos> MoveTo::currentPos = GW::Maybe<GW::GamePos>::Nothing();

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
                AggressiveMoveTo::SetSpiritPos(GW::Maybe<GW::GamePos>::Nothing());
                AggressiveMoveTo::SetTargetAgentId(0);
                SetPos(pos);

                GW::Gamethread().Enqueue([=]() {
                    GW::Agents().Move(pos);
                });
            }

            GW::Maybe<GW::GamePos> MoveTo::GetPos() {
                return currentPos;
            }

            void MoveTo::SetPos(GW::Maybe<GW::GamePos> pos) {
                currentPos = pos;
            }
        }
    }
}