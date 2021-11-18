#ifndef __CONFIG_7C93E23E270F0C7E1773E9CC6E60E394_H__
#define __CONFIG_7C93E23E270F0C7E1773E9CC6E60E394_H__

#define __TCAL_INTEGRATE_ALL


#ifdef __TCAL_INTEGRATE_ALL

#else
#   ifndef __TCAL_INTEGRATE_VEC
#   define __TCAL_DISABLE_VEC
#   endif
// TODO
#endif






#define CFG_VEC_INIT_CAPACITY             1   // capacity after vector initialization
#define CFG_VEC_EXPAND_TIMES              2   // must > 1, otherwise it will cause problem at expanding
#define CFG_VEC_EXPAND_LINEAR_DELTA       1   // usually >= 1, otherwise it will cause problem at expanding
#define CFG_VEC_SHRINK_TIMES              0   // 0 means vectors will not shrink in any situation (recommended), otherwise it must > 1

#endif //__CONFIG_7C93E23E270F0C7E1773E9CC6E60E394_H__
