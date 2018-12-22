#include "Parser.hpp"

#include <cstdint>
#include <limits>
#include <regex>
#include <sstream>
#include <string>

namespace InferExamAnswers
{

Parser::ExamResults Parser::getExamResults(std::istream& inputStream)
{
	static const auto maxStudent = 12;
	static const auto maxQuestion = 40;
	static const std::regex countRegex(R"(\s*(\d+)\s+(\d+))");

	std::smatch match;

	int8_t studentCount = 0;
	int8_t questionCount = 0;

	std::string inputLine;
	std::getline(inputStream, inputLine);

	if (!std::regex_match(inputLine, match, countRegex)) {
		std::stringstream ss;
		ss << R"(Expected input of the form of "p q" where p is the number of )"
		   << R"(students and q is the number of questions. Got: ")" << inputLine << "\"";
		throw ParserError(ss.str());
	}

	auto rawStudentCount = std::stoi(match[1].str());
	auto rawQuestionCount = std::stoi(match[2].str());
	if (rawStudentCount > maxStudent) {
		std::stringstream ss;
		throw std::invalid_argument("A maximum of 12 students are supported.");
	}

	if (rawQuestionCount > maxQuestion) {
		std::stringstream ss;
		throw std::invalid_argument("A maximum of 40 questions are supported.");
	}

	studentCount = static_cast<int8_t>(rawStudentCount);
	questionCount = static_cast<int8_t>(rawQuestionCount);

	const std::regex questionRegex(R"(\s*([0|1]{)" + match[2].str() + R"(})\s*(\d+))");

	std::vector<std::vector<int8_t>> examAnswers;
	std::vector<int8_t> examScores;

	examAnswers.reserve(studentCount);
	examScores.reserve(studentCount);

	for (std::size_t i = 0; i < studentCount; ++i) {
		int8_t score = 0;
		std::vector<int8_t> answers;
		answers.reserve(questionCount);

		std::getline(inputStream, inputLine);
		if (!std::regex_match(inputLine, match, questionRegex)) {
			std::stringstream ss;
			ss << R"(Expected answers in the form a_1a_2...a_q <score>. Got: ")" << inputLine << "\"";
			throw ParserError(ss.str());
		}

		auto rawScore = std::stoi(match[2].str());
		if (rawScore > questionCount) {
			throw std::invalid_argument("Score is higher then the number of questions.");
		}

		score = static_cast<int8_t>(rawScore);
		for (const auto& c : match[1].str()) {
			answers.emplace_back(c == '0' ? 0 : 1);
		}

		examAnswers.emplace_back(std::move(answers));
		examScores.emplace_back(score);
	}

	return std::make_pair(examAnswers, examScores);
}

} // InferExamAnswers