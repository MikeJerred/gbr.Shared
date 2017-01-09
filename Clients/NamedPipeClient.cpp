#include "NamedPipeClient.h"

namespace gbr {
    namespace Shared {
        namespace Clients {
            const std::initializer_list<std::wstring> SingletonNamedPipeClient::names = {
                L"A S L Force",
                L"Callisto Delta",
                L"Violetta Alpha",
                L"Bellatrix Beta",
                L"Solitude Zeta",
                L"Marianne Gamma",
                L"Solace Epsilon"
            };
            std::vector<NamedPipeClient> SingletonNamedPipeClient::pipes = std::vector<NamedPipeClient>();

            NamedPipeClient::NamedPipeClient(const wchar_t* name) {
                auto nameString = std::wstring(L"\\\\.\\pipe\\gbr_") + name;
                pipeHandle = CreateFile(
                    nameString.c_str(),
                    GENERIC_WRITE | GENERIC_READ,
                    0,
                    NULL,
                    OPEN_EXISTING,
                    0,
                    NULL);
            }
        }
    }
}