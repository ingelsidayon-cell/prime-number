#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <format>

int main(int argc, char* argv[]) {
	uint64_t number_of_primes;
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <number_of_primes>" << std::endl;
		return 1;
	}

	try {
		size_t chars_read = 0;
		auto n = std::stoll( argv[1] , &chars_read);
		if (chars_read != strlen( argv[1] ) || n < 1) {
			throw std::invalid_argument("argument should be a natural number");
		}
		number_of_primes=n;

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}

	if (number_of_primes == 1) {
		std::cout << "2" << std::endl;
		return 0;
	}

	// Initialize primes vector with first two primes
	std::vector<uint64_t> primes;
	primes.reserve(number_of_primes);
	primes.push_back(2);
	primes.push_back(3);
	uint64_t candidate = 5;  // First candidate to test
	uint64_t test_prime_limit = 2;  // Index to determine how many primes to test against

	while (primes.size() < number_of_primes) {
		bool is_prime = true;
		uint64_t limit = std::sqrt(candidate);
		for (uint64_t i = 1; i < test_prime_limit && primes[i] <= limit; ++i) {
			if (candidate % primes[i] == 0) {
				is_prime = false;
				break;
			}
		}

		if (is_prime) {
			primes.push_back(candidate);
		}

		// Update test_prime_limit if necessary
		if (primes[test_prime_limit] * primes[test_prime_limit] <= candidate) {
			++test_prime_limit;
		}

		// Increment candidate by 2 (skip even numbers)
		candidate += 2;
	}

	std::cout << std::format("{}", primes.back()) << std::endl;
	return 0;
}
