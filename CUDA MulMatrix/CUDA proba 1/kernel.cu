#include <cuda_runtime.h>
#include <cstdlib>
#include <cuda.h>
#include <device_launch_parameters.h>
#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

__global__ void MatrixMul(int *a, int *b, int *c, int N) {
	//Calculate the global row and colomn for each thread
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;


	if (row < N && col < N) {
		int temp = 0;
		for (int i = 0; i < N; i++) {
			temp += a[row * N + i] * b[i * N + col];
		}

		//Write back the resolt
		c[row * N + col] = temp;
	}
}

void CreateMatrix(int *a, int N) {
	for (int i = 0; i < N * N; i++)
		a[i] = rand() % 100;
}

clock_t Test(int N) {
	
	size_t bytes = N * N * sizeof(int);
	clock_t clocks;

	//Alocate memory
	int* a, * b, * c;

	cudaMallocManaged(&a, bytes);
	cudaMallocManaged(&b, bytes);
	cudaMallocManaged(&c, bytes);

	//Create matrix
	CreateMatrix(a, N);
	CreateMatrix(b, N);


	//Set CTA and grid dimension
	int threads = 16;
	int blocks = (N + threads - 1) / threads;

	dim3 THREADS(threads, threads);
	dim3 BLOCKS(blocks, blocks);

	clocks = clock();
	MatrixMul <<<BLOCKS, THREADS >>> (a, b, c, N);
	cudaDeviceSynchronize();
	clocks = clock() - clocks;

	cout << "Program completed successfully " << endl;
	cout << "Dimension: "<< N << " Clocks: " << clocks << " Time: " << (double)clocks / CLOCKS_PER_SEC << endl;

	cudaFree(a);
	cudaFree(b);
	cudaFree(c);

	return clocks;
}

int main() {
	int i = 0;
	cout << " PRogram starting " << i << endl;
	clock_t clk;
	ofstream resolt;
	resolt.open("resolt.txt");

	while (i <= 10000) {
		clk = Test(i);
		resolt << i << " " << clk << " " << (double)clk / CLOCKS_PER_SEC << endl;
		if (i < 100)
			i += 10;
		else if (i < 1000)
			i += 100;
		else
			i += 1000;
	}
	resolt.close();
	return 0;
}