#include <iostream>
#include <vector>
#include <format>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <number_of_primes>\n";
		return 1;
	}

	// Convert command line argument to uint64_t
	uint64_t number_of_primes;
	try {
		number_of_primes = std::stoull(argv[1]);
		if(number_of_primes==0){
			throw std::invalid_argument("Invalid");
		}
	} catch (const std::invalid_argument& e) {
		std::cerr << "argument should be a natural number\n";
		return 1;
	}

	// Initialize primes vector with first two primes
	std::vector<uint64_t> primes;
	primes.reserve(number_of_primes);
	primes.push_back(2);
	primes.push_back(3);
	uint64_t candidate = 5;	 // First candidate to test
	uint64_t test_prime_limit = 2;	// Index to determine how many primes to test against

	// Continue until we have enough primes
	while (primes.size() < number_of_primes) {
		// If the square of the next prime limit is greater than or equal to the candidate,
		// increment the test_prime_limit
		if (primes[test_prime_limit - 1] * primes[test_prime_limit - 1] <= candidate) {
			++test_prime_limit;
		}

		// Check if the candidate is prime by testing against all known primes up to test_prime_limit
		bool is_prime = true;
		for (size_t i = 1; i < test_prime_limit; ++i) {
			if (candidate % primes[i] == 0) {
				is_prime = false;
				break;
			}
		}

		if (is_prime) primes.push_back(candidate);
		// Move to the next candidate
		candidate += 2;	 // Only check odd numbers for primality
	}

	// Output the last prime number found
	std::cout << std::format("{}\n", primes[number_of_primes-1]);

	return 0;
}
