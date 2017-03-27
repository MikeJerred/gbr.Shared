#pragma once

#include <GWCA/GameEntities/Position.h>
#include <GWCA/Utilities/Maybe.h>
#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class MoveTo : public BaseCommand {
            private:
                static GW::Maybe<GW::GamePos> currentPos;
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::MoveTo) {}
                    Request(const char* s);

                    float x;
                    float y;
                    DWORD zPlane;
                };

                static void Execute(Request* request);

                static GW::Maybe<GW::GamePos> GetPos();
                static void SetPos(GW::GamePos pos);
                static void ClearPos();
            };
        }
    }
}