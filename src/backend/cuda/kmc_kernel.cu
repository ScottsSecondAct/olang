// KMC Gillespie kernel — see include/olang/runtime/bio/IsletState.h
#include <cuda_runtime.h>
#include <curand_kernel.h>
#include <cstdint>

namespace rates {
  static constexpr float kTCR_on  = 1.0e5f, kTCR_off  = 1.0e-3f;
  static constexpr float kPDL1_on = 5.0e4f, kPDL1_off = 2.0e-3f;
  static constexpr float kAnergyThreshold = 0.7f;
}

struct IsletDelta {
  uint32_t threadId, betaCellIdx, tCellIdx;
  float newPDL1Surface, newMHC1Surface;
  uint8_t newTCellState;
  float simTimeAdvance;
};

__global__ void kmc_init_rng(curandState* states, uint64_t seed, uint32_t n) {
  uint32_t tid = blockIdx.x * blockDim.x + threadIdx.x;
  if (tid < n) curand_init(seed, tid, 0, &states[tid]);
}

__global__ void kmc_gillespie_step(
    const void* /*baseline*/, IsletDelta* deltas,
    curandState* rng, uint32_t nSims,
    uint32_t betaCellIdx, uint32_t tCellIdx,
    float pdl1, float mhc1, float affin, uint8_t currentState)
{
  uint32_t tid = blockIdx.x * blockDim.x + threadIdx.x;
  if (tid >= nSims) return;

  curandState localRng = rng[tid];
  float a_tcr  = rates::kTCR_on * mhc1 * affin;
  float a_untcr = rates::kTCR_off;
  float a_pdl1 = rates::kPDL1_on * pdl1;
  float a_tot  = a_tcr + a_untcr + a_pdl1;

  float dt = (a_tot < 1e-12f) ? 0.0f : -__logf(curand_uniform(&localRng)) / a_tot;
  float sel = curand_uniform(&localRng) * a_tot;

  uint8_t newState = currentState;
  if (a_tot >= 1e-12f) {
    if      (sel < a_tcr)           newState = (pdl1 > rates::kAnergyThreshold) ? 3 : 2;
    else if (sel < a_tcr + a_untcr) newState = 0;
  }

  deltas[tid] = {tid, betaCellIdx, tCellIdx, pdl1, mhc1, newState, dt};
  rng[tid] = localRng;
}

extern "C" void launch_kmc_step(
    const void* d_baseline, IsletDelta* d_deltas, curandState* d_rng,
    uint32_t nSims, uint32_t betaIdx, uint32_t tIdx,
    float pdl1, float mhc1, float affin, uint8_t state,
    cudaStream_t stream)
{
  constexpr uint32_t kBlock = 256;
  kmc_gillespie_step<<<(nSims+kBlock-1)/kBlock, kBlock, 0, stream>>>(
      d_baseline, d_deltas, d_rng, nSims, betaIdx, tIdx, pdl1, mhc1, affin, state);
}
