#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#include "vec.h"

int comp(const double * a, const double * b) {
    return *a > *b;
}

int main() {
    TCAL_VEC_INIT(double, a);

    struct timespec ts0, ts;
    clock_gettime(CLOCK_REALTIME, &ts0);

    for (size_t i = 0; i < 10000; ++i) {
        TCAL_VEC_PUSH(double, a, i);
    }

    TCAL_VEC_SORT(a, comp);

    for (size_t i = 0; i < 10000; ++i) {
        printf("%lf\n", TCAL_VEC_GET(double, a, i));
    }

    clock_gettime(CLOCK_REALTIME, &ts);

    int sec_diff = ts.tv_sec - ts0.tv_sec;
    int nsec_diff = ts.tv_nsec - ts0.tv_nsec;

    size_t ms = sec_diff * 1000 + nsec_diff / 1000000;

    printf("use %ld ms, size = %ld\n", ms, TCAL_VEC_SIZE(a));

    return 0;
}
