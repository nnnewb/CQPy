#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport)
#define CQ_EXPORT(ReturnType, FuncName, ParamsSize, ...)                            \
    __pragma(comment(linker, "/EXPORT:" #FuncName "=_" #FuncName "@" #ParamsSize)) \
        DLL_EXPORT ReturnType __stdcall FuncName(__VA_ARGS__)

#define CQ_IMPORT_API(ReturnType, FuncName, ...)                                                             \
    typedef ReturnType(__stdcall *__CQ_##FuncName##_T)(__VA_ARGS__); \
    __CQ_##FuncName##_T CQ_##FuncName;                                                                \
    static bool __CQ_API_##FuncName##_REGISTERED = add_initializer([](auto dll) {                     \
        CQ_##FuncName = reinterpret_cast<__CQ_##FuncName##_T>(GetProcAddress(dll, "CQ_" #FuncName));  \
    });

#define CQ_IMPORT_API_DECLARE(ReturnType, FuncName, ...) \
    extern ReturnType(__stdcall *CQ_##FuncName)(__VA_ARGS__);

