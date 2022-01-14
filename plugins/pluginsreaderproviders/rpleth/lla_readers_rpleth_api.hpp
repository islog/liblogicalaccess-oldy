
#ifndef LLA_READERS_RPLETH_API_H
#define LLA_READERS_RPLETH_API_H

#ifdef RPLETHREADERS_STATIC_DEFINE
#  define LLA_READERS_RPLETH_API
#  define RPLETHREADERS_NO_EXPORT
#else
#  ifndef LLA_READERS_RPLETH_API
#    ifdef rplethreaders_EXPORTS
        /* We are building this library */
#      define LLA_READERS_RPLETH_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define LLA_READERS_RPLETH_API __declspec(dllimport)
#    endif
#  endif

#  ifndef RPLETHREADERS_NO_EXPORT
#    define RPLETHREADERS_NO_EXPORT 
#  endif
#endif

#ifndef RPLETHREADERS_DEPRECATED
#  define RPLETHREADERS_DEPRECATED __declspec(deprecated)
#endif

#ifndef RPLETHREADERS_DEPRECATED_EXPORT
#  define RPLETHREADERS_DEPRECATED_EXPORT LLA_READERS_RPLETH_API RPLETHREADERS_DEPRECATED
#endif

#ifndef RPLETHREADERS_DEPRECATED_NO_EXPORT
#  define RPLETHREADERS_DEPRECATED_NO_EXPORT RPLETHREADERS_NO_EXPORT RPLETHREADERS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RPLETHREADERS_NO_DEPRECATED
#    define RPLETHREADERS_NO_DEPRECATED
#  endif
#endif

#endif /* LLA_READERS_RPLETH_API_H */
