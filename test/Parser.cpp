#include <Parser.hpp>
#include <catch2/catch.hpp>

#include <cstddef>
#include <iterator>
#include <sstream>


SCENARIO("Parsing box specifcations from inputStream")
{
	GIVEN("an input stream")
	{
		WHEN("parsing correct input")
		{
			uint8_t questionCount = 5;
			std::valarray<uint64_t> inputAnswers{
				0b01101,
				0b10100,
				0b00011
			};
			std::valarray<uint8_t> inputScores{4, 3, 3};

			std::stringstream stream;

			stream << inputAnswers.size() << " " << +questionCount << std::endl;

			for (size_t i = 0; i < inputAnswers.size(); ++i) {
				for (size_t j = 0; j < questionCount; ++j)
				{
					stream << ((inputAnswers[i] >> (questionCount - j - 1)) & 1U);
				}
				stream << " " << +(inputScores[i]) << std::endl;
			}

			const auto examResults = InferExamAnswers::Parser::getExamResults(stream);

			THEN("The exam results are parsed correctly")
			{
				REQUIRE(examResults.answers.size() == inputAnswers.size());

				for (std::size_t i = 0; i < examResults.answers.size(); ++i) {
					REQUIRE(examResults.scores[i] == inputScores[i]);
					REQUIRE(examResults.answers[i] == inputAnswers[i]);
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
