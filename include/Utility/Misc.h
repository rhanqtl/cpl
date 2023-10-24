#ifndef CPL_UTILITY_MISC_H
#define CPL_UTILITY_MISC_H

#define _CONCAT_INTERNAL(x, y) x##y
#define CONCAT(x, y) _CONCAT_INTERNAL(x, y)

#ifdef __COUNTER__
#define ANON_VAR(prefix) CONCAT(prefix, __COUNTER__)
#else
#define ANON_VAR(prefix) CONCAT(prefix, __LINE__)
#endif

#endif // CPL_UTILITY_MISC_H
