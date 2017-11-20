#include <assert.h>
#include <benchmark/benchmark.h>
#include <cuda_runtime.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

static void CUDAMemcpyToGPU(benchmark::State &state) {
  const auto bytes = 1ULL << static_cast<size_t>(state.range(0));
  char *src = new char[bytes];
  char *dst = nullptr;
  const auto err = cudaMalloc(&dst, bytes);
  if (err != cudaSuccess) {
    state.SkipWithError("failed to perform cudaMemcpy");
    return;
  }
 //for (auto _ : state) {
 //  const auto err = cudaMemcpy(dst, src, bytes, cudaMemcpyHostToDevice);
 //  if (err != cudaSuccess) {
 //    state.SkipWithError("failed to perform cudaMemcpy");
 //    break;
 //  }
 //}
  for (auto _ : state) {
    cudaMemcpy(dst, src, bytes, cudaMemcpyHostToDevice);
  }
  state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(bytes));
  state.counters.insert({{"bytes", bytes}});
  if (dst) {
    cudaFree(dst);
  }
  delete[] src;
}
BENCHMARK(CUDAMemcpyToGPU)->DenseRange(1, 32, 1);

static void CUDAPinnedMemcpyToGPU(benchmark::State &state) {
  const auto bytes = 1ULL << static_cast<size_t>(state.range(0));
  char *src = nullptr;
  auto err = cudaHostAlloc(&src, bytes, cudaHostAllocWriteCombined);
  if (err != cudaSuccess) {
    state.SkipWithError("failed to perform pinned cudaHostAlloc");
    return;
  }
  char *dst = nullptr;
  err = cudaMalloc(&dst, bytes);
  if (err != cudaSuccess) {
    state.SkipWithError("failed to perform cudaMalloc");
    return;
  }
  for (auto _ : state) {
    const auto err = cudaMemcpy(dst, src, bytes, cudaMemcpyHostToDevice);
    if (err != cudaSuccess) {
      state.SkipWithError("failed to perform pinned cudaMemcpy");
      break;
    }
  }
  state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(bytes));
  state.counters.insert({{"bytes", bytes}});
  if (src) {
    cudaFree(src);
  }
  if (dst) {
    cudaFree(dst);
  }
}
BENCHMARK(CUDAPinnedMemcpyToGPU)->DenseRange(19, 32, 1);
