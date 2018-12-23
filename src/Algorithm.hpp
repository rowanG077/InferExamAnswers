#pragma once

#include "ExamResults.hpp"

#include <cstdint>
#include <list>
#include <unordered_map>
#include <vector>

/**
 * @brief Contains code for the InferExamAnswers problem
 */
namespace InferExamAnswers
{

struct ValarrayHash {
	size_t operator()(const std::valarray<uint8_t>& v) const {
		std::hash<uint8_t> hasher;
		size_t seed = 0;
		for (auto i : v) {
			seed ^= hasher(i) + 0x9e3779b9 + (seed << 6u) + (seed >> 2u);
		}
		return seed;
	}
};

struct ValarrayEqual {
	bool operator()(const std::valarray<uint8_t>& a, const std::valarray<uint8_t>& b) const {
		bool equals = true;

		for (size_t i = 0; i < a.size(); ++i)
		{
			equals &= a[i] == b[i];
			if (!equals)
			{
				break;
			}
		}

		return equals;
	}
};

/**
 * @brief Algorithm class that contains the algorithm to get the exam solution
 */
class Algorithm
{
public:
	/**
	 * @brief Map that contains the score of each student as a key and the value are the associated solutions
	 */
	using ScoreMap = std::unordered_map<std::valarray<uint8_t>, std::list<uint32_t>, ValarrayHash, ValarrayEqual>;

	/**
	 * @brief Deleted constructor
	 */
	Algorithm() = delete;

	/**
	 * @brief Deleted virtual destructor
	 */
	virtual ~Algorithm() = delete;

	/**
	 * @brief Deleted copy constructor
	 * \param b
	 */
	Algorithm(const Algorithm& b) = delete;

	/**
	 * @brief Deleted move constructor
	 * \param b
	 */
	Algorithm(Algorithm&& b) = delete;

	/**
	 * @brief Deleted copy assignment operator
	 * \param b
	 * \return
	 */
	Algorithm& operator=(const Algorithm& b) = delete;

	/**
	 * @brief Deleted move assignment operator
	 * \param b
	 * \return
	 */
	Algorithm& operator=(Algorithm&& b) = delete;

	/**
	 * @brief Run the algorithm to find all possible exam answers
	 * 
	 * @param examResults The results of the exam
	 * @return The possible results
	 */
	[[nodiscard]] static std::list<uint64_t> runAlgorithm(const ExamResults& examResults);

	/**
	 * @brief Compute a scoreMap for a part of the exam. The part that is computed is indicated by indices n and m
	 * 
	 * @param examResults The results of the exam
	 * @param n The start index of the examResults partition
	 * @param m The end index of the examResults partition
	 * @return The resulting scoreMap
	 */
	[[nodiscard]] static ScoreMap computeScoreMap(const ExamResults& examResults, uint8_t n, uint8_t m);

};
} // InferExamAnswers
