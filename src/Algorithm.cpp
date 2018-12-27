#include "Algorithm.hpp"

namespace InferExamAnswers
{
SolutionCollection Algorithm::runAlgorithm(const ExamResults& examResults)
{
	/**
	 * We split the answers of all students into two parts. We brute force
	 * The possible exam solution for each side and then combine the results
	 */
	const uint8_t splitIndex = examResults.questionCount / 2;

	/**
	 * The results of the brute force computation of each side is stored
	 * in a map. The key is a valarray of the score of each student and the
	 * value are the associated solution(s). This way we can easily compute
	 * what the corresponding key is to a score in a map because we can
	 * subtract the key from the obtained scores to obtain the required key
	 * for the other half.
	 */
	const auto rightScores = computeScoreMap(examResults, 0, splitIndex);
	const auto leftScores = computeScoreMap(examResults, splitIndex, examResults.questionCount);

	SolutionCollection solutions;

	// Combine the left and right scores
	for (const auto& [rightScore, rightSolutions] : rightScores) {
		const std::valarray<uint8_t> leftScore = examResults.scores - rightScore;

		const auto it = leftScores.find(leftScore);
		if (it == leftScores.end()) {
			continue;
		}

		const auto& leftSolutions = it->second;

		/**
		 * we only actually add the solutions here if the cardinality of the cartesian
		 * product is 1 since if it is larger we aren't interested in the actual solution
		 * just the number of them so we can just add dummy solutions
		 */
		auto combinationCount = leftSolutions.getSize() * rightSolutions.getSize();
		if (solutions.getSize() == 0 && combinationCount == 1) {
			solutions.addSolution((leftSolutions.getSolution() << splitIndex) | rightSolutions.getSolution());
		} else {
			solutions.grow(combinationCount);
		}
	}

	return solutions;
}

Algorithm::ScoreMap Algorithm::computeScoreMap(const ExamResults& examResults, const uint8_t n, const uint8_t m)
{
	/**
	 *  Compute the length of the answers to create for the current partition
	 *  and the also compute the length of the anwers for the other partition.
	 */
	const uint8_t currentSequenceLength = m - n;
	const uint8_t otherSequenceLength = examResults.questionCount - currentSequenceLength;

	/**
	 * We have to check 2^currentSequenceLength solutions.
	 * So we create that number so we can use it as the upper
	 * limit in a for loop.
	 */
	const uint64_t solutionsToCheck = 1UL << currentSequenceLength;

	/**
	 * Since we are checking a subset of the total answers
	 * of a student we might have some extra bits from other
	 * answers we need to disregard. This mask uses can be used
	 * to filter out only the bits of the current subset since
	 * it contains currentSequenceLength number of 1 bits
	 */
	const uint64_t scoreMask = solutionsToCheck - 1UL;

	/**
	 * Initial bucket count will be the amount of possible solutions so a rehash
	 * will never occur while trying solutions.
	 */
	ScoreMap scoreMap(solutionsToCheck);

	/**
	 * If the length of the current partition is 0 no solution would be checked.
	 * However there still is a correct in that case. One with 0 solutions
	 */
	if (currentSequenceLength == 0) {
		std::valarray<uint8_t> score(examResults.studentCount);

		auto collection = SolutionCollection();
		collection.addSolution(0);
		scoreMap[std::move(score)] = std::move(collection);
		return scoreMap;
	}

	/**
	 * We create every possible solution from 0 to 2^n
	 * Verify if the resulting score with that solution
	 * still makes it possible to obtain the actual score
	 * the student got.
	 */
	for (uint32_t i = 0; i < solutionsToCheck; ++i) {
		auto keepSolution = true;
		std::valarray<uint8_t> score(examResults.studentCount);

		for (uint8_t j = 0; j < examResults.studentCount; ++j) {
			/**
			 * To obtain the score a student has obtained given a solution and the answer
			 * We first have to bitshift the solution over the current answers we are going
			 * to check. Then we apply a XOR operation. This results in a bit string that
			 * will contain a 1 if the answer didn't match and a 0 if it did match. So we
			 * negate that result. However since this result can still contain answers
			 * from the partition that we are currently disregarding we have to mask them
			 * out using the scoreMask.
			 *
			 * Now finally we need to count the amount of set bits in the resulting bit string.
			 * For this we use the special builtin function popcount which actually results
			 * in a single assembly instruction on modern hardware.
			 */
			const uint64_t correctAnswers = ~((examResults.answers[j] >> n) ^ i) & scoreMask;
			score[j] = __builtin_popcount(correctAnswers);

			/**
			 * The solution will be thrown away if the current
			 * score plus the perfect score for the other partition
			 * is smaller then the required score because there is no way
			 * to obtain the required score then.
			 * The same applies if the score exceeds the required score.
			 */
			if (score[j] + otherSequenceLength < examResults.scores[j] || score[j] > examResults.scores[j]) {
				keepSolution = false;
				break;
			}
		}

		if (!keepSolution) {
			continue;
		}

		SolutionCollection collection;
		collection.addSolution(i);

		// Clang-tidy sees this as a dead store but it's a false positive
		auto [it, inserted] = scoreMap.insert({std::move(score), std::move(collection)}); // NOLINT
		if (!inserted) {
			it->second.grow(1);
		}
	}

	/**
	 * Rehashing will remove unused buckets. Since after this the map will not
	 * be mutated further this will improve iteration speed when combining the
	 * partitions
	 */
	scoreMap.rehash(scoreMap.size());

	return scoreMap;
}

} // InferExamAnswers
