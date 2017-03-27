#include <GWCA/Managers/GameThreadMgr.h>

#include "ToggleRender.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            void ToggleRender::Execute(Request* request) {
                GW::GameThread::ToggleRenderHook();
            }
        }
    }
}