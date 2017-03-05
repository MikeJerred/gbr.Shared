#pragma once

#include <GWCA/Utilities/Maybe.h>
#include "BaseCommand.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            class PlaceSpirit : public BaseCommand {
            private:
                static GW::Maybe<GW::GamePos> spiritPos;
            public:
                struct Request : public BaseRequest {
                    Request() : BaseRequest(CommandType::PlaceSpirit) {}

                    float x;
                    float y;
                    DWORD zPlane;
                };

                static void Execute(Request* request);

                static GW::Maybe<GW::GamePos> GetSpiritPos();
                static void SetSpiritPos(const GW::GamePos& pos);
                static void ClearSpiritPos();
            };
        }
    }
}