#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <format>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: prime-number <number_of_primes>\n";
		return 1;
	}

	uint64_t target_input;
	try {
        std::size_t end;
        target_input = std::stoull(argv[1], &end);
        if ( argv[1][0] < '0' || argv[1][0] > '9' || *(argv[1]+end) || target_input < 1) {
			throw std::invalid_argument("Invalid");
		}
	} catch (...) {
		std::cout << "argument should be a natural number" << std::endl;
		return 1;
	}

	size_t target_count = static_cast<size_t>(target_input);

	// Initialize primes vector with first two primes
	std::vector<uint64_t> primes;
	primes.reserve(target_count);

	// Logic for cases 1 and 2:
	if (target_count >= 1) primes.push_back(2);
	if (target_count >= 2) primes.push_back(3);

	uint64_t candidate = 5;         // First candidate to test
	uint64_t test_prime_limit = 2;  // Index to determine how many primes to test against

	while (primes.size() < target_count) {
		// Update the limit: if the square of the prime at the current limit
		// is <= candidate, we need to include the next prime in our tests.
		// We use primes[test_prime_limit] because index 2 is the 3rd prime (5).
		if (primes[test_prime_limit - 1] * primes[test_prime_limit - 1] <= candidate) {
			test_prime_limit++;
		}

		bool is_prime = true;
		// Test candidate against primes starting from primes[1] (which is 3)
		// up to the prime before the current limit.
		for (size_t i = 1; i < test_prime_limit - 1; ++i) {
			if (candidate % primes[i] == 0) {
				is_prime = false;
				break;
			}
		}

		if (is_prime) {
			primes.push_back(candidate);
		}

		candidate += 2; // Only test odd numbers
	}

	// Output the last prime found
	if (!primes.empty()) {
		std::cout << std::format("{}\n", primes.back());
	}

	return 0;
}
