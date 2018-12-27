#include <Algorithm.hpp>
#include <catch2/catch.hpp>

#include <cstddef>
#include <iostream>

SCENARIO("Algorithm benchmarking 2")
{
	GIVEN("an algorithm that can infer exam solution given a list of exam answers and scores")
	{
		WHEN("There is a very large exam with many students")
		{
			InferExamAnswers::ExamResults examResults {
				{
					0b0000000000000000000011111111111111111111,
					0b0000000000000000000111111111111111111110,
					0b0000000000000000001111111111111111111100,
					0b0000000000000000011111111111111111111000,
					0b0000000000000000111111111111111111110000,
					0b0000000000000001111111111111111111100000,
					0b0000011111111111111111111000000000000000,
					0b0000111111111111111111110000000000000000,
					0b0001111111111111111111100000000000000000,
					0b0011111111111111111111000000000000000000,
					0b0111111111111111111110000000000000000000,
					0b1111111111111111111111111111111111111111
				},
				{20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 0},
				40,
				12
			};

			auto result = InferExamAnswers::Algorithm::runAlgorithm(examResults);

			THEN("the algorithm gets a result")
			{
				REQUIRE(result.getSize() == 1);
				REQUIRE(result.getSolution() == 0b0000000000000000000000000000000000000000);
			}
		}
	}
}
