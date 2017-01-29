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
                    for (auto agent : GW::Agents().GetAgentArray()) {
                        if (agent && agent->pos.SquaredDistanceTo(pos) < GW::Constants::SqrRange::Adjacent) {
                            closeAgents.push_back(agent);
                        }
                    }

                    if (closeAgents.size() > 0) {
                        auto target = *std::max_element(closeAgents.begin(), closeAgents.end(), [=](GW::Agent* a, GW::Agent* b) {
                            if (!a || !b || a->GetIsItemType() || b->GetIsItemType()) {
                                if (a && !a->GetIsItemType())
                                    return false;

                                if (b && !b->GetIsItemType())
                                    return true;

                                return b->Id < a->Id;
                            }

                            auto isEnemy = [](GW::Agent* agent) { return !agent->IsPlayer() && agent->Allegiance == 3 && !agent->GetIsDead() && !IsSpirit(agent); };
                            if (isEnemy(a) != isEnemy(b)) {
                                // prioritize non-spirit enemy agents that are alive
                                return isEnemy(b);
                            }

                            auto isDeadPlayer = [](GW::Agent* agent) { return agent->IsPlayer() && agent->GetIsDead(); };
                            if (isDeadPlayer(a) != isDeadPlayer(b)) {
                                // prioritize dead players
                                return isDeadPlayer(b);
                            }

                            if (IsSpirit(a) != IsSpirit(b)) {
                                // prioritize non spirits
                                return !IsSpirit(b);
                            }

                            auto distanceA = a->pos.SquaredDistanceTo(pos);
                            auto distanceB = b->pos.SquaredDistanceTo(pos);
                            return distanceB < distanceA;
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

            bool AggressiveMoveTo::IsSpirit(GW::Agent* agent) {
                switch (agent->PlayerNumber) {
                case GW::Constants::ModelID::QZ:
                case GW::Constants::ModelID::Winnowing:
                case GW::Constants::ModelID::EoE:
                case GW::Constants::ModelID::InfuriatingHeat:
                case GW::Constants::ModelID::Equinox:
                case GW::Constants::ModelID::Famine:
                case GW::Constants::ModelID::FrozenSoil:
                case GW::Constants::ModelID::Quicksand:
                case GW::Constants::ModelID::Lacerate:
                    return true;
                default:
                    return false;
                }
            }
        }
    }
}