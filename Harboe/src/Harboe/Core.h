#pragma once

#ifdef HB_PLATFORM_WINDOWS
	#ifdef HB_BUILD_DLL
		#define HARBOE_API __declspec(dllexport)
	#else
		#define HARBOE_API __declspec(dllimport)
	#endif
#else
	#error Harboe only supports Windows!
#endif


#define BIT(x) (1 << x)
