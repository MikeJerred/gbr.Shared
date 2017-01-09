#include <json/json.hpp>
#include <GWCA/Managers/ChatMgr.h>

#include "Resign.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            using json = nlohmann::json;

            void Resign::Execute(Request* request) {
                GW::Gamethread().Enqueue([]() {
                    GW::Chat().SendChat(L"resign", L'/');
                });
            }
        }
    }
}