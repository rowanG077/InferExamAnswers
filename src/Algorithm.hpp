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
/**
 * @brief We are using a val array as key in an unordered_map so we need
 *        a hash function for it. We can create a perfect hash function
 *        that is always collision free. Since we know we have a maximum
 *        of 12 students and a partition has a maximum of 40/2 = 20
 *        questions we can use 5 bits to store the score for each student.
 *        Since sizeof(size_t) is 64 we can use 60 bits to store a
 *        lossless version of the score. Which means we will never have
 *        a hash collision.
 */
struct ScoreValarrayHash
{
	/**
	 * @brief Get the hash of the valarray containing the score for a partition
	 *
	 * @param v The score valarray
	 * @return The hash
	 */
	size_t operator()(const std::valarray<uint8_t>& v) const
	{
		size_t hash = 0;
		for (uint8_t i = 0; i < v.size(); ++i) {
			hash |= static_cast<size_t>(v[i]) << (5U * i);
		}
		return hash;
	}
};

/**
 * @brief valarray is a weird datatype dat doesn't return a bool with
 *        == operator but a valarray<bool> where the elements are
 *        pairwise compared. For an unordered_map we need a normal
 *        equality so we implement it here.
 */
struct ScoreValarrayEqual
{
	/**
	 * @brief Check if two valarrays contain the same elements
	 *
	 * @param a The first operand
	 * @param b The second operand
	 * @return True if they contain the same elements. False if not
	 */
	bool operator()(const std::valarray<uint8_t>& a, const std::valarray<uint8_t>& b) const
	{
		for (size_t i = 0; i < a.size(); ++i) {
			if (a[i] != b[i]) {
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
	using ScoreMap =
		std::unordered_map<std::valarray<uint8_t>, SolutionCollection, ScoreValarrayHash, ScoreValarrayEqual>;

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
	 * @brief Run the algorithm to find all possible exam solutions
	 *
	 * @param examResults The results of the exam
	 * @return The possible solutions
	 */
	[[nodiscard]] static SolutionCollection runAlgorithm(const ExamResults& examResults);

	/**
	 * @brief Compute a scoreMap for a part of the exam.
	 *        The part that is computed is indicated by indices n and m
	 *
	 * @param examResults The results of the exam
	 * @param n The start index of the examResults partition
	 * @param m The end index of the examResults partition
	 * @return The resulting scoreMap
	 */
	[[nodiscard]] static ScoreMap computeScoreMap(const ExamResults& examResults, uint8_t n, uint8_t m);
};
} // InferExamAnswers
