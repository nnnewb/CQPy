#pragma once
#include <Windows.h>

#define DLL_EXPORT extern "C" __declspec(dllexport)
#define CQ_EVENT(ReturnType, FuncName, ParamsSize, ...)                            \
    __pragma(comment(linker, "/EXPORT:" #FuncName "=_" #FuncName "@" #ParamsSize)) \
        DLL_EXPORT ReturnType __stdcall FuncName(__VA_ARGS__)
