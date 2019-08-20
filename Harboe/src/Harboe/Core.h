#pragma once

#ifdef HB_PLATFORM_WINDOWS
#	ifdef HB_BUILD_DLL
#		define HARBOE_API __declspec(dllexport)
#	else
#		define HARBOE_API __declspec(dllimport)
#	endif
#else
#	error Harboe only supports Windows!
#endif

#define BIT(x) (1 << x)

#ifdef HB_ENABLE_ASSERTS
#	define HB_ASSERT(x, ...) { if (!x) { HB_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#	define HB_CORE_ASSERT(x, ...) { if (!x) { HB_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } } 
#else
#	define HB_ASSERT(x, ...)
#	define HB_CORE_ASSERT(x, ...)
#endif

#define HB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
