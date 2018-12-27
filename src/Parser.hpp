#pragma once

#include "ExamResults.hpp"
#include "ParserError.hpp"

#include <istream>

/**
 * @brief Contains code for the InferExamAnswers problem
 */
namespace InferExamAnswers
{
/**
 * @brief Parser class that handles reading from input to obtain ExamResults
 */
class Parser
{
public:
	/**
	 * @brief Delete constructor
	 */
	Parser() = delete;

	/**
	 * @brief Delete virtual destructor
	 */
	virtual ~Parser() = delete;

	/**
	 * @brief Delete copy constructor
	 * \param b
	 */
	Parser(const Parser& b) = delete;

	/**
	 * @brief Delete move constructor
	 * \param b
	 */
	Parser(Parser&& b) = delete;

	/**
	 * @brief Delete copy assignment operator
	 * \param b
	 * \return
	 */
	Parser& operator=(const Parser& b) = delete;

	/**
	 * @brief Delete move assignment operator
	 * \param b
	 * \return
	 */
	Parser& operator=(Parser&& b) = delete;

	/**
	 * @brief Get exam results
	 *
	 * @throw ParserError Parsing failed due to malformed input
	 * @throw invalid_argument If input form is correct but is not valid
	 *
	 * @param inputStream The inputStream to read from
	 * @return A pair containing in the first index a vector of the answers for each student and on the second
	 *         index containing the score
	 */
	[[nodiscard]] static ExamResults getExamResults(std::istream& inputStream);
};
} // InferExamAnswers
