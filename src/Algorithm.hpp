#pragma once

#include <cstdint>
#include <list>
#include <unordered_map>
#include <vector>

/**
 * @brief Contains code for the InferExamAnswers problem
 */
namespace InferExamAnswers
{

struct VectorHash {
	size_t operator()(const std::vector<int8_t>& v) const {
		std::hash<int> hasher;
		size_t seed = 0;
		for (int i : v) {
			seed ^= hasher(i) + 0x9e3779b9 + (seed << 6u) + (seed >> 2u);
		}
		return seed;
	}
};

/**
 * @brief Algorithm class that contains the algorithm to get the exam solution
 */
class Algorithm
{
public:
	/**
	 * @brief Map that contains the score of each student as a key and the value is the associated solution
	 */
	using ScoreMap = std::unordered_map<std::vector<int8_t>, std::list<std::vector<int8_t>>, VectorHash>;

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
	 * @param answers The answers given by each student
	 * @param scores The scores associated with each answer
	 * @return  
	 */
	[[nodiscard]] static std::list<std::vector<int8_t>> runAlgorithm(
		const std::vector<std::vector<int8_t>>& answers,
		const std::vector<int8_t>& scores);

	/**
	 * @brief Generate the next bit sequence given the current sequence
	 * 
	 * @param currentSequence the current sequence to get the successor for
	 * @return Return false if the the end of the sequence has been reached
	 */
	[[nodiscard]] static bool generateNextBitSequence(std::vector<int8_t>& currentSequence);

	/**
	 * @brief Compute a scoreMap for a split part of the exams
	 * 
	 * @param exams The exams
	 * @param n The lower limit which answers to use to compute the map
	 * @param m The upper limit which answers to use to compute the map
	 * @return The resulting map containing a vector of scores as keys with the associated solution
	 */
	[[nodiscard]] static ScoreMap computeScoreMap(
		const std::vector<std::vector<int8_t>>& answers,
		const std::vector<int8_t>& scores,
		int8_t n, int8_t m);

	/**
	 * @brief Calculate the score for an answer given by a student a with a subset of an exam solution
	 * 
	 * @param studentAnswer The vector of answer a student has given
	 * @param examSolution The proposed solution to check the score for
	 * @param n The start index of the exam solution that should be checked with the studentAnswer
	 * @param m The end index of the exam solution that should be checked with the studentAnswer
	 * @return The score the student has obtained for the subset
	 */
	[[nodiscard]] static int8_t calculateScore(
		const std::vector<int8_t>& studentAnswer,
		const std::vector<int8_t>& examSolution,
		int8_t n, int8_t m);

};
} // InferExamAnswers
