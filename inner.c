#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <link.h>
#include "inner.h"
#include <unistd.h>
#include <sys/syscall.h> 
#include <sys/types.h>


void inner_para(int outer_tid, int outer_tnum, int outer_get_max_threads, int inner_get_max_threads){
    #pragma omp parallel shared(outer_tid, outer_tnum)
    {
        int inner_tid = syscall(SYS_gettid);
        int inner_tnum = omp_get_thread_num();
        printf("  [%i]        [%i]               [%i]             [%i]        [%i]                [%i]                    [%i]\n",
               outer_tid, outer_tnum, outer_get_max_threads, inner_tid, inner_tnum, omp_get_num_threads(), inner_get_max_threads);
    }
}


void inner_set_num_threads(int n){
    omp_set_num_threads(n);
}


int inner_get_max_threads(){
    return omp_get_max_threads();
}