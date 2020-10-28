#pragma once
#include <Windows.h>
#include <vector>

namespace memory {
    template<class t>
    t* ResolvePointer(const uintptr_t &base, const std::vector<std::ptrdiff_t> &offsets) {
        uintptr_t buffer = base;
        for (auto &offset : offsets) {
            buffer = *reinterpret_cast<uintptr_t *>(buffer);
            buffer += offset;
        }
        return reinterpret_cast<t*>(buffer);

    }
}