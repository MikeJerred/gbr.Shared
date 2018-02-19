#include <stdexcept>
#include <string>

#include "BaseCommand.h"
#include "DropBuff.h"
#include "Disperse.h"
#include "InteractAgent.h"
#include "MoveTo.h"
#include "PlaceSpirit.h"
#include "Resign.h"
#include "Seed.h"
#include "Terminate.h"
#include "ToggleRender.h"
#include "UseSkill.h"

namespace gbr {
    namespace Shared {
        namespace Commands {
            bool BaseCommand::ExecuteCommand(BaseRequest* request) {
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
                case CommandType::PlaceSpirit:
                    PlaceSpirit::Execute(static_cast<PlaceSpirit::Request*>(request));
                    break;
                case CommandType::Terminate:
                    return Terminate::Execute(static_cast<Terminate::Request*>(request));
                    break;
                case CommandType::ToggleRender:
                    ToggleRender::Execute(static_cast<ToggleRender::Request*>(request));
                    break;
                case CommandType::Disperse:
                    Disperse::Execute(static_cast<Disperse::Request*>(request));
                    break;
                case CommandType::InteractAgent:
                    InteractAgent::Execute(static_cast<InteractAgent::Request*>(request));
                    break;
				case CommandType::Seed:
					Seed::Execute(static_cast<Seed::Request*>(request));
					break;
                default:
                    throw std::invalid_argument(std::string("Invalid Command Type: ") + std::to_string((int)request->type));
                }

                return false;
            }
        }
    }
}