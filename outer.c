#include "outer.h"
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include "inner.h"
#include <unistd.h>
#include <sys/syscall.h> 
#include <sys/types.h>


int main(int argc, char **argv){
    outer_para();
    return 0;
}


void outer_para(){
    printf(" outer_tid | outer_tnum | outer_get_max_threads | inner_tid | inner_tnum | inner_get_num_threads | inner_get_max_threads\n");
    
    // limit num threads for outer & inner separately
    inner_set_num_threads(2);
    outer_set_num_threads(3);
    
    #pragma omp parallel
    {
        int outer_tid = syscall(SYS_gettid);
        int outer_tnum = omp_get_thread_num();
        inner_para(outer_tid, outer_tnum, outer_get_max_threads(), inner_get_max_threads());
    }
}


void outer_set_num_threads(int n){
    omp_set_num_threads(n);
}


int outer_get_max_threads(){
    return omp_get_max_threads();
}