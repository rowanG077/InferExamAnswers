#include "Algorithm.hpp"

#include <iostream>

#include <sstream>

namespace InferExamAnswers
{

std::string binaryToString(uint64_t s) // NOLINT
{
	std::stringstream ss;
	for (size_t i = 0; i < 64; ++i)
	{
		ss << ((s >> (63 - i)) & 1U);
	}

	return ss.str();
}

std::string scoreToString(const std::valarray<uint8_t>& score)
{
	std::stringstream ss;
	ss << "[";
	for (size_t i = 0; i < score.size(); ++i)
	{
		ss << +score[i];
		if (i + 1 != score.size())
		{
			ss << ", ";
		}
	}

	ss << "]";
	return ss.str();
}

SolutionCollection Algorithm::runAlgorithm(const ExamResults& examResults)
{
	uint8_t splitIndex = examResults.questionCount / 2;

	// std::cout << "computing right scores" << std::endl << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	
	const auto rightScores = computeScoreMap(examResults, 0, splitIndex);
	
	// std::cout << std::endl << "computing left scores" << std::endl << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	
	const auto leftScores = computeScoreMap(examResults, splitIndex, examResults.questionCount);

	// std::cout << "left solutions size: " << leftScores.size() << ", right solutions size: " << rightScores.size() << std::endl;

	SolutionCollection solutions;

	// std::cout << "Total required score: " << scoreToString(examResults.scores) << std::endl;

	// std::cout << "scores in right: " << std::endl;
	// for (const auto& [rightScore, rightSolutions] : rightScores)
	// {
	// 	std::cout << "\t" << scoreToString(rightScore) << ", with number of solutions: " << rightSolutions.getSize() << std::endl;
	// }

	// std::cout << "scores in left: " << std::endl;
	// for (const auto& [leftScore, leftSolutions] : leftScores)
	// {
	// 	std::cout << "\t" << scoreToString(leftScore) << ", with number of solutions: " << leftSolutions.getSize() << std::endl;
	// }

	// Fuse results
	for (const auto& [rightScore, rightSolutions] : rightScores)
	{
		// std::cout << "trying to combine right score " << scoreToString(rightScore) << ", with number of solutions: " << rightSolutions.getSize() << std::endl;

		// std::cout << "with left score so looking for leftScore: " << scoreToString(examResults.scores - rightScore);

		const std::valarray<uint8_t> leftScore = examResults.scores - rightScore;

		auto it = leftScores.find(leftScore);
		if (it == leftScores.end())
		{
			// std::cout << ", Did not find leftScore continueing..." << std::endl;
			continue;
		}

		auto& leftSolutions = it->second;

		// std::cout << ", with number of solutions: " << leftSolutions.getSize() << std::endl;

		// we only actually add the solutions here if the cardinality of the cartesian
		// product is 1 since if it is larger we aren't interested in the actual solution
		// just the number of them so we can just add dummy solutions
		auto combinationCount = leftSolutions.getSize() * rightSolutions.getSize();
		if (solutions.getSize() == 0 && combinationCount == 1)
		{
			uint64_t solution = (leftSolutions.getSolution() << splitIndex) | rightSolutions.getSolution();
			solutions.addSolution(solution);
		}
		else
		{
			solutions.grow(combinationCount);
		}
	}

	return solutions;
}

Algorithm::ScoreMap Algorithm::computeScoreMap(const ExamResults& examResults, uint8_t n, uint8_t m)
{
	/**
	 *  Compute the length of the answers to create for the current partition
	 *  and for the other partition
	 */
	uint8_t currentSequenceLength = m - n;
	uint8_t otherSequenceLength = examResults.questionCount - currentSequenceLength;

	auto solutionsToCheck = 1UL << currentSequenceLength;
	auto scoreMask = solutionsToCheck - 1;
	ScoreMap scoreMap(solutionsToCheck);

	/**
	 * If the length is 0 it would mean no answers are created to check
	 * however if the length is 0 then everyone has a score of 0 with a
	 * solution that has no answers
	 */
	if (currentSequenceLength == 0)
	{
		// std::cout << "Empty sequnce putting en lambda solution" << std::endl;
		std::valarray<uint8_t> score(examResults.studentCount);

		auto collection = SolutionCollection();
		collection.addSolution(0);
		scoreMap[std::move(score)] = std::move(collection);
		return scoreMap;
	}

	/**
	 * We create every possible answer sheet from 0 to 2^n  
	 */
	for (uint32_t i = 0; i < solutionsToCheck; ++i)
	{
		auto keepSequence = true;
		std::valarray<uint8_t> score(examResults.studentCount);

		for (uint8_t j = 0; j < examResults.studentCount; ++j)
		{
			auto matchingAnswers = ~((examResults.answers[j] >> n) ^ i) & scoreMask;
			score[j] = __builtin_popcount(matchingAnswers);

			// std::cout << "======================================" << std::endl << "\t" << binaryToString(examResults.answers[j]);
			// std::cout << std::endl << "\t" << binaryToString(examResults.answers[j] >> n);
			// std::cout << std::endl << " ^\t" << binaryToString(i);
			// std::cout << std::endl << "-----------------------------" << std::endl << "\t" << binaryToString((examResults.answers[j] >> n) ^ i);
			// std::cout << std::endl << "score: " << +score[j] << std::endl;
			
			
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

		SolutionCollection collection;
		collection.addSolution(i);

		// Clang-tidy sees this as a dead store but it's a false positive
		auto [it, inserted] = scoreMap.insert({ std::move(score), std::move(collection) }); // NOLINT
		if (!inserted)
		{
			it->second.grow(1);
		}
	}

	scoreMap.rehash(scoreMap.size());

	return scoreMap;
}

} // InferExamAnswers
