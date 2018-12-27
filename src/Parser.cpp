#include "Parser.hpp"

#include <cstdint>
#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <string>

namespace InferExamAnswers
{
ExamResults Parser::getExamResults(std::istream& inputStream)
{
	static const auto maxStudent = 12;
	static const auto maxQuestion = 40;
	static const std::regex countRegex(R"(\s*(\d+)\s+(\d+))");

	std::smatch match;

	uint8_t studentCount = 0;
	uint8_t questionCount = 0;

	std::string inputLine;
	std::getline(inputStream, inputLine);

	if (!std::regex_match(inputLine, match, countRegex)) {
		std::stringstream ss;
		ss << R"(Expected input of the form of "p q" where p is the number of )"
		   << R"(students and q is the number of questions. Got: ")" << inputLine << "\"";
		throw ParserError(ss.str());
	}

	const auto rawStudentCount = std::stoi(match[1].str());
	const auto rawQuestionCount = std::stoi(match[2].str());
	if (rawStudentCount > maxStudent) {
		std::stringstream ss;
		ss << "A maximum of " << maxStudent << " students are supported.";
		throw std::invalid_argument(ss.str());
	}

	if (rawQuestionCount > maxQuestion) {
		std::stringstream ss;
		ss << "A maximum of " << maxQuestion << " questions are supported.";
		throw std::invalid_argument(ss.str());
	}

	studentCount = static_cast<uint8_t>(rawStudentCount);
	questionCount = static_cast<uint8_t>(rawQuestionCount);

	const std::regex questionRegex(R"(\s*([0|1]{)" + match[2].str() + R"(})\s*(\d+))");

	std::valarray<uint64_t> studentAnswers(studentCount);
	std::valarray<uint8_t> examScores(studentCount);

	for (size_t i = 0; i < studentCount; ++i) {
		std::getline(inputStream, inputLine);
		if (!std::regex_match(inputLine, match, questionRegex)) {
			std::stringstream ss;
			ss << R"(Expected answers in the form a_1a_2...a_q <score>. Got: ")" << inputLine << "\"";
			throw ParserError(ss.str());
		}

		const auto rawScore = std::stoi(match[2].str());
		if (rawScore > questionCount) {
			throw std::invalid_argument("Score is higher then the number of questions.");
		}

		const auto bitString = match[1].str();

		examScores[i] = static_cast<uint8_t>(rawScore);
		for (uint8_t j = 0; j < questionCount; ++j) {
			if (bitString[j] == '1') {
				studentAnswers[i] |= 1U << (questionCount - j - 1U);
			}
		}
	}

	return ExamResults{studentAnswers, examScores, questionCount, studentCount};
}

} // InferExamAnswers