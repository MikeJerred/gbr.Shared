#pragma once

#include "BaseCommand.h"

namespace gbr {
	namespace Shared {
		namespace Commands {
			class Seed : public BaseCommand {
			private:
				static bool isSeedRequired;
			public:
				struct Request : public BaseRequest {
					Request() : BaseRequest(CommandType::Seed) {}
				};

				static void Execute(Request* request);

				static bool IsSeedRequired();
				static void SetSeedRequired(bool required);
			};
		}
	}
}
