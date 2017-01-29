#include <GWCA/GWCA.h>
#include <GWCA/Managers/PartyMgr.h>

#include "Disperse.h"
#include "AggressiveMoveTo.h"
#include "MoveTo.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            void Disperse::Execute(Request* request) {
                auto x = request->x;
                auto y = request->y;

                GW::Gamethread().Enqueue([=]() {
                    auto player = GW::Agents().GetPlayer();
                    auto party = GW::Partymgr().GetPartyInfo();

                    if (!player || !party || !party->players.valid())
                        return;

                    auto players = GW::Partymgr().GetPartyInfo()->players;

                    auto index = 0;

                    for (int i = 0; i < players.size(); ++i) {
                        auto p = players[i];
                        if (p.loginnumber == player->LoginNumber) {
                            index = i % 7;
                            break;
                        }
                    }

                    auto radius = GW::Constants::Range::Earshot - 200.0f;
                    auto angle = 2 * 3.1415926535 / index;
                    auto newX = radius * cos(angle);
                    auto newY = radius * sin(angle);
                    auto newPos = GW::GamePos(newX + x, newY + y);

                    AggressiveMoveTo::SetSpiritPos(GW::Maybe<GW::GamePos>::Nothing());
                    AggressiveMoveTo::SetTargetAgentId(0);
                    MoveTo::SetPos(newPos);

                    GW::Agents().Move(newPos);
                });
            }
        }
    }
}