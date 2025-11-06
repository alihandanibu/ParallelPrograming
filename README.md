# Vectorization Assignment

## Build commands:
```bash
mkdir build && cd build
cmake ..
make
cat > timestep.h << 'EOF'
#ifndef TIMESTEP_H
#define TIMESTEP_H

double timestep(int ncells, double g, double sigma, int* celltype,
                double* H, double* U, double* V, double* dx, double* dy);

#endif
