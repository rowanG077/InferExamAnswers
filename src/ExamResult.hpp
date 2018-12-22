#pragma once

#include <cstdint>
#include <vector>

/**
 * @brief Contains code for the InferExamAnswers problem
 */
namespace InferExamAnswers
{
/**
 * @brief ExamResult class that contains the result of a single exam
 */
class ExamResult
{
public:
	/**
	 * @brief Delete constructor
	 */
	ExamResult() = delete;

	/**
	 * @brief Default virtual destructor
	 */
	virtual ~ExamResult() = default;

	/**
	 * @brief Delete copy constructor
	 * \param b
	 */
	ExamResult(const ExamResult& b) = default;

	/**
	 * @brief Default move constructor
	 * \param b
	 */
	ExamResult(ExamResult&& b) = default;

	/**
	 * @brief Default copy assignment operator
	 * \param b
	 * \return
	 */
	ExamResult& operator=(const ExamResult& b) = default;

	/**
	 * @brief Default move assignment operator
	 * \param b
	 * \return
	 */
	ExamResult& operator=(ExamResult&& b) = default;

	/**
	 * @brief Construct a new Exam Result object
	 *
	 * @param examAnswers Rvalue of the exam answers
	 * @param score The associated score
	 * @return New constructed examResult object
	 */
	ExamResult(std::vector<int8_t>&& examAnswers, int8_t score);

	/**
	 * @brief Get the exam answers
	 *
	 * @return Vector containing the exam answers
	 */
	[[nodiscard]] const std::vector<int8_t>& getExamAnswers() const;

	/**
	 * @brief Get the associated score for this exame
	 *
	 * @return The score
	 */
	[[nodiscard]] int8_t getScore() const;

private:
	/**
	 * @brief Contains the sequence of answers for an exam
	 */
	std::vector<int8_t> examAnswers;

	/**
	 * @brief Contains the total score for this set of exam answers
	 */
	int8_t score;
};
} // InferExamAnswers
