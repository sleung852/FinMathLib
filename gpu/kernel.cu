#include "kernel.h"
#include <stdexcept>
#include <algorithm>
#include <math.h>

// declare function to be ran in the GPU
__global__ void monte_carlo_sim(double* d_St, const double* d_Zs, double d_drift, double d_sigma,
	double d_deltaT, int d_n, int d_m) {

    // create stock_index
    int idx = threadIdx.x + blockIdx.x * blockDim.x;

    // for each simluated stock
    if (idx < d_m) {
		int t = 0;
		while (t < d_n) {
    		// compute stock price from previous stock price 
    		d_St[idx] = d_St[idx] * d_drift * exp((d_sigma) * sqrt(d_deltaT) * d_Zs[idx*(d_n) + t]);
			t++;
    	}
    }
}

// function to setup running Monte Carlo Simulation in the GPU
void run_mc_cuda(double* ST, double S, double sigma, double rate, double T, int n,
	int m, double* Zs) {

	// assign values in the CPU
	double deltaT = T/n;
	double drift = exp((rate - 0.5*(pow(sigma, 2.0)))*T/n);
	for (size_t i=0; i<m; i++) ST[i] = S; 

	// declarations for variables in the GPU
	//array
	double* d_St = nullptr;
	double* d_Zs = nullptr;

	// allocations in GPU (device) global memory
	cudaMalloc((void **) &d_Zs, n*m*sizeof(double));
	cudaMalloc((void **) &d_St, m*sizeof(double));
	// copy values from host (CPU) to device (GPU)
	cudaMemcpy(d_Zs, Zs, n*m*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(d_St, ST, m*sizeof(double), cudaMemcpyHostToDevice);

	// Use 1024 for THREADS_PER_BLOCK
	int TPB = 1024;
	
	// invoke the Monte Carlo kernel
	monte_carlo_sim<<<(m+TPB-1)/TPB,TPB>>>(d_St, d_Zs, drift, sigma, deltaT, n, m);

	// copy the results from the device (GPU) back to the host (CPU)
	cudaMemcpy(ST, d_St, m*sizeof(double), cudaMemcpyDeviceToHost);

	// free device memory
	cudaFree(d_Zs);
	cudaFree(d_St);
}
