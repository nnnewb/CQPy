#pragma once

#define DLL_EXPORT extern "C" __declspec(dllexport)

#define CQ_IMPORT_API(ReturnType, FuncName, ...)                               \
  typedef ReturnType(__stdcall *__CQ_##FuncName##_T)(__VA_ARGS__);             \
  __CQ_##FuncName##_T CQ_##FuncName;                                           \
  static bool __CQ_API_##FuncName##_REGISTERED =                               \
      add_initializer([](auto dll) {                                           \
        CQ_##FuncName = reinterpret_cast<__CQ_##FuncName##_T>(                 \
            GetProcAddress(dll, "CQ_" #FuncName));                             \
      });

#define CQ_IMPORT_API_DECLARE(ReturnType, FuncName, ...)                       \
  extern ReturnType(__stdcall *CQ_##FuncName)(__VA_ARGS__);

#if defined(_MSC_VER)
#define CQ_EXPORT(ReturnType, FuncName, ParamsSize, ...)                       \
  __pragma(                                                                    \
      comment(linker, "/EXPORT:" #FuncName "=_" #FuncName "@" #ParamsSize))    \
      DLL_EXPORT ReturnType __stdcall FuncName(__VA_ARGS__)
#define CQPY_API(ReturnType, CQ_API_FUNC, PY_API, ...)                         \
  m.def(#PY_API, std::function<ReturnType __stdcall(__VA_ARGS__)>(CQ_API_FUNC))
#else
#define CQ_EXPORT(ReturnType, FuncName, ParamsSize, ...)                       \
  DLL_EXPORT ReturnType __stdcall FuncName(__VA_ARGS__)
#define CQPY_API(ReturnType, CQ_API_FUNC, PY_API, ...)                         \
  m.def(#PY_API, std::function<ReturnType(__VA_ARGS__)>(CQ_API_FUNC))
#endif