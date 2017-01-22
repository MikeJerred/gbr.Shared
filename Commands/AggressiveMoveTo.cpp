#include <algorithm>

#include "MoveTo.h"
#include "AggressiveMoveTo.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            DWORD AggressiveMoveTo::targetAgentId = 0;
            GW::Maybe<GW::GamePos> AggressiveMoveTo::spiritPos = GW::Maybe<GW::GamePos>::Nothing();

            void AggressiveMoveTo::Execute(Request* request) {
                auto pos = GW::GamePos(request->x, request->y, request->zPlane);

                GW::Gamethread().Enqueue([=]() {
                    std::vector<GW::Agent*> closeAgents;
                    const auto adjacentSq = GW::Constants::Range::Adjacent * GW::Constants::Range::Adjacent;

                    for (auto agent : GW::Agents().GetAgentArray()) {
                        if (agent && agent->pos.SquaredDistanceTo(pos) < adjacentSq) {
                            closeAgents.push_back(agent);
                        }
                    }

                    if (closeAgents.size() > 0) {
                        auto target = *std::max_element(closeAgents.begin(), closeAgents.end(), [=](GW::Agent* a, GW::Agent* b) {
                            if (!a || a->GetIsItemType())
                                return true;
                            if (!b || b->GetIsItemType())
                                return false;

                            if ((a->Allegiance == 3 && !a->GetIsDead() && !a->GetIsSpawned() && b->Allegiance != 3)
                                || (a->Allegiance != 3 && !b->GetIsDead() && !b->GetIsSpawned() && b->Allegiance == 3)) {
                                // prioritize non-spirit enemy agents that are alive
                                return b->Allegiance == 3;
                            }

                            if ((a->IsPlayer() && a->GetIsDead()
                                && !(b->IsPlayer() && b->GetIsDead()))
                                || (b->IsPlayer() && b->GetIsDead()
                                    && !(a->IsPlayer() && a->GetIsDead()))) {
                                // prioritize dead players
                                return b->IsPlayer() && b->GetIsDead();
                            }

                            if ((a->GetIsSpawned() && !b->GetIsSpawned())
                                || (!a->GetIsSpawned() && b->GetIsSpawned())) {
                                // prioritize non spirits
                                return a->GetIsSpawned();
                            }

                            auto distanceA = a->pos.SquaredDistanceTo(pos);
                            auto distanceB = b->pos.SquaredDistanceTo(pos);
                            return distanceA < distanceB;
                        });

                        SetTargetAgentId(target->Id);
                        SetSpiritPos(GW::Maybe<GW::GamePos>::Nothing());
                        MoveTo::SetPos(GW::Maybe<GW::GamePos>::Nothing());
                    }
                    else {
                        SetTargetAgentId(0);
                        SetSpiritPos(pos);
                        MoveTo::SetPos(GW::Maybe<GW::GamePos>::Nothing());
                        GW::Agents().Move(pos);
                    }
                });
            }

            DWORD AggressiveMoveTo::GetTargetAgentId() {
                return targetAgentId;
            }

            void AggressiveMoveTo::SetTargetAgentId(DWORD agentId) {
                targetAgentId = agentId;
            }

            GW::Maybe<GW::GamePos> AggressiveMoveTo::GetSpiritPos() {
                return spiritPos;
            }

            void AggressiveMoveTo::SetSpiritPos(GW::Maybe<GW::GamePos> pos) {
                spiritPos = pos;
            }
        }
    }
}