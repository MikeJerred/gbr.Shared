#pragma once

#include <GWCA/Utilities/Maybe.h>
#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class InteractAgent : public BaseCommand {
            private:
                static GW::Maybe<DWORD> agentId;
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::InteractAgent) {}

                    DWORD agentId;
                };

                static void Execute(Request* request);

                static GW::Maybe<DWORD> GetAgentId();
                static void SetAgentId(DWORD agent);
                static void ClearAgentId();
            };
        }
    }
}