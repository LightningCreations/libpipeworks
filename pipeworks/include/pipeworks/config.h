#ifndef PIPEWORKS_CONFIG_H_2020_06_04_09_40_37
#define PIPEWORKS_CONFIG_H_20202_06_04_09_40_37


#ifdef _WIN32
#define PIPEWORKS_EXPORT __declspec(dllexport)
#define PIPEWORKS_IMPORT __declspec(dllimport)
#else
#define PIPEWORKS_EXPORt __attribute__((visibility("default")))
#define PIPEWORKS_IMPORT __attribute__((visibility("default")))
#endif

#ifdef PIPEWORKS_BUILDSHARED
#define PIPEWORKS_API PIPEWORKS_EXPORT
#else
#define PIPEWORKS_API PIPEWORKS_IMPORT
#endif



#endif
