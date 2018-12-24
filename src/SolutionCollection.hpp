#pragma once

#include <cstdint>

/**
 * @brief Contains code for the InferExamAnswers problem
 */
namespace InferExamAnswers
{

/**
 * @brief Faux collection of solutions.
 *        Since we are only interested in the first solution or the number of solutions
 *        we can get by never storing the solutions if there is more then 1
 */
class SolutionCollection
{
public:
	/**
	 * @brief default constructor
	 */
	SolutionCollection() = default;
	/**
	 * @brief Defaulted virtual destructor
	 */
	virtual ~SolutionCollection() = default;

	/**
	 * @brief Defaulted copy constructor
	 * \param b
	 */
	SolutionCollection(const SolutionCollection& b) = default;

	/**
	 * @brief Defaulted move constructor
	 * \param b
	 */
	SolutionCollection(SolutionCollection&& b) = default;

	/**
	 * @brief Defaulted copy assignment operator
	 * \param b
	 * \return
	 */
	SolutionCollection& operator=(const SolutionCollection& b) = default;

	/**
	 * @brief Defaulted move assignment operator
	 * \param b
	 * \return
	 */
	SolutionCollection& operator=(SolutionCollection&& b) = default;

	/**
	 * @brief Add a solution to the collection
	 * 
	 * @param solution The solution to add
	 */
	void addSolution(uint64_t solution)
	{
		this->solution = solution;
		++this->size;
	}

	/**
	 * @brief Add a number of faux solutions to the container
	 * 
	 * @param count The number of faux solutions to add.
	 */
	void grow(uint64_t count)
	{
		this->size += count;
	}

	/**
	 * @brief Get the first solution in the container
	 * 
	 * @return The solution
	 */
	uint64_t getSolution() const
	{
		return this->solution;
	}

	/**
	 * @brief Get the size of the container
	 * 
	 * @return The size of the container
	 */
	uint64_t getSize() const
	{
		return this->size;
	}

private:
	/**
	 * @brief The first solution in the collection  
	 */
	uint64_t solution{ 0 };

	/**
	 * @brief The total number of solutions in the container  
	 */
	uint64_t size{ 0 };
};

} // InferExamAnswers