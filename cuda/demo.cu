#include <cuda_runtime.h>

#include <chrono>
#include <iostream>
#include <memory>
#include <random>

__global__ void vectorAdd(const float* A, const float* B, float* C,
                          int numElements)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;

    if (i < numElements) {
        C[i] = A[i] + B[i] + 0.0f;
    }
}

template <typename T> class CudaMemory {
public:
    explicit CudaMemory(std::size_t num)
    {
        auto err = cudaMalloc((void**)&p_, num * sizeof(T));
        if (err != cudaSuccess) {
            std::cerr << "Failed to allocate device: "
                      << cudaGetErrorString(err) << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    ~CudaMemory()
    {
        auto err = cudaFree(p_);

        if (err != cudaSuccess) {
            std::cerr << "Failed to free device: " << cudaGetErrorString(err)
                      << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    T* get() { return p_; }

private:
    T* p_ {};
};

template <typename T>
void memcpy_gpu(T* dst, T* src, std::size_t size, enum cudaMemcpyKind kind)
{
    auto err = cudaMemcpy(dst, src, size, kind);
    if (err != cudaSuccess) {
        std::cerr << "Failed to memcpy device: " << cudaGetErrorString(err)
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int main()
{
    cudaError_t err = cudaSuccess;

    int num = 50000;
    size_t size = num * sizeof(float);
    std::cout << "num: " << num << std::endl;

    auto h_A = std::unique_ptr<float[]>(new float[num]);
    auto h_B = std::unique_ptr<float[]>(new float[num]);
    auto h_C = std::unique_ptr<float[]>(new float[num]);

    std::default_random_engine generator(
        std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(1, 100);

    for (int i = 0; i < num; ++i) {
        h_A[i] = float(distribution(generator)) / (float)100;
        h_B[i] = float(distribution(generator)) / (float)100;
    }

    // Allocate the device input vector A
    CudaMemory<float> d_A { static_cast<size_t>(num) };
    CudaMemory<float> d_B { static_cast<size_t>(num) };
    CudaMemory<float> d_C { static_cast<size_t>(num) };

    std::cout << "Copy input data from the host memory to the CUDA device"
              << std::endl;
    memcpy_gpu(d_A.get(), h_A.get(), size, cudaMemcpyHostToDevice);
    memcpy_gpu(d_B.get(), h_B.get(), size, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (num + threadsPerBlock - 1) / threadsPerBlock;
    printf("CUDA kernel launch with %d blocks of %d threads\n", blocksPerGrid,
           threadsPerBlock);
    vectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A.get(), d_B.get(),
                                                  d_C.get(), num);
    err = cudaGetLastError();

    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to launch vectorAdd kernel (error code %s)!\n",
                cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    memcpy_gpu(h_C.get(), d_C.get(), size, cudaMemcpyDeviceToHost);

    for (int i = 0; i < num; ++i) {
        if (fabs(h_A[i] + h_B[i] - h_C[i]) > 1e-5) {
            fprintf(stderr, "Result verification failed at element %d!\n", i);
            exit(EXIT_FAILURE);
        }
    }

    std::cout << "done" << std::endl;

    return 0;
}