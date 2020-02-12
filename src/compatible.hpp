#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport)

#if defined(_MSC_VER)
#define CQ_EXPORT(ReturnType, FuncName, ParamsSize, ...)                      \
    __pragma(                                                                 \
        comment(linker, "/EXPORT:" #FuncName "=_" #FuncName "@" #ParamsSize)) \
        DLL_EXPORT ReturnType __stdcall FuncName(__VA_ARGS__)
#else
#define CQ_EXPORT(ReturnType, FuncName, ParamsSize, ...) \
    DLL_EXPORT ReturnType __stdcall FuncName(__VA_ARGS__)
#endif