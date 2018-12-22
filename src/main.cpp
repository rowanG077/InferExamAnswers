#include "Algorithm.hpp"
#include "Parser.hpp"
#include "version.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>

void printVersion()
{
	std::cout << "program info:" << std::endl
			  << "\tname: " << INFEREXAMANSWERS_NAME << std::endl
			  << "\tdescription: " << INFEREXAMANSWERS_DESCRIPTION << std::endl
			  << "\tauthor: " << INFEREXAMANSWERS_AUTHOR << std::endl
			  << "\tversion: " << INFEREXAMANSWERS_VERSION << std::endl
			  << "\tmail: " << INFEREXAMANSWERS_MAIL << std::endl
			  << "\tcopyright: " << INFEREXAMANSWERS_COPYRIGHT << std::endl;
}

void printHelp(const std::string& progName)
{
	std::cout
		<< "usage: " << progName << " [options]" << std::endl
		<< "  basic user options: " << std::endl
		<< "    -h --help   \tshow this message" << std::endl
		<< "    -v --version\tshow version" << std::endl
		<< std::endl
		<< "when no options are specified program waits for input of exam answers and total points on stdin in the "
		   "following format: "
		<< std::endl
		<< std::endl
		<< "<p> <q>" << std::endl
		<< "a_1a_2...a_q <total points for student a>" << std::endl
		<< "b_1b_2...b_q <total points for student b>" << std::endl
		<< "..." << std::endl
		<< "p_1p_2...p_q <total points for student p>" << std::endl
		<< std::endl
		<< "where p is positive integer representing the number of students "
		<< "and q is a positive integer representing the number of exam questions "
		<< "For each question all students answered either 1 or 0 represented by the a_1a_2...a_q" << std::endl
		<< "Example:" << std::endl
		<< "3 5" << std::endl
		<< "01101 4" << std::endl
		<< "10100 3" << std::endl
		<< "00011 3" << std::endl
		<< std::endl
		<< "once input is given the program will calculate all possibilies of exams that could lead to the scores. "
		<< "If there is only one way for the exam answers to match the given input the sequence of answers is given, "
		<< "else only the number of possible sequences is given." << std::endl;

	printVersion();
}

int main(int argc, char** argv)
{
	// Because ptr arithmatic is not allowed but we need it here
	// to access program arguments we exclude no lint here
	std::vector<std::string> arguments(argv, argv + argc); // NOLINT

	if (arguments.size() >= 2) {
		if (arguments.at(1) == "--version" || arguments.at(1) == "-v") {
			printVersion();
		} else if (arguments.at(1) == "--help" || arguments.at(1) == "-h") {
			printHelp(arguments.at(0));
		} else {
			std::cout << "unknown options: \"" << arguments.at(1) << "\"" << std::endl << std::endl;
			printHelp(arguments.at(0));
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

	const auto [answers, scores] = InferExamAnswers::Parser::getExamResults(std::cin);

	auto result = InferExamAnswers::Algorithm::runAlgorithm(answers, scores);

	if (result.size() == 1)
	{
		for (const auto& i : result.front())
		{
			std::cout << +i;
		}
	}
	else
	{
		std::cout << result.size() << " solutions";
	}

	std::cout << std::endl;

	return EXIT_SUCCESS;
}
