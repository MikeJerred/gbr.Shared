#include "ToggleRender.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            void ToggleRender::Execute(Request* request) {
                GW::Gamethread().ToggleRenderHook();
            }
        }
    }
}