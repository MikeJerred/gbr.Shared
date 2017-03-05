#include <algorithm>

#include "InteractAgent.h"
#include "MoveTo.h"
#include "PlaceSpirit.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            GW::Maybe<GW::GamePos> PlaceSpirit::spiritPos = GW::Nothing<GW::GamePos>();

            void PlaceSpirit::Execute(Request* request) {
                auto pos = GW::GamePos(request->x, request->y, request->zPlane);

                MoveTo::ClearPos();
                InteractAgent::ClearAgentId();
                SetSpiritPos(pos);
            }

            GW::Maybe<GW::GamePos> PlaceSpirit::GetSpiritPos() {
                return spiritPos;
            }

            void PlaceSpirit::SetSpiritPos(const GW::GamePos& pos) {
                spiritPos = pos;
            }

            void PlaceSpirit::ClearSpiritPos() {
                spiritPos = GW::Nothing<GW::GamePos>();
            }
        }
    }
}