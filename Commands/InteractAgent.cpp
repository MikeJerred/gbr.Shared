#include <algorithm>

#include "InteractAgent.h"
#include "MoveTo.h"
#include "PlaceSpirit.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            GW::Maybe<DWORD> InteractAgent::agentId = GW::Nothing<DWORD>();

            void InteractAgent::Execute(Request* request) {
                auto agent = request->agentId;

                MoveTo::ClearPos();
                PlaceSpirit::ClearSpiritPos();
                SetAgentId(agent);
            }

            GW::Maybe<DWORD> InteractAgent::GetAgentId() {
                return agentId;
            }

            void InteractAgent::SetAgentId(DWORD agent) {
                agentId = agent;
            }

            void InteractAgent::ClearAgentId() {
                agentId = GW::Nothing<DWORD>();
            }
        }
    }
}