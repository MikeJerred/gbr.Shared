#pragma once

#include <Windows.h>
#include <GWCA/GWCA.h>

namespace gbr {
    namespace Shared {
        namespace Commands {
            enum class CommandType {
                MoveTo,
                UseSkill,
                DropBuff,
                Resign,
                PlaceSpirit,
                Terminate,
                ToggleRender,
                Disperse,
                InteractAgent,
				Seed
            };


            class BaseCommand {
            public:
                struct BaseRequest {
                protected:
                    BaseRequest(CommandType type) : type(type) {}
                public:
                    const CommandType type;
                };

                struct BaseReply {
                protected:
                    BaseReply(CommandType type) : type(type) {}
                public:
                    const CommandType type;
                };

                static bool ExecuteCommand(BaseRequest* request);
            };
        }
    }
}