# Snellius hybrid jobs
## Introduction
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

## Snellius supercomputer
We will work with a small subset of the Snellius supercomputer, a powerful system with a total computational performance of 37.9 petaFLOPS. Snellius consists of over 1,500 compute nodes interconnected via a high-speed InfiniBand network. The system is equipped with a variety of processors and GPUs, including AMD Genoa CPUs and NVIDIA H100 GPUs, optimized for tasks ranging from high-performance computing to AI workloads.

Snellius features a range of node types:
- **Thin nodes**: 1,263 nodes with AMD Rome or Genoa CPUs, each containing either 128 or 192 CPU cores, for a total of over 208,000 cores.
- **Fat nodes**: 120 nodes, each with 1 TiB or 1.5 TiB of RAM, intended for memory-intensive jobs.
- **High-memory nodes**: 4 nodes with up to 64 GiB of RAM, intended for extremely memory-intensive jobs.
- **GPU nodes**: 160 nodes equipped with 4 NVIDIA A100 or H100 GPUs per node, designed for massively parallel computations such as machine learning and molecular dynamics.

The front-end nodes of the cluster are accessed via `snellius.surf.nl`, and all job submissions and resource management are handled through Slurm. For additional details on the system, you can refer to the [SURF User Knowledge Base](https://servicedesk.surf.nl/wiki/display/WIKI/Snellius) or explore the [Snellius virtual tour](https://visualization.surf.nl/snellius-virtual-tour/) for a more interactive overview.
