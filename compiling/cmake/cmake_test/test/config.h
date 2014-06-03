#ifndef CONFIG_H
#define CONFIG_H

#define __DEBUG ON

#ifdef __DEBUG
#define DEBUG(x) printf(x)
#else
#define DEBUG(x)
#endif

#endif
