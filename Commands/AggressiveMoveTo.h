#pragma once

#include <GWCA/Utilities/Maybe.h>
#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class AggressiveMoveTo : public BaseCommand {
            private:
                static DWORD targetAgentId;
                static GW::Maybe<GW::GamePos> spiritPos;
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::AggressiveMoveTo) {}

                    float x;
                    float y;
                    DWORD zPlane;
                };

                static void Execute(Request* request);

                static DWORD GetTargetAgentId();
                static void SetTargetAgentId(DWORD agentId);
                static GW::Maybe<GW::GamePos> GetSpiritPos();
                static void SetSpiritPos(GW::Maybe<GW::GamePos> pos);

                static bool IsSpirit(GW::Agent* agent);
            };
        }
    }
}