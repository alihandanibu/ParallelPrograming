**Parallel Computing – Week 10

CUDA, OpenCL, OpenMP, OpenACC, and GPU Server Execution**

This repository documents all practical work performed in Week 10 of the Parallel Computing course. It covers local experimentation with CUDA, OpenMP, OpenACC, and OpenCL, followed by remote deployment and execution on the department’s GPU server.

The goal of this work is to validate different parallel programming models, compare performance characteristics, and understand real GPU offloading workflows.

1. CUDA Execution (Local Machine)

The StreamTriad CUDA implementation was compiled and executed locally using nvcc.

nvcc StreamTriad.cu -o StreamTriad

./StreamTriad
./screenshots/cuda_output.png

2. OpenCL Execution (Local Machine)

The OpenCL version of StreamTriad attempted to initialize an OpenCL device.
Since no compatible OpenCL platform was detected on the local machine, the expected error occurred:
EZCL_DEVTYPE_INIT: Error with clGetDeviceIDs at line 34
This confirms the environment does not support OpenCL GPU runtime.

Screenshot:
./screenshots/opencl_error.png

3. OpenACC Execution (GCC Fallback)

GCC supports the OpenACC syntax but does not include a GPU backend by default.
Therefore, execution falls back to CPU mode.

Command:
gcc -fopenacc StreamTriad.c timer.c -o acc_exec
./acc_exec

Average runtime for stream triad loop is ~0.084 seconds
Screenshot:
./screenshots/openacc_output.png

4. OpenMP Execution (CPU / NVPTX Fallback)

The NVPTX offload target is present in GCC, but offload support is incomplete on the lab’s local machines.
As a result, OpenMP code falls back to CPU execution.

Command:
gcc -fopenmp -foffload=nvptx-none StreamTriad.c timer.c -o omp_exec
./omp_exec

verage runtime for stream triad loop is ~0.085 ms

Screenshot:
./screenshots/openmp_output.png

5. Transferring Files to the GPU Server

To perform real GPU execution, source files were copied to the remote GPU server via SCP.

Command:
scp StreamTriad.c timer.c gpulab@10.1.8.100:~

Successful transfer confirms readiness for GPU compilation.

Screenshot:
./screenshots/scp_transfer.png

6. GPU Server Verification (RTX 2060)

Upon connecting to the server:
ssh gpulab@10.1.8.100
nvidia-smi

The server reports:

NVIDIA GeForce RTX 2060

CUDA Driver Version 13.0

8 GB VRAM

Fully operational GPU device

No processes blocking compute mode

This validates that the system is ready for GPU workloads.

Screenshot:
./screenshots/gpu_server_nvidia_smi.png

Repository Structure (Visual Studio Code Overview)

A complete overview of the folder architecture is included to visualize all modules:

cuda/
ocl/
omp/
openacc
Timer utilities
Build files and Makefiles
Screenshot:
./screenshots/project_structure.png

8. Key Outcomes and Observations

CUDA successfully compiled and executed on a local machine with NVIDIA drivers.
OpenCL failed due to missing device support — expected behavior in non-GPU environments.
OpenACC with GCC defaults to CPU execution; GPU backend requires NVHPC.
OpenMP Offload also fell back to CPU, confirming missing NVPTX runtime support.
GPU Server (RTX 2060) is fully operational and validated for CUDA/OpenACC/NVHPC execution.
All steps—compilation, execution, errors, and performance readings—are documented with screenshots.
The environment differences between local machine and GPU server demonstrate the importance of toolchain availability when performing real GPU computation.

Note on Missing Files After Reset

Due to an accidental git reset --hard operation performed during cleanup, several previously completed files and intermediate work were permanently removed from the working directory.
This reset reverted the repository to an earlier state received from the remote branch, which means:

local edits,

additional screenshots,

extended debugging notes,

and earlier compiled executables

were overwritten and are no longer recoverable.

The content currently available in this branch represents the reconstructed version of the work based on what remained after the reset.
All essential outputs, screenshots, and explanations have been re-added manually to ensure the assignment remains complete and verifiable.
