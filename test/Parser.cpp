#include <Parser.hpp>
#include <catch2/catch.hpp>

#include <cstddef>
#include <iterator>
#include <limits>
#include <sstream>

SCENARIO("Parsing box specifcations from inputStream")
{
	GIVEN("an input stream")
	{
		WHEN("parsing correct input")
		{
			std::vector<std::vector<int8_t>> inputAnswers{{0, 1, 1, 0, 1}, {1, 0, 1, 0, 0}, {0, 0, 0, 1, 1}};
			std::vector<int8_t> inputScores{4, 3, 3};

			std::stringstream stream;

			stream << inputAnswers.size() << " " << inputAnswers[0].size() << std::endl;

			for (std::size_t i = 0; i < inputAnswers.size(); ++i) {
				for (const auto& a : inputAnswers[i]) {
					stream << +a;
				}
				stream << " " << +(inputScores[i]) << std::endl;
			}

			const auto examResults = InferExamAnswers::Parser::getExamResults(stream);

			THEN("The exam results are parsed correctly")
			{
				REQUIRE(examResults.size() == inputAnswers.size());
				for (std::size_t i = 0; i < examResults.size(); ++i) {
					REQUIRE(examResults[i].getScore() == inputScores[i]);
					REQUIRE(examResults[i].getExamAnswers() == inputAnswers[i]);
				}
			}
		}

		WHEN("parsing the first line and negative number is present")
		{
			std::stringstream stream;
			stream << "-1 1" << std::endl;
			THEN("a ParserError is thrown")
			{
				REQUIRE_THROWS_AS(InferExamAnswers::Parser::getExamResults(stream), InferExamAnswers::ParserError);
			}
		}

		WHEN("parsing the first line and there are more then 40 exam question")
		{
			std::stringstream stream;
			THEN("An invalid_argument exception is thrown")
			{
				stream << "1 41" << std::endl;
				REQUIRE_THROWS_AS(InferExamAnswers::Parser::getExamResults(stream), std::invalid_argument);
			}
		}

		WHEN("parsing the first line and there are more then 12 students")
		{
			std::stringstream stream;
			THEN("An invalid_argument exception is thrown")
			{
				stream << "13 1" << std::endl;
				REQUIRE_THROWS_AS(InferExamAnswers::Parser::getExamResults(stream), std::invalid_argument);
			}
		}

		WHEN("parsing an examResult that doesn't contain the correct number of answers")
		{
			std::stringstream stream;

			THEN("a ParserError is thrown")
			{
				stream << "1 2" << std::endl << "011 2" << std::endl;
				REQUIRE_THROWS_AS(InferExamAnswers::Parser::getExamResults(stream), InferExamAnswers::ParserError);
			}
		}

		WHEN("parsing an examResult where the score is higher then then number of questions")
		{
			std::stringstream stream;

			THEN("a invalid_argument is thrown")
			{
				stream << "1 2" << std::endl << "01 3" << std::endl;
				REQUIRE_THROWS_AS(InferExamAnswers::Parser::getExamResults(stream), std::invalid_argument);
			}
		}
	}
}
