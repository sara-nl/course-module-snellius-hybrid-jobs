# Snellius hybrid jobs
## Introduction
### About the course module and hands-on session
In this session, we will dive deeper into the Slurm resource manager, focusing on understanding key parameters for efficient parallel job scheduling, including threads, cores, sockets, nodes, and processes. Our goal is to connect to the Snellius supercomputer and explore hybrid job execution, which leverages both shared-memory (OpenMP) and distributed-memory (MPI) parallelism.

We will explore three basic linear algebra kernels, each with a different parallel nature:
1. **Linear combination of vectors (axpy)**: The operation $$y \gets a * x + y$$, known as *axpy*, is a pointwise operation where each element of the vectors `x` and `y` can be updated independently. This makes it an embarrassingly parallel task, meaning all operations can be executed simultaneously without any inter-task communication.

2. **Dot product (scalar product)**: The dot product of two vectors, $$z \gets \sum_{i=1}^{n} x_i * y_i$$, involves multiplying corresponding elements of two vectors and summing the results. The parallel complexity arises from the need for a reduction operation to sum the products. This requires synchronization between threads or processes to accumulate the intermediate sums.

3. **Matrix multiplication**: The matrix product $$C \gets A * B$$ is more complex, as it involves computing the dot product of rows from matrix `A` with columns from matrix `B`. Efficient parallelization requires distributing the data across multiple nodes or threads, managing both computation and data transfer, which introduces a higher level of parallel complexity compared to vector operations.

The provided materials include two implementations for each kernel:
- A **sequential** version to understand the basic functionality.
- A **hybrid** version combining shared-memory (OpenMP) and distributed-memory (MPI) parallelization.

The main objective is to gain practical experience in running hybrid jobs on supercomputing systems, focusing on the challenges and strategies for parallelizing different computations.

You can find the materials and example codes in the linked repository. This document will guide you through the exercises step by step.

### Snellius supercomputer
We will work with a small subset of the Snellius supercomputer, a powerful system with a total computational performance of 37.9 petaFLOPS. Snellius consists of over 1,500 compute nodes interconnected via a high-speed InfiniBand network. The system is equipped with a variety of processors and GPUs, including AMD Genoa CPUs and NVIDIA H100 GPUs, optimized for tasks ranging from high-performance scientific computing to AI workloads.

Snellius features a range of node types:
- **Thin nodes**: 1,263 nodes with AMD Rome or Genoa CPUs, each containing either 128 or 192 CPU cores, for a total of over 208,000 cores.
- **Fat nodes**: 120 nodes, each with 1 TiB or 1.5 TiB of RAM, intended for memory-intensive jobs.
- **High-memory nodes**: 4 nodes with up to 64 GiB of RAM, intended for extremely memory-intensive jobs.
- **GPU nodes**: 160 nodes equipped with 4 NVIDIA A100 or H100 GPUs per node, designed for massively parallel computations such as machine learning and molecular dynamics.

The front-end nodes of the cluster are accessed via `snellius.surf.nl`, and all job submissions and resource management are handled through Slurm. For additional details on the system, you can refer to the [SURF User Knowledge Base](https://servicedesk.surf.nl/wiki/display/WIKI/Snellius) or explore the [Snellius virtual tour](https://visualization.surf.nl/snellius-virtual-tour/) for a more interactive overview.

### Connecting to Snellius
Since this module is part of the third section in the *Introduction to Supercomputing* course series, we assume that participants already have established connections to Snellius and are familiar with the system, including moving data and interacting with the filesystem. 

However, if needed, you can refer to the following guides for assistance:
- [Connecting to the system](https://servicedesk.surf.nl/wiki/display/WIKI/Connecting+to+the+system).
- [Interacting with the filesystem](https://servicedesk.surf.nl/wiki/display/WIKI/Interacting+with+the+filesystem).

### Snellius environment modules
In a high-performance computing (HPC) cluster, users require access to a variety of software tools, libraries, compilers, and applications. These resources can include various versions of the same software or distinct installations tailored for different hardware architectures. Consequently, managing these resources effectively becomes essential to ensure that users can select the appropriate version and avoid potential conflicts that might arise from incompatible installations.

The environment modules provide a robust solution for this purpose. It allows users to dynamically load and unload specific software modules into their environment, tailoring it to their particular computational needs. By doing so, users can seamlessly switch between different software versions or configurations without the risk of interference between them. 

The advantages of using the `module` command include:
- **Version management**: Users can easily switch between different versions of a software package, ensuring that they run their applications with the correct dependencies and optimizations suited for their particular task.
- **Hardware compatibility**: The cluster may contain software installations optimized for specific hardware, such as GPUs or multi-core CPUs. The `module` system allows users to load the necessary versions that take advantage of the available hardware.
- **Environment configuration**: The `module` command simplifies the setup process by providing an easy interface to manage software dependencies and configurations. This ensures that users can focus on their computations rather than dealing with environment management.

Basic options for the `module` command are listed in the table below.
| Command          | Description                                                                    |
|------------------|--------------------------------------------------------------------------------|
| `module help`    | Provides information about the command options                                 |
| `module avail`   | Displays all modules available in the system                                   |
| `module list`    | Shows the modules currently loaded in your environment                         |
| `module load`    | Loads a new module into your environment                                       |
| `module unload`  | Removes a module from your environment                                         |
| `module purge`   | Removes all modules from your environment                                      |

#### Example
In this example, you will load the necessary software modules in a Slurm job script and verify that the modules have been loaded correctly by outputting the version of the compiler.

First, **create a Slurm script** named `load_modules.sh` with the following content:
```bash
#!/bin/bash
#SBATCH -J load_modules         # Job name
#SBATCH -o load_modules.out     # Output file
#SBATCH --nodes 1               # Number of nodes
#SBATCH --ntasks 1              # Number of tasks
#SBATCH -t 01:00:00             # Time limit

# Load the necessary modules
module load 2023                # Load the general 2023 module
module load foss/2023a          # Load the foss compiler module

# Verify the loaded modules by checking the version of the compiler
echo "Loaded modules:"
module list                     # Display currently loaded modules

echo "Checking compiler version:"
mpicc -v                        # Output the version of the MPI C compiler
```

**Submit the Slurm job** to the cluster by executing the following command:
```bash
sbatch load_modules.sh
```

**Verify the output** by checking the contents of `load_modules.out` after the job completes. This file will contain:
- A list of the currently loaded modules
- The version information of the MPI C compiler
   
```bash
cat load_modules.out
```

By completing this exercise, you will have successfully loaded the required software modules in a SLURM job script and verified that they are functioning as expected.
