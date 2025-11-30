#ifndef CONFIG_H
#define CONFIG_H

#ifdef ACTARIA_TEST
#define DEBUG_ONLY(code) code
#else
#define DEBUG_ONLY(code)
#endif

#endif // CONFIG_H
