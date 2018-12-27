#include <Algorithm.hpp>
#include <catch2/catch.hpp>

SCENARIO("Algorithm correctness")
{
	GIVEN("an algorithm that can infer exam solution given a list of exam answers and scores")
	{
		WHEN("there is an exam with a single question and a single student")
		{
			InferExamAnswers::ExamResults examResults{{0b1}, {1}, 1, 1};

			auto result = InferExamAnswers::Algorithm::runAlgorithm(examResults);

			THEN("the algorithm finds a single solutions")
			{
				REQUIRE(result.getSize() == 1);
				REQUIRE(result.getSolution() == 1);
			}
		}

		WHEN("there is an exam with no solutions")
		{
			InferExamAnswers::ExamResults examResults{{0b01101, 0b10100, 0b00011}, {0, 3, 2}, 5, 3};

			auto result = InferExamAnswers::Algorithm::runAlgorithm(examResults);

			THEN("the algorithm finds no solutions")
			{
				REQUIRE(result.getSize() == 0);
			}
		}

		WHEN("there is an exam with a single solutions")
		{
			InferExamAnswers::ExamResults examResults{{0b01101, 0b10100, 0b00011}, {4, 3, 3}, 5, 3};

			auto result = InferExamAnswers::Algorithm::runAlgorithm(examResults);

			THEN("the algorithm finds one solutions")
			{
				REQUIRE(result.getSize() == 1);
				REQUIRE(result.getSolution() == 0b00101);
			}
		}

		WHEN("there is an exam with 4 solutions")
		{
			InferExamAnswers::ExamResults examResults{{0b0000, 0b1010, 0b0101, 0b1111}, {2, 2, 2, 2}, 4, 4};

			auto result = InferExamAnswers::Algorithm::runAlgorithm(examResults);

			THEN("the algorithm finds four solutions")
			{
				REQUIRE(result.getSize() == 4);
			}
		}
	}
}
