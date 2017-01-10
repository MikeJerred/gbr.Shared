#include "BaseCommand.h"
#include "AggressiveMoveTo.h"
#include "DropBuff.h"
#include "MoveTo.h"
#include "Resign.h"
#include "UseSkill.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            void BaseCommand::ExecuteCommand(BaseRequest* request) {
                switch (request->type) {
                case CommandType::MoveTo:
                    MoveTo::Execute(static_cast<MoveTo::Request*>(request));
                    break;
                case CommandType::UseSkill:
                    UseSkill::Execute(static_cast<UseSkill::Request*>(request));
                    break;
                case CommandType::DropBuff:
                    DropBuff::Execute(static_cast<DropBuff::Request*>(request));
                    break;
                case CommandType::Resign:
                    Resign::Execute(static_cast<Resign::Request*>(request));
                    break;
                case CommandType::AggressiveMoveTo:
                    AggressiveMoveTo::Execute(static_cast<AggressiveMoveTo::Request*>(request));
                    break;
                default:
                    throw std::invalid_argument(std::string("Invalid Command Type: ") + std::to_string((int)request->type));
                }
            }
        }
    }
}