#ifndef __VEC_7C93E23E270F0C7E1773E9CC6E60E394_H__
#define __VEC_7C93E23E270F0C7E1773E9CC6E60E394_H__

#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

#include "config.h"

#ifndef __TCAL_DISABLE_VEC

#if CFG_VEC_SHRINK_TIMES < 0 || (CFG_VEC_SHRINK_TIMES > 0 && CFG_VEC_SHRINK_TIMES <= 1)
#error "Illegal shrink times"
#endif

#if CFG_VEC_EXPAND_TIMES <= 1
#error "Illegal expand times"
#endif


typedef struct tag_tcal_vec {
    size_t  _sizeOfT;
    size_t  _size;
    size_t  _cap;
    void   *_data_p;
} tcal_vec;

void __tcal_vec_init__(tcal_vec * vec_p, size_t sizeOfT);
void __tcal_vec_destroy__(tcal_vec * vec_p);
void __tcal_vec_push__(tcal_vec * vec_p, const void * p);
void __tcal_vec_pop__(tcal_vec * vec_p);
void __tcal_vec_insert__(tcal_vec * vec_p, size_t i, const void *p);
void __tcal_vec_remove__(tcal_vec * vec_p, size_t i);
void * __tcal_vec_tail__(tcal_vec * vec_p);
void __tcal_vec_sort__(tcal_vec *vec_p, int (*compare_func)(const void *, const void *));
size_t __tcal_vec_erase__(tcal_vec * vec_p, size_t beg, size_t end);
tcal_vec __tcal_vec_dup__(tcal_vec * vec_p);
void __tcal_vec_merge__(tcal_vec * vec_dst_p, const tcal_vec * vec_src_p);


#define TCAL_VEC_INIT(T, name)           \
    tcal_vec name;                       \
    __tcal_vec_init__(&(name), sizeof(T))

#define TCAL_VEC_DESTROY(name) \
    tcal_vec name;                       \
    __tcal_vec_destroy__(&(name))


#define TCAL_VEC_SIZE(name) \
    name._size

#define TCAL_VEC_EMPTY(name) \
    name._size == 0

#define TCAL_VEC_CAPACITY(name) \
    name._cap

#define TCAL_VEC_GET(T, name, i) \
    (*(T *)((char *)((name)._data_p) + (i) * (name)._sizeOfT))

#define TCAL_VEC_DATA(T, name) \
    ((T *)((name)._data_p))

#define TCAL_VEC_SET(name, i, elem) \
    memcpy((char *)((name)._data_p) + (i) * (name)._sizeOfT, &(elem), (name)._sizeOfT);

#define TCAL_VEC_PUSH(T, name, elem) \
    { T __##T##_##_##name__ = elem; __tcal_vec_push__(&(name), (const void *)&(__##T##_##_##name__)); }

#define TCAL_VEC_POP(name) \
    __tcal_vec_pop__(&(name))

#define TCAL_VEC_TAIL(T, name) \
    (*(T *)__tcal_vec_tail__(&(name)))

#define TCAL_VEC_INSERT(T, name, i, elem) \
    { T __##T##_##_##name__ = elem; __tcal_vec_insert__(&(name), i, (const void *)&(__##T##_##_##name__)); }

#define TCAL_VEC_REMOVE(name, i) \
    __tcal_vec_remove__(&(name), i)

#define TCAL_VEC_SORT(name, compare_func) \
    __tcal_vec_sort__(&(name), compare_func)

#define TCAL_VEC_DUP(name) \
    __tcal_vec_dup__(name)

#define TCAL_VEC_MERGE(name_dst, name_src) \
    __tcal_vec_merge__(name_dst, name_src)

#define TCAL_VEC_ERASE(name, beg, end) \
    __tcal_vec_erase__(name, beg, end)

#endif //__VEC_7C93E23E270F0C7E1773E9CC6E60E394_H__

#endif