#include "Modules.h"

namespace modules
{
    uintptr_t GameAssembly;

    void Initialize()
    {
        GameAssembly = reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll"));
    }
}