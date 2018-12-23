#include <Algorithm.hpp>
#include <catch2/catch.hpp>

#include <cstddef>
#include <iostream>

SCENARIO("Bitsequence generation")
{
	// GIVEN("an algorithm that can infer exam solution given a list of exam answers and scores")
	// {
	// 	WHEN("there is an exam with a single question and a single student")
	// 	{
	// 		std::vector<std::vector<int8_t>> inputAnswers{{1}};
	// 		std::vector<int8_t> inputScores{1};

	// 		auto result = InferExamAnswers::Algorithm::runAlgorithm(inputAnswers, inputScores);
		
	// 		THEN("the algorithm finds a single solutions")
	// 		{
	// 			REQUIRE(result.size() == 1);
	// 			REQUIRE(result.front() == std::vector<int8_t>{ 1 });
	// 		}
	// 	}

	// 	WHEN("there is an exam with no solutions")
	// 	{
	// 		std::vector<std::vector<int8_t>> inputAnswers{
	// 			{0,1,1,0,1},
	// 			{1,0,1,0,0},
	// 			{0,0,0,1,1}
	// 		};

	// 		std::vector<int8_t> inputScores{0, 3, 2};

	// 		auto result = InferExamAnswers::Algorithm::runAlgorithm(inputAnswers, inputScores);
			
	// 		THEN("the algorithm finds no solutions")
	// 		{
	// 			REQUIRE(result.empty());
	// 		}
	// 	}

	// 	WHEN("there is an exam with a single solutions")
	// 	{
	// 		std::vector<std::vector<int8_t>> inputAnswers{
	// 			{0,1,1,0,1},
	// 			{1,0,1,0,0},
	// 			{0,0,0,1,1}
	// 		};

	// 		std::vector<int8_t> inputScores{4, 3, 3};

	// 		auto result = InferExamAnswers::Algorithm::runAlgorithm(inputAnswers, inputScores);
			
	// 		THEN("the algorithm finds one solutions")
	// 		{
	// 			REQUIRE(result.size() == 1);
	// 			REQUIRE(result.front() == std::vector<int8_t>{ 0,0,1,0,1 });
	// 		}
	// 	}

	// 	WHEN("there is an exam with 4 solutions")
	// 	{
	// 		std::vector<std::vector<int8_t>> inputAnswers{
	// 			{0,0,0,0},
	// 			{1,0,1,0},
	// 			{0,1,0,1},
	// 			{1,1,1,1}
	// 		};

	// 		std::vector<int8_t> inputScores{2, 2, 2, 2};

	// 		auto result = InferExamAnswers::Algorithm::runAlgorithm(inputAnswers, inputScores);
			
	// 		THEN("the algorithm finds four solutions")
	// 		{
	// 			REQUIRE(result.size() == 4);
	// 		}
	// 	}

	// }
}
