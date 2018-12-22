#include "Algorithm.hpp"

#include <iostream>


namespace InferExamAnswers
{

std::list<std::vector<int8_t>> Algorithm::runAlgorithm(const std::vector<std::vector<int8_t>>& answers, const std::vector<int8_t>& scores)
{
	std::list<std::vector<int8_t>> result;

	auto questionCount = answers[0].size();

	auto splitIndex = questionCount / 2;

	auto leftScores = computeScoreMap(answers, scores, 0, splitIndex);
	auto rightScores = computeScoreMap(answers, scores, splitIndex, questionCount);

	std::list<std::vector<int8_t>> solutions;

	// Fuse results
	for (auto& [leftScore, leftSolutions] : leftScores)
	{
		std::vector<int8_t> keyRequiredInRight(scores);
		for (int8_t i = 0; i < keyRequiredInRight.size(); ++i)
		{
			keyRequiredInRight[i] -= leftScore[i];
		}

		auto it = rightScores.find(keyRequiredInRight);
		if (it == rightScores.end())
		{
			continue;
		}

		auto& rightSolutions = it->second;

		for (const auto& l : leftSolutions)
		{
			for (const auto& r : rightSolutions)
			{
				std::cout << std::endl << "solution found: ";
				for (const auto& i : l)
				{
					std::cout << +i;
				}

				std::cout << "|";

				for (const auto& i : r)
				{
					std::cout << +i;
				}
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;

		// we only actuallly add the solutions here if the cardinality of the cartesian
		// product is 1 since if it is larger we aren't interested in the actual solution
		// just the number of them and then we can just add dummy solutions
		auto combinationCount = leftSolutions.size() * rightSolutions.size();
		if (combinationCount == 1)
		{
			leftSolutions.front().insert(leftSolutions.front().end(), std::make_move_iterator(rightSolutions.front().begin()), 
			                             std::make_move_iterator(rightSolutions.front().end()));

			solutions.emplace_front(std::move(leftSolutions.front()));
		}
		else
		{
			for (int i = 0; i < combinationCount; ++i)
			{
				solutions.emplace_front(std::vector<int8_t>());
			}
		}
	}

	return solutions;
}

bool Algorithm::generateNextBitSequence(std::vector<int8_t>& currentSequence)
{
	for (int8_t i = 0; i < currentSequence.size(); ++i)
	{
		if (currentSequence[i] == 0)
		{
			currentSequence[i] = 1;
			for (int8_t j = i - 1; j >= 0; --j)
			{
				currentSequence[j] = 0;
			}
			return true;
		}
	}

	return false;
}

Algorithm::ScoreMap Algorithm::computeScoreMap(
	const std::vector<std::vector<int8_t>>& answers,
	const std::vector<int8_t>& scores,
	int8_t n,
	int8_t m
)
{
	ScoreMap scoreMap;

	std::vector<int8_t> sequence(m - n);
	
	auto examCount = answers.size();
	auto questionCount = answers[0].size();

	std::cout << "Look at exams from " << +n << " to " << +m << std::endl;
	std::cout << "Generating sequences of length " << sequence.size() << std::endl;

	if (sequence.empty())
	{
		std::vector<int8_t> guessScores(examCount);
		scoreMap[guessScores] = std::list<std::vector<int8_t>>();
		return scoreMap;
	}

	auto otherSideSequenceLength = questionCount - sequence.size();

	std::cout << "Length of the sequence for the other side is " << otherSideSequenceLength << std::endl;

	do
	{
		std::cout << "Testing sequence: ";
		for (const auto& i : sequence)
		{
			std::cout << +i;
		}
		std::cout << std::endl;

		auto keepSequence = true;
		std::vector<int8_t> guessScores(examCount);
		for (int8_t i = 0; i < examCount; ++i)
		{
			guessScores[i] = calculateScore(answers[i], sequence, n, m);
			if (guessScores[i] < scores[i] - otherSideSequenceLength || guessScores[i] > scores[i])
			{
				std::cout << "Is not a valid sequence. The calculated score is " << +(guessScores[i]) << " and the total score of the student is " << +(scores[i]) << std::endl;
				keepSequence = false;
				break;
			}
		}

		if (keepSequence)
		{
			std::cout << "Storing result with scores: ";
			for (const auto& i : guessScores)
			{
				std::cout << +i;
			}
			std::cout << std::endl << "sequence: ";
			for (const auto& i : sequence)
			{
				std::cout << +i;
			}
			std::cout << std::endl;

			auto it = scoreMap.find(guessScores);
			if (it != scoreMap.end())
			{
				it->second.emplace_front(sequence);
			}
			else
			{
				scoreMap[guessScores] = std::list<std::vector<int8_t>>{{ sequence }};
			}
		}
	} while (generateNextBitSequence(sequence));

	return scoreMap;
}

int8_t Algorithm::calculateScore(
	const std::vector<int8_t>& studentAnswer,
	const std::vector<int8_t>& examSolution,
	int8_t n,
	int8_t m
)
{
	int8_t score = 0;
	for (int8_t i = n; i < m; ++i)
	{
		if (studentAnswer[i] == examSolution[i - n])
		{
			++score;
		}
	}

	return score;
}

} // InferExamAnswers
