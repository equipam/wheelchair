#include "FIRfilter.h"

float* FIRFilterInput(FilterInput<float>& input){

  const auto* x = input.x;
  const auto* c = input.c;
  auto* y = input.y;

  for (auto i = 0u; i < input.outputLength; ++i) {
    y[i] = x[i] * c[0];
    for (auto j = 1u; j < input.filterLength; ++j) {
      y[i] += x[i + j] * c[j];
    }
  }
  return input.output();

}
