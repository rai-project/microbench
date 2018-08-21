
#include <tuple>

#include "optional/optional.hpp"

#include "flags.hpp"
#include "init.hpp"
#include "logger.hpp"
#include "cuda.hpp"

bool has_cuda = false;
cudaDeviceProp cuda_device_prop;
int device_count = 0;

int num_gpus() {
  return device_count;
}

// using optional = std::experimental::optional;
// using nullopt = std::experimental::nullopt;

static float device_giga_bandwidth{0};
static size_t device_free_physmem{0};
static size_t device_total_physmem{0};

bool init_cuda() {

  if (PRINT_IF_ERROR(cudaGetDeviceCount(&device_count))) {
    return false;
  }

  if (device_count == 0) {
    LOG(critical, "No devices supporting CUDA.");
    exit(1);
  }

  has_cuda = true;

  if (FLAG(cuda_device_id) < 0) {
    LOG(critical, "device = {} is not valid.", FLAG(cuda_device_id));
    exit(1);
  }
  if ((FLAG(cuda_device_id) > device_count - 1) || (FLAG(cuda_device_id) < 0)) {
    FLAG(cuda_device_id) = 0;
  }

  if (PRINT_IF_ERROR(cudaSetDevice(FLAG(cuda_device_id)))) {
    return false;
  }

  if (PRINT_IF_ERROR(cudaMemGetInfo(&device_free_physmem, &device_total_physmem))) {
    return false;
  }

  if (PRINT_IF_ERROR(cudaGetDeviceProperties(&cuda_device_prop, FLAG(cuda_device_id)))) {
    return false;
  }

  if (cuda_device_prop.major < 1) {
    LOG(critical, "Device does not support CUDA.");
    exit(1);
  }

  device_giga_bandwidth =
      float(cuda_device_prop.memoryBusWidth) * cuda_device_prop.memoryClockRate * 2 / 8 / 1000 / 1000;

  return false;
}

std::experimental::optional<std::tuple<size_t, size_t>> mem_info() {
  size_t device_free_physmem, device_total_physmem;

  if (PRINT_IF_ERROR(cudaMemGetInfo(&device_free_physmem, &device_total_physmem))) {
    return std::experimental::nullopt;
  }
  return std::make_tuple(device_free_physmem, device_total_physmem);
}