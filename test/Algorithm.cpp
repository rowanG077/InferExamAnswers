#include <Algorithm.hpp>
#include <catch2/catch.hpp>

#include <cstddef>
#include <iostream>

SCENARIO("Bitsequence generation")
{
	GIVEN("a length and a bit sequence generator")
	{
		WHEN("Generating bit sequence of that length")
		{
			THEN("The next bit sequence is always one larger")
			{
				std::vector<int8_t> sequence(3);
				REQUIRE(std::vector<int8_t> {0,0,0} == sequence);
				
				REQUIRE(InferExamAnswers::Algorithm::generateNextBitSequence(sequence) == true);
				REQUIRE(std::vector<int8_t> {1,0,0} == sequence);

				REQUIRE(InferExamAnswers::Algorithm::generateNextBitSequence(sequence) == true);
				REQUIRE(std::vector<int8_t> {0,1,0} == sequence);

				REQUIRE(InferExamAnswers::Algorithm::generateNextBitSequence(sequence) == true);
				REQUIRE(std::vector<int8_t> {1,1,0} == sequence);

				REQUIRE(InferExamAnswers::Algorithm::generateNextBitSequence(sequence) == true);
				REQUIRE(std::vector<int8_t> {0,0,1} == sequence);

				REQUIRE(InferExamAnswers::Algorithm::generateNextBitSequence(sequence) == true);
				REQUIRE(std::vector<int8_t> {1,0,1} == sequence);

				REQUIRE(InferExamAnswers::Algorithm::generateNextBitSequence(sequence) == true);
				REQUIRE(std::vector<int8_t> {0,1,1} == sequence);

				REQUIRE(InferExamAnswers::Algorithm::generateNextBitSequence(sequence) == true);
				REQUIRE(std::vector<int8_t> {1,1,1} == sequence);

				REQUIRE(InferExamAnswers::Algorithm::generateNextBitSequence(sequence) == false);
			}
		}
	}

	GIVEN("A list of exam answer")
	{
		std::vector<std::vector<int8_t>> inputAnswers{{1}};
		std::vector<int8_t> inputScores{1};

		WHEN("Splitting the exam answer into two")
		{
			auto questionsCount = inputAnswers[0].size();
			auto splitIndex = questionsCount / 2;

			auto leftScores = InferExamAnswers::Algorithm::computeScoreMap(inputAnswers, inputScores, 0, splitIndex);
			auto rightScores = InferExamAnswers::Algorithm::computeScoreMap(inputAnswers, inputScores, splitIndex, questionsCount);

			std::cout << "leftScores: " << std::endl;
			for ( const auto &[k, v]: leftScores) {
				std::cout << '\t';
				for (const auto& j : k)
				{
					std::cout << +j;
				}
				std::cout << ": ";
				for (const auto& j : v)
				{
					for (const auto& s : j)
					{
						std::cout << +s;
					}
					std::cout << ",";
				}
				std::cout << std::endl;
			}

			std::cout << "rightScores: " << std::endl;
			for ( const auto &[k, v]: rightScores) {
				std::cout << '\t';
				for (const auto& j : k)
				{
					std::cout << +j;
				}
				std::cout << ": ";
				for (const auto& j : v)
				{
					for (const auto& s : j)
					{
						std::cout << +s;
					}
					std::cout << ",";
				}
				std::cout << std::endl;
			}

			std::cout << std::endl << std::endl << std::endl << std::endl;
		}

	}
}
