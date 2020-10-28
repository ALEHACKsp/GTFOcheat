#include "dllmain.h"
#include <vector>
#include "Memory.h"
#ifdef DEBUG

#define ALLOCCONSOLE()\
{\
    AllocConsole();\
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);\
}

#define FREECONSOLE()\
{\
    fclose(stdout);\
    FreeConsole();\
}
#else

#define ALLOCCONSOLE()
#define FREECONSOLE()

#endif

void Detach()
{
    FREECONSOLE()
}

DWORD WINAPI fMain(LPVOID lpParameter)
{
    ALLOCCONSOLE()

    modules::Initialize();
    LOGHEX("GameAssembly.dll", modules::GameAssembly)

    std::vector<std::ptrdiff_t> offsets = {0xB8, 0x68, 0x20, 0x90, 0x220};
    int* DynamicAmmo = memory::ResolvePointer<int>(modules::GameAssembly + 0x02A08718, offsets);

    while(true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1) break;

        *DynamicAmmo = 101;
        std::cout << *DynamicAmmo << std::endl;

        Sleep(10);
    }
    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParameter), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        HANDLE hThread = CreateThread(nullptr, 0, fMain, hModule, 0, nullptr);
        if (hThread)
        {
            CloseHandle(hThread);
        }
    } else if (dwReason == DLL_PROCESS_DETACH && !lpReserved) {
        Detach();
    }
    return TRUE;
}