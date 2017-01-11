#include <algorithm>

#include "AggressiveMoveTo.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            DWORD AggressiveMoveTo::targetEnemyId = 0;
            DWORD AggressiveMoveTo::targetNpcId = 0;

            void AggressiveMoveTo::Execute(Request* request) {
                auto pos = GW::GamePos(request->x, request->y, request->zPlane);

                GW::Gamethread().Enqueue([=]() {
                    std::vector<GW::Agent*> enemies;
                    std::vector<GW::Agent*> npcs;
                    const auto adjacentSq = GW::Constants::Range::Adjacent * GW::Constants::Range::Adjacent;

                    for (auto agent : GW::Agents().GetAgentArray()) {
                        if (agent
                            && !agent->GetIsDead()
                            && agent->GetIsLivingType()
                            && agent->pos.SquaredDistanceTo(pos) < adjacentSq) {

                            if (agent->Allegiance == 3 && !(agent->TypeMap & 0x4000)) {
                                enemies.push_back(agent);
                            }
                            else if (agent->IsNPC() && !(agent->TypeMap & 0x4000)) {
                                npcs.push_back(agent);
                            }
                        }
                    }

                    if (enemies.size() > 0) {
                        auto target = *std::max_element(enemies.begin(), enemies.end(), [=](GW::Agent* a, GW::Agent* b) {
                            auto distanceA = a->pos.SquaredDistanceTo(pos);
                            auto distanceB = b->pos.SquaredDistanceTo(pos);
                            return distanceA < distanceB;
                        });

                        targetEnemyId = target->Id;
                        GW::Agents().Move(pos);
                    }
                    else if (npcs.size() > 0) {
                        auto target = *std::max_element(npcs.begin(), npcs.end(), [=](GW::Agent* a, GW::Agent* b) {
                            auto distanceA = a->pos.SquaredDistanceTo(pos);
                            auto distanceB = b->pos.SquaredDistanceTo(pos);
                            return distanceA < distanceB;
                        });

                        targetNpcId = target->Id;
                        GW::Agents().Move(pos);
                    }
                    else {
                        targetEnemyId = 0;
                        targetNpcId = 0;
                        GW::Agents().Move(pos);
                    }
                });
            }

            DWORD AggressiveMoveTo::GetTargetEnemyId() {
                return targetEnemyId;
            }

            void AggressiveMoveTo::SetTargetEnemyId(DWORD agentId) {
                targetEnemyId = agentId;
            }

            DWORD AggressiveMoveTo::GetTargetNpcId() {
                return targetNpcId;
            }

            void AggressiveMoveTo::SetTargetNpcId(DWORD agentId) {
                targetNpcId = agentId;
            }
        }
    }
}