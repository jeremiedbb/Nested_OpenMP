We expect 3 threads for outer parallelism and 2 threads for inner

## outer ICC / inner GCC
outer_tid | outer_tnum | outer_get_max_threads | inner_tid | inner_tnum | inner_get_num_threads | inner_get_max_threads
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
[18076] | [0] | [3] | [18076] | [0] | [1] | [3]
[18078] | [1] | [3] | [18078] | [0] | [1] | [3]
[18079] | [2] | [3] | [18079] | [0] | [1] | [3]

3 threads for outer as expected (3 unique values for outer_num)
Only 1 for inner. Seems that gnu openmp is aware it's in nested parallelism which is disable by default.

## outer GCC / inner ICC
outer_tid | outer_tnum | outer_get_max_threads | inner_tid | inner_tnum | inner_get_num_threads | inner_get_max_threads
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
[18158] | [0] | [3] | [18158] | [0] | [2] | [2]
[18158] | [0] | [3] | [18162] | [1] | [2] | [2]
[18160] | [2] | [3] | [18160] | [0] | [4] | [4]
[18160] | [2] | [3] | [18164] | [2] | [4] | [4]
[18160] | [2] | [3] | [18163] | [1] | [4] | [4]
[18160] | [2] | [3] | [18165] | [3] | [4] | [4]
[18159] | [1] | [3] | [18168] | [3] | [4] | [4]
[18159] | [1] | [3] | [18167] | [2] | [4] | [4]
[18159] | [1] | [3] | [18166] | [1] | [4] | [4]
[18159] | [1] | [3] | [18159] | [0] | [4] | [4]

3 threads for outer as expected.
In master thread of outer: 2 inner threads as expected
In other threads: as many as possible (4 is the value returned by omp_get_max_threads before entering the parallel region)
