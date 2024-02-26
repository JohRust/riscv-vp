#include <vector>
#include <cstdint>

void replaceValues(std::vector<float>& array, const std::vector<bool>& mask, std::vector<float>& newValues);

uint32_t binomialCoeff(uint32_t n, uint32_t k);

// TODO: Extract requests and make 
void explainPrediction(const std::vector<float>& input_data, std::vector<float>& shapley_values);