extern "C"  __global__ void fill(int * A, int cnt){
	const int gap = blockDim.x*gridDim.x;
	for (int id = blockDim.x*blockIdx.x + threadIdx.x; id < cnt; id += gap)
		A[id] = id * 2;
};
