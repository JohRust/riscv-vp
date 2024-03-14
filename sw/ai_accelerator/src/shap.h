#pragma once

#include <vector>
#include <cstdint>

/**
 * Replaces values in the given array based on the provided mask and new values.
 *
 * @param array The array of float values to be modified.
 * @param mask The mask indicating which values in the array should be replaced.
 * @param newValues The new values to replace the masked values in the array.
 */
void replaceValues(std::vector<float>& array, const std::vector<bool>& mask, const std::vector<float>& newValues);

/**
 * Calculates the factorial of a given number.
 * 
 * @param n The number for which the factorial is to be calculated.
 * @return The factorial of the given number. Returns -1 if the number is greater than 20.
 */
uint64_t factorial(uint64_t n);


/**
 * Creates a new vector by sampling each feature from a vector in the input data.
 * @param data The input data vector.
 * @return A random vector sampled from the input data.
*/
std::vector<float> sampleFromData(const std::vector<std::vector<float>> data);

/**
 * Calculates the binomial coefficient.
 *
 * @param n The total number of elements.
 * @param k The number of elements in the subset.
 * @return The binomial coefficient.
 */
uint32_t binomialCoeff(uint32_t n, uint32_t k);

/**
 * Calculates the frequency of feature i in the Shapley value calculation.
 *
 * @param n The total number of features.
 * @param s The number of features in the subset.
 * @return The frequency of feature i in the Shapley value calculation.
 */
float shapleyFrequency(uint32_t n, uint32_t s);

/**
 * Calculates the marginal contribution of a feature in the input data based on a given mask.
 * 
 * @param input_data The input data vector.
 * @param mask The mask vector indicating which elements of the input data should be masked.
 * @return The marginal contribution of the feature.
 */
float marginalContribution(const std::vector<float>& input_data, const std::vector<bool>& mask);

/**
 * Explains the prediction of the model by calculating the Shapley value of every value in the input data.
 * 
 * @param input_data The input data vector.
 * @param func The function to be used for prediction.
 * @param background_data The background data vector. Optional, defaults to a vector of zeros.
 * @return The vector to store the Shapley values in.
 */
std::vector<float> explainPrediction(std::vector<float> input_data, float (func)(const float*, unsigned int), std::vector<std::vector<float>> background_data);
std::vector<float> explainPrediction(std::vector<float> input_data, float (func)(const float*, unsigned int));

/**
 * Get a binary representation of n as a vector of bools.
 * E.g. getAsBoolVector(5, 3) -> 101 -> {true, false, true}
 * This is an easy way to get masks for all subsets of a set.
 * If you have a set of n elements, there are 2^n subsets.
 * So calling this function with 0...(n-1) will give you all subsets.
 *
 * @param n The number to convert to a binary representation.
 * @param length The length of the binary representation.
 * @return A vector of bools representing the binary representation of n.
 */
std::vector<bool> getAsBoolVector(uint32_t n, uint16_t length);
