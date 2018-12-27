#pragma once

#include <cstdint>
#include <valarray>

/**
 * @brief Contains code for the InferExamAnswers problem
 */
namespace InferExamAnswers
{
/**
 * @brief Contains the results of the exam
 */
struct ExamResults
{
	/**
	 * @brief Contains the answers of each student represented as a single number
	 *        Note that only the bits upto questionCount are used.
	 */
	std::valarray<uint64_t> answers;

	/**
	 * @brief Contains the scores of each student
	 */
	std::valarray<uint8_t> scores;

	/**
	 * @brief The number of questions for the exam
	 */
	uint8_t questionCount;

	/**
	 * @brief The number of students that took the exam
	 */
	uint8_t studentCount;
};

} // InferExamAnswers
