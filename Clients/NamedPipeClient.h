#pragma once

#include <Windows.h>
#include <GWCA/GWCA.h>

namespace gbr {
    namespace Shared {
        namespace Clients {
            class NamedPipeClient {
            public:
                NamedPipeClient(const wchar_t* name);

                template<class T>
                void Send(T command) {
                    if (pipeHandle != INVALID_HANDLE_VALUE) {
                        DWORD bytesWritten;
                        WriteFile(pipeHandle, &command, sizeof(T), &bytesWritten, NULL);
                    }
                }
            private:
                HANDLE pipeHandle;
            };

            class SingletonNamedPipeClient {
            public:
                static void Connect() {
                    if (pipes.empty()) {
                        for (auto name : names) {
                            pipes.push_back(NamedPipeClient(name.c_str()));
                        }
                    }
                }

                static void Reconnect() {
                    pipes.empty();
                    Connect();
                }

                template<class T>
                static void Send(T command) {
                    Connect();

                    for (auto pipe : pipes) {
                        pipe.Send(command);
                    }
                }
            private:
                static std::vector<NamedPipeClient> pipes;
                static const std::initializer_list<std::wstring> names;
            };
        }
    }
}