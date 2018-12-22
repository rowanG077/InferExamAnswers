
#include "ExamResult.hpp"

/**
 * @brief Contains code for the InferExamAnswers problem
 */
namespace InferExamAnswers
{
ExamResult::ExamResult(std::vector<int8_t>&& examAnswers, int8_t score) : examAnswers(examAnswers), score(score)
{
}

const std::vector<int8_t>& ExamResult::getExamAnswers() const
{
	return this->examAnswers;
}

int8_t ExamResult::getScore() const
{
	return this->score;
}

} // InferExamAnswers
