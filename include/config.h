#ifndef CONFIG_H
#define CONFIG_H

#ifdef ACTARIA_TEST
    #define DEBUG_ONLY(code) code
#else
    #define DEBUG_ONLY(code)
#endif

#ifndef POST_ORDER
    #define PRE_ORDER 1
#else
    #define POST_ORDER 0
#endif

#ifndef LITTLE_ENDIAN
    #define BIG_ENDIAN 1
#else
    #define LITTLE_ENDIAN 1
#endif

#endif // CONFIG_H
