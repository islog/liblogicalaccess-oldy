
#ifndef LLA_READERS_PROMAG_API_H
#define LLA_READERS_PROMAG_API_H

#ifdef PROMAGREADERS_STATIC_DEFINE
#  define LLA_READERS_PROMAG_API
#  define PROMAGREADERS_NO_EXPORT
#else
#  ifndef LLA_READERS_PROMAG_API
#    ifdef promagreaders_EXPORTS
        /* We are building this library */
#      define LLA_READERS_PROMAG_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define LLA_READERS_PROMAG_API __declspec(dllimport)
#    endif
#  endif

#  ifndef PROMAGREADERS_NO_EXPORT
#    define PROMAGREADERS_NO_EXPORT 
#  endif
#endif

#ifndef PROMAGREADERS_DEPRECATED
#  define PROMAGREADERS_DEPRECATED __declspec(deprecated)
#endif

#ifndef PROMAGREADERS_DEPRECATED_EXPORT
#  define PROMAGREADERS_DEPRECATED_EXPORT LLA_READERS_PROMAG_API PROMAGREADERS_DEPRECATED
#endif

#ifndef PROMAGREADERS_DEPRECATED_NO_EXPORT
#  define PROMAGREADERS_DEPRECATED_NO_EXPORT PROMAGREADERS_NO_EXPORT PROMAGREADERS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PROMAGREADERS_NO_DEPRECATED
#    define PROMAGREADERS_NO_DEPRECATED
#  endif
#endif

#endif /* LLA_READERS_PROMAG_API_H */
