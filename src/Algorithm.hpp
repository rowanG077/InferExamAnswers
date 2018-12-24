#pragma once

#include "ExamResults.hpp"
#include "SolutionCollection.hpp"

#include <cstdint>
#include <unordered_map>

/**
 * @brief Contains code for the InferExamAnswers problem
 */
namespace InferExamAnswers
{

struct ScoreValarrayHash {
	size_t operator()(const std::valarray<uint8_t>& v) const {
		size_t hash = 0;
		for (uint8_t i = 0; i < v.size(); ++i)
		{
			hash |= v[i] << (5U * i);
		}
		return hash;
	}
};

struct ScoreValarrayEqual {
	bool operator()(const std::valarray<uint8_t>& a, const std::valarray<uint8_t>& b) const {
		for (size_t i = 0; i < a.size(); ++i)
		{
			if (a[i] != b[i])
			{
				return false;
			}
		}

		return true;
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
	using ScoreMap = std::unordered_map<std::valarray<uint8_t>, SolutionCollection, ScoreValarrayHash, ScoreValarrayEqual>;

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
	[[nodiscard]] static SolutionCollection runAlgorithm(const ExamResults& examResults);

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
