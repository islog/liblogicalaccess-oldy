
#ifndef LLA_READERS_SCIEL_API_H
#define LLA_READERS_SCIEL_API_H

#ifdef SCIELREADERS_STATIC_DEFINE
#  define LLA_READERS_SCIEL_API
#  define SCIELREADERS_NO_EXPORT
#else
#  ifndef LLA_READERS_SCIEL_API
#    ifdef scielreaders_EXPORTS
        /* We are building this library */
#      define LLA_READERS_SCIEL_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define LLA_READERS_SCIEL_API __declspec(dllimport)
#    endif
#  endif

#  ifndef SCIELREADERS_NO_EXPORT
#    define SCIELREADERS_NO_EXPORT 
#  endif
#endif

#ifndef SCIELREADERS_DEPRECATED
#  define SCIELREADERS_DEPRECATED __declspec(deprecated)
#endif

#ifndef SCIELREADERS_DEPRECATED_EXPORT
#  define SCIELREADERS_DEPRECATED_EXPORT LLA_READERS_SCIEL_API SCIELREADERS_DEPRECATED
#endif

#ifndef SCIELREADERS_DEPRECATED_NO_EXPORT
#  define SCIELREADERS_DEPRECATED_NO_EXPORT SCIELREADERS_NO_EXPORT SCIELREADERS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SCIELREADERS_NO_DEPRECATED
#    define SCIELREADERS_NO_DEPRECATED
#  endif
#endif

#endif /* LLA_READERS_SCIEL_API_H */
