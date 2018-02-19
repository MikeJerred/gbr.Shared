#include <json/json.hpp>

#include "Seed.h"

namespace gbr {
	namespace Shared {
		namespace Commands {
			using json = nlohmann::json;

			bool Seed::isSeedRequired = false;

			void Seed::Execute(Request* request) {
				// todo
			}

			bool Seed::IsSeedRequired() {
				return isSeedRequired;
			}

			void Seed::SetSeedRequired(bool required) {
				isSeedRequired = required;
			}
		}
	}
}