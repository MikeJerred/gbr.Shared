#pragma once

#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class AggressiveMoveTo : public BaseCommand {
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::AggressiveMoveTo) {}

                    float x;
                    float y;
                    DWORD zPlane;
                };

                static void Execute(Request* request);
                static DWORD GetTargetEnemyId();
                static void SetTargetEnemyId(DWORD agentId);
                static DWORD GetTargetNpcId();
                static void SetTargetNpcId(DWORD agentId);
            private:
                static DWORD targetEnemyId;
                static DWORD targetNpcId;
            };
        }
    }
}