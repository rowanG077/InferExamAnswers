#include "Algorithm.hpp"

#include <iostream>


namespace InferExamAnswers
{

void printBinary(uint64_t s) // NOLINT
{
	for (size_t i = 0; i < 64; ++i)
	{
		std::cout << ((s >> (63 - i)) & 1U);
	}
}

std::list<uint64_t> Algorithm::runAlgorithm(const ExamResults& examResults)
{
	uint8_t answersLeft = examResults.questionCount / 2;
	uint8_t answersRight = examResults.questionCount - answersLeft;

	const auto leftScores = computeScoreMap(examResults, 0, answersLeft);
	const auto rightScores = computeScoreMap(examResults, answersLeft, examResults.questionCount);

	std::list<uint64_t> solutions;

	// Fuse results
	for (const auto& [leftScore, leftSolutions] : leftScores)
	{
		std::valarray<uint8_t> rightKey = examResults.scores - leftScore;

		auto it = rightScores.find(rightKey);
		if (it == rightScores.end())
		{
			continue;
		}

		auto& rightSolutions = it->second;

		// we only actuallly add the solutions here if the cardinality of the cartesian
		// product is 1 since if it is larger we aren't interested in the actual solution
		// just the number of them and then we can just add dummy solutions
		auto combinationCount = leftSolutions.size() * rightSolutions.size();
		if (combinationCount == 1)
		{
			uint64_t solution = (static_cast<uint64_t>(leftSolutions.front()) << answersRight) | static_cast<uint64_t>(rightSolutions.front());
			solutions.emplace_front(solution);
		}
		else
		{
			solutions.resize(solutions.size() + combinationCount);
		}
	}

	return solutions;
}

Algorithm::ScoreMap Algorithm::computeScoreMap(const ExamResults& examResults, uint8_t n, uint8_t m)
{
	ScoreMap scoreMap;

	// Compute the length of the answers to create for the current partition
	// and for the other partition
	uint8_t currentSequenceLength = m - n;
	uint8_t otherSequenceLength = examResults.questionCount - currentSequenceLength;



	/**
	 * If the length is 0 it would mean no answers are created to check
	 * however if the length is - then every has a score of 0 with a
	 * solution that has no answers
	 */
	if (currentSequenceLength == 0)
	{
		std::cout << "Empty sequnce putting en lambda solution" << std::endl;
		std::valarray<uint8_t> score(examResults.studentCount);
		scoreMap[score] = std::list<uint32_t>{ 0 };
		return scoreMap;
	}

	/**
	 * We create every possible answer sheet from 0 to 2^n  
	 */
	auto maxBitToCheck = 1UL << currentSequenceLength;
	for (uint32_t i = 0; i < maxBitToCheck; ++i)
	{
		std::cout << "testing guess: ";
		printBinary(i);
		std::cout << std::endl;

		auto keepSequence = true;
		std::valarray<uint8_t> score(examResults.studentCount);

		for (uint8_t j = 0; j < examResults.studentCount; ++j)
		{
			score[j] = (examResults.answers[j] << n) & i;
			std::cout << "Exam answer raw, bitMoved, anded" << std::endl;
			printBinary(examResults.answers[j]);
			std::cout << std::endl;
			printBinary(examResults.answers[j] << n);
			std::cout << std::endl;
			printBinary(score[j]);
			std::cout << std::endl;
			
			if (score[j] < examResults.scores[j] - otherSequenceLength || score[j] > examResults.scores[j])
			{
				keepSequence = false;
				break;
			}
		}

		if (!keepSequence)
		{
			continue;
		}

		auto it = scoreMap.find(score);
		if (it != scoreMap.end())
		{
			it->second.emplace_front(i);
		}
		else
		{
			scoreMap[score] = std::list<uint32_t>{ i };
		}
	}

	return scoreMap;
}

} // InferExamAnswers
