#include <error.h>
#include <signal.h>

#include "vec.h"
#include "utils.h"

#ifndef __TCAL_DISABLE_VEC

inline void __tcal_vec_init__(tcal_vec * vec_p, size_t sizeOfT) {
    vec_p->_data_p = malloc(CFG_VEC_INIT_CAPACITY * sizeOfT);
    vec_p->_size = 0;
    vec_p->_cap = CFG_VEC_INIT_CAPACITY;
    vec_p->_sizeOfT = sizeOfT;
}

inline void __tcal_vec_pop__(tcal_vec *vec_p) {
    if (vec_p->_size == 0) {
        raise(SIGSEGV);
    }
#if CFG_VEC_SHRINK_TIMES >= 0
    if (vec_p->_size * CFG_VEC_SHRINK_TIMES <= vec_p->_cap) {
        size_t mem_size = vec_p->_size * vec_p->_sizeOfT;
        void *tmp_p = malloc(mem_size);
        tcal_bcopy(tmp_p, vec_p->_data_p, mem_size);
        vec_p->_cap = mem_size;
        free(vec_p->_data_p);
        vec_p->_data_p = tmp_p;
    }
#endif
    --vec_p->_size;
}

inline void * __tcal_vec_tail__(tcal_vec *vec_p) {
    if (vec_p->_size == 0) {
        raise(SIGSEGV);
    }
#if CFG_VEC_SHRINK_TIMES >= 0
    if (vec_p->_size * CFG_VEC_SHRINK_TIMES <= vec_p->_cap) {
        size_t mem_size = vec_p->_size * vec_p->_sizeOfT;
        void *tmp_p = malloc(mem_size);
        tcal_bcopy(tmp_p, vec_p->_data_p, mem_size);
        vec_p->_cap = mem_size;
        free(vec_p->_data_p);
        vec_p->_data_p = tmp_p;
    }
#endif
    return (char *)vec_p->_data_p + vec_p->_size--;
}


inline void __tcal_vec_push__(tcal_vec * vec_p, const void * p) {
    size_t old_cap = vec_p->_cap;
    size_t old_mem_siz = old_cap * vec_p->_sizeOfT;
    if (vec_p->_size >= old_cap) {
        void * tmp_p = malloc(old_mem_siz);
        memcpy(tmp_p, vec_p->_data_p, old_mem_siz);
        free(vec_p->_data_p);
        vec_p->_data_p = malloc(
                (vec_p->_cap = (int)(vec_p->_cap * CFG_VEC_EXPAND_TIMES) + CFG_VEC_EXPAND_LINEAR_DELTA)
                * vec_p->_sizeOfT
        );
        tcal_bcopy(vec_p->_data_p, tmp_p, old_mem_siz);
        free(tmp_p);

    }
    tcal_bcopy((char *)(vec_p->_data_p) + (vec_p->_size++) * vec_p->_sizeOfT, p, vec_p->_sizeOfT);
}

inline void __tcal_vec_insert__(tcal_vec *vec_p, size_t i, const void *p) {
    size_t old_cap = vec_p->_cap;
    size_t old_mem_siz = vec_p->_size * vec_p->_sizeOfT;
    if (vec_p->_size >= old_cap) {
        void * tmp_p = malloc(old_mem_siz);
        tcal_bcopy(tmp_p, vec_p->_data_p, old_mem_siz);
        free(vec_p->_data_p);
        vec_p->_data_p = malloc(
                (vec_p->_cap = (int)(vec_p->_cap * CFG_VEC_EXPAND_TIMES) + CFG_VEC_EXPAND_LINEAR_DELTA)
                * vec_p->_sizeOfT
        );
        tcal_bcopy(vec_p->_data_p, tmp_p, old_mem_siz);
        free(tmp_p);
    }

    char * src = (char *)(vec_p->_data_p) + i * vec_p->_sizeOfT;
    char * dst = src + vec_p->_sizeOfT;
    tcal_bcopy4insert(dst, src, vec_p->_size * vec_p->_sizeOfT);

    tcal_bcopy((char *)(vec_p->_data_p) + vec_p->_size * vec_p->_sizeOfT, p, vec_p->_sizeOfT);
    vec_p->_size++;
}

inline void __tcal_vec_remove__(tcal_vec *vec_p, size_t i) {
    if (vec_p->_size == 0) {
        raise(SIGSEGV);
    }
#if CFG_VEC_SHRINK_TIMES >= 0
    if (vec_p->_size * CFG_VEC_SHRINK_TIMES <= vec_p->_cap) {
        size_t mem_size = vec_p->_size * vec_p->_sizeOfT;
        void *tmp_p = malloc(mem_size);
        tcal_bcopy(tmp_p, vec_p->_data_p, mem_size);
        vec_p->_cap = mem_size;
        free(vec_p->_data_p);
        vec_p->_data_p = tmp_p;
    }
#endif

    char * dst = (char *)(vec_p->_data_p) + i * vec_p->_sizeOfT;
    char * src = dst + vec_p->_sizeOfT;
    tcal_bcopy4remove(dst, src, vec_p->_size * vec_p->_sizeOfT);

    --vec_p->_size;
}

inline void __tcal_vec_sort__(tcal_vec *vec_p, int (*compare_func)(const void *, const void *)) {
    qsort(vec_p->_data_p, vec_p->_size, vec_p->_sizeOfT, compare_func);
}

inline void __tcal_vec_destroy__(tcal_vec *vec_p) {
    free(vec_p->_data_p);
    tcal_bzero(vec_p, sizeof(tcal_vec));
}

inline size_t __tcal_vec_erase__(tcal_vec *vec_p, size_t beg, size_t end) {
    return 0;
}

inline tcal_vec __tcal_vec_dup__(tcal_vec *vec_p) {
    tcal_vec res;
    res._sizeOfT = vec_p->_sizeOfT;
    res._size = vec_p->_size;
    res._cap = vec_p->_cap;

    res._data_p = malloc(res._cap);
    tcal_bcopy(res._data_p, vec_p->_data_p, res._size);
    return res;
}

inline void __tcal_vec_merge__(tcal_vec *vec_dst_p, const tcal_vec *vec_src_p) {
    if (vec_src_p->_sizeOfT != vec_dst_p->_sizeOfT) {
        raise(SIGSEGV);
    }

    size_t new_cap = vec_dst_p->_cap;
    size_t mem_size = vec_dst_p->_size * vec_dst_p->_sizeOfT;

    if (new_cap - vec_dst_p->_size <= vec_src_p->_size)  {
        do {
            new_cap = new_cap * CFG_VEC_EXPAND_TIMES + CFG_VEC_EXPAND_LINEAR_DELTA;
        } while (new_cap - vec_dst_p->_size > vec_src_p->_size);
        // renew
        void * tmp_p = malloc(mem_size);
        memcpy(tmp_p, vec_dst_p->_data_p, mem_size);
        free(vec_dst_p->_data_p);
        vec_dst_p->_data_p = malloc(new_cap * vec_dst_p->_sizeOfT);
        vec_dst_p->_cap = new_cap;

        tcal_bcopy(vec_dst_p->_data_p, tmp_p, mem_size);
        free(tmp_p);
    }

    // copy immediately
    tcal_bcopy((char *)vec_dst_p->_data_p + mem_size, vec_src_p->_data_p, vec_src_p->_sizeOfT * vec_src_p->_size);
    vec_dst_p->_size += vec_src_p->_size;
}

#endif