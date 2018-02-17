#include <json/json.hpp>
#include <GWCA/Managers/ChatMgr.h>
#include <GWCA/Managers/GameThreadMgr.h>

#include "Resign.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            using json = nlohmann::json;

            void Resign::Execute(Request* request) {
                GW::GameThread::Enqueue([]() {
                    GW::Chat::SendChat(L'/', L"resign");
                });
            }
        }
    }
}