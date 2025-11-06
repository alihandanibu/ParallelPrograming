# Vectorization Assignment - IT 2004 Parallel Programming

## Compilation and Build
```bash
mkdir build && cd build
cmake ..
make
Evo kompletan README tekst za copy-paste u jedan blok:

```
# Vectorization Assignment - IT 2004 Parallel Programming

## Compilation and Build
```bash
mkdir build && cd build
cmake ..
make
```

## Compiler Vectorization Reports

### timestep_opt1.c (Basic SIMD Reduction)
```
/home/student/Desktop/week6 parallel/timestep_opt1.c:9:9: optimized: loop vectorized using 32 byte vectors
/home/student/Desktop/week6 parallel/timestep_opt1.c:11:7: optimized: loop vectorized using 16 byte vectors
/home/student/Desktop/week6 parallel/timestep_opt1.c:9:9: optimized: loop vectorized using 32 byte vectors
```

### timestep_opt2.c (With Private Clause)
```
/home/student/Desktop/week6 parallel/timestep_opt2.c:9:9: optimized: loop vectorized using 32 byte vectors
/home/student/Desktop/week6 parallel/timestep_opt2.c:11:7: optimized: loop vectorized using 16 byte vectors
/home/student/Desktop/week6 parallel/timestep_opt2.c:9:9: optimized: loop vectorized using 32 byte vectors
```

### timestep_opt3.c (Variables Declared Inside Loop)
```
/home/student/Desktop/week6 parallel/timestep_opt3.c:8:9: optimized: loop vectorized using 32 byte vectors
/home/student/Desktop/week6 parallel/timestep_opt3.c:10:7: optimized: loop vectorized using 16 byte vectors
/home/student/Desktop/week6 parallel/timestep_opt3.c:8:9: optimized: loop vectorized using 32 byte vectors
```

## LIKWID Performance Analysis (FLOPS_DP Group)

### timestep_opt1 Results:
```
+--------------------------------------+---------+-------------+
|                 Event                | Counter |  HWThread 0 |
+--------------------------------------+---------+-------------+
| FP_COMP_OPS_EXE_SSE_FP_PACKED_DOUBLE |   PMC0  |  6042454352 |
| FP_COMP_OPS_EXE_SSE_FP_SCALAR_DOUBLE |   PMC1  |         899 |
|       SIMD_FP_256_PACKED_DOUBLE      |   PMC2  |          75 |
+--------------------------------------+---------+-------------+

+----------------------+--------------+
|        Metric        |  HWThread 0  |
+----------------------+--------------+
|  Runtime (RDTSC) [s] |      20.0938 |
|     DP [MFLOP/s]     |     601.4243 |
|   Packed [MUOPS/s]   |     300.7121 |
|   Scalar [MUOPS/s]   | 4.474013e-05 |
|  Vectorization ratio |     100.0000 |
+----------------------+--------------+
```

### timestep_opt2 Results:
```
+--------------------------------------+---------+-------------+
|                 Event                | Counter |  HWThread 0 |
+--------------------------------------+---------+-------------+
| FP_COMP_OPS_EXE_SSE_FP_PACKED_DOUBLE |   PMC0  |  6043171297 |
| FP_COMP_OPS_EXE_SSE_FP_SCALAR_DOUBLE |   PMC1  |          46 |
|       SIMD_FP_256_PACKED_DOUBLE      |   PMC2  |          77 |
+--------------------------------------+---------+-------------+

+----------------------+--------------+
|        Metric        |  HWThread 0  |
+----------------------+--------------+
|  Runtime (RDTSC) [s] |      20.4201 |
|     DP [MFLOP/s]     |     591.8838 |
|   Packed [MUOPS/s]   |     295.9419 |
|   Scalar [MUOPS/s]   | 2.252679e-06 |
|  Vectorization ratio |     100.0000 |
+----------------------+--------------+
```

### timestep_opt3 Results:
```
+--------------------------------------+---------+-------------+
|                 Event                | Counter |  HWThread 0 |
+--------------------------------------+---------+-------------+
| FP_COMP_OPS_EXE_SSE_FP_PACKED_DOUBLE |   PMC0  |  6042336412 |
| FP_COMP_OPS_EXE_SSE_FP_SCALAR_DOUBLE |   PMC1  |        1847 |
|       SIMD_FP_256_PACKED_DOUBLE      |   PMC2  |          80 |
+--------------------------------------+---------+-------------+

+----------------------+--------------+
|        Metric        |  HWThread 0  |
+----------------------+--------------+
|  Runtime (RDTSC) [s] |      20.9324 |
|     DP [MFLOP/s]     |     577.3188 |
|   Packed [MUOPS/s]   |     288.6593 |
|   Scalar [MUOPS/s]   |       0.0001 |
|  Vectorization ratio |     100.0000 |
+----------------------+--------------+
```

## Performance Summary

| Version | Runtime (s) | MFLOP/s | Vectorization | Packed Ops | Scalar Ops | 256-bit Ops |
|---------|-------------|---------|---------------|------------|------------|-------------|
| opt1    | 20.094      | 601.42  | 100.0000%     | 6,042,454,352 | 899       | 75         |
| opt2    | 20.420      | 591.88  | 100.0000%     | 6,043,171,297 | 46        | 77         |
| opt3    | 20.932      | 577.32  | 100.0000%     | 6,042,336,412 | 1,847     | 80         |

## Analysis

### 1. Vectorization Success
 All three versions achieved 100% vectorization ratio - Perfect SIMD utilization

### 2. Performance Comparison
- **Fastest**: timestep_opt1 - 20.094s runtime, 601.42 MFLOP/s
- **Middle**: timestep_opt2 - 20.420s runtime, 591.88 MFLOP/s  
- **Slowest**: timestep_opt3 - 20.932s runtime, 577.32 MFLOP/s

### 3. Vector Operation Analysis
- **Packed Operations**: ~6 billion operations across all versions (99.99%+ of total)
- **Scalar Operations**: Minimal (46-1847 operations, <0.001%)
- **256-bit Operations**: Very limited usage (75-80 operations) - Sandy Bridge has limited AVX support

### 4. Hardware Information
- **CPU**: Intel(R) Core(TM) i3-2120 @ 3.30GHz
- **Architecture**: Sandy Bridge
- **Vector Support**: Primarily 128-bit SSE, limited 256-bit AVX

## Conclusion
All three vectorization approaches successfully achieved **perfect 100% vectorization**. The basic SIMD reduction (opt1) performed best, while declaring variables inside the loop (opt3) showed slightly worse performance. The Sandy Bridge processor effectively utilized 128-bit vector instructions but had minimal 256-bit AVX usage due to architectural limitations.

## Files Included
- `timestep_opt1.c` - Basic SIMD reduction
- `timestep_opt2.c` - With private clause  
- `timestep_opt3.c` - Variables declared inside loop
- `main.c` - Test driver
- `timestep.h` - Header file
- `CMakeLists.txt` - Build configuration
```
