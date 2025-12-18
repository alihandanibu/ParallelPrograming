# Parallel Computing – Week 11  
## Slurm Workload Manager (Single-Node Setup)

### Student
Ali Handan

### System Information
- Hostname: itcenter-lab128  
- CPU: Intel Core i3 (2 physical cores, 4 threads)  
- RAM: ~8 GB  
- OS: Ubuntu (IT Lab environment)

---

## 1. Introduction

The goal of this assignment is to install, configure, and test the Slurm
Workload Manager on a single-node system. The experiment demonstrates how
Slurm schedules batch jobs, allocates CPU resources, enforces time limits,
and prevents uncontrolled system overload compared to running workloads
directly on the operating system.

---

## 2. Slurm Installation

Slurm and all required dependencies were installed using the system package
manager. The following components were installed:

- slurm-wlm  
- slurmctld  
- slurmd  
- munge  

Munge authentication was verified successfully before starting Slurm services,
ensuring secure communication between Slurm components.

---

## 3. Slurm Configuration

Slurm was configured as a single-node cluster using the configuration file:

/etc/slurm/slurm.conf

Key configuration details:
- One node: `itcenter-lab128`
- 4 logical CPUs
- One partition: `debug`
- Linux process tracking
- Time limits enforced via Slurm

The configuration enables controlled execution of batch workloads on a
single system, simulating a minimal HPC environment.

---

## 4. Starting Slurm Services
<img width="1282" height="999" alt="Screenshot from 2025-12-18 16-04-10" src="https://github.com/user-attachments/assets/af196c62-527b-4526-96a3-d3639f2142ab" />

The screenshot shows the status of the Slurm controller daemon (`slurmctld`)
using `systemctl status`. The service is active and running, confirming that
the Slurm controller was successfully started and is ready to manage job
scheduling and resource allocation on the system.

Due to restricted permissions in the IT lab environment, Slurm daemons could
not be started under a regular user account. The Slurm controller
(`slurmctld`) and node daemon (`slurmd`) were successfully started using
root privileges.

This allowed full testing of Slurm scheduling and resource management
functionality.

---

## 5. Cluster Status Verification

The Slurm cluster status was verified using the `sinfo` command.
//

The screenshot shows the Slurm cluster status using the `sinfo` command,
confirming that the single node `itcenter-lab128` is available and idle.
Multiple jobs were submitted using `sbatch compute.sh`, and the `squeue`
output demonstrates that Slurm successfully scheduled and executed the jobs,
with some jobs running and others pending due to resource allocation.

---

## 6. Job Submission with sbatch (compute.sh)

<img width="1282" height="999" alt="prvi" src="https://github.com/user-attachments/assets/f48bdc2c-62b2-40ba-9097-a9ed5e3d4d88" />

This screenshot shows the submission of multiple jobs using the `sbatch`
command with the `compute.sh` script. Each job receives a unique Job ID.
The `squeue` output confirms that Slurm successfully schedules the jobs,
with some jobs running and others pending due to limited CPU resources.

<img width="1282" height="999" alt="Screenshot from 2025-12-18 15-51-36" src="https://github.com/user-attachments/assets/00533ad3-2b3e-45a8-8f7c-3e9eb41b1089" />
The screenshot displays the `squeue` command output after submitting multiple
instances of the same job. Slurm places some jobs in the RUNNING state while
others remain PENDING due to limited available resources, demonstrating
fair scheduling and proper queue management.

Jobs were submitted using the `sbatch` command with the `compute.sh` script.
Each submission received a unique Job ID and was scheduled by Slurm on the
available node.

The job output confirms:
- Correct job initialization
- Execution on the intended node
- Allocation of a single CPU per job

---

## 7. CPU Monitoring During Job Execution

<img width="1282" height="999" alt="Screenshot from 2025-12-18 15-52-30" src="https://github.com/user-attachments/assets/11633f5c-96a2-41ea-936d-49db9160d75c" />

This screenshot shows high CPU activity while Slurm jobs are running.
Multiple `slurm_script` and `bc` processes are visible, confirming that
the workload is actively consuming CPU resources. Despite the load,
the system remains responsive, demonstrating Slurm’s ability to manage
parallel execution without uncontrolled resource exhaustion.
While jobs were running, system resource usage was monitored using the `top`
command.


The output shows active `slurm_script` and `bc` processes consuming CPU
resources, confirming that Slurm successfully controls and distributes CPU
usage across running jobs.

---

## 8. Job Time Limit Enforcement
<img width="1282" height="999" alt="Screenshot from 2025-12-18 15-58-18" src="https://github.com/user-attachments/assets/4fba6eb6-da55-4ce9-adc4-f95505f28aa5" />

The screenshot shows the contents of the job output file (`work_1.out`).
The output confirms that the job started successfully, ran on the
`itcenter-lab128` node using one processor, and was later terminated by
Slurm with the message **CANCELLED DUE TO TIME LIMIT**. This provides
direct evidence that Slurm enforces execution time limits at the job level.


Submitted jobs were automatically terminated when exceeding the specified
time limit.

Slurm displayed the message **“CANCELLED DUE TO TIME LIMIT”**, confirming that
runtime constraints are enforced correctly and that jobs cannot exceed their
allocated execution time.

---

## 9. Overload Test (overload.sh)

The `overload.sh` script was submitted multiple times to simulate a high CPU
load scenario. Slurm queued and scheduled the jobs without causing
uncontrolled system overload.

This experiment demonstrates how Slurm prevents all CPU resources from being
consumed simultaneously by competing workloads.

---

## 10. Comparison Without Slurm

When CPU-intensive workloads were executed directly on the system without
Slurm, the CPU became fully saturated, system responsiveness decreased, and
there was no mechanism to control resource usage.

This comparison highlights the importance of workload managers such as Slurm
in parallel and high-performance computing environments.

---

## 11. Conclusion

This assignment demonstrates the successful installation, configuration, and
testing of the Slurm Workload Manager on a single-node system. The experiments
show how Slurm schedules jobs, allocates CPU resources, enforces execution
limits, and maintains system stability. Slurm provides essential functionality
for managing parallel workloads in both educational and production settings.

---
