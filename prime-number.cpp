#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstdint>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: prime-number <number_of_primes>\n";
		return 1;
	}

	string input = argv[1];
	if (input.empty()) {
		cout << "Argument should be a natural number\n";
		return 1;
	}

	bool is_number = true;
	for (char c : input) {
		if (!isdigit(c)) {
			is_number = false;
			break;
		}
	}

	if (!is_number) {
		cout << "Argument should be a natural number\n";
		return 1;
	}

	// Convert input to unsigned 64-bit integer
	uint64_t number_of_primes = stoul(input);

	if (number_of_primes <= 0) {
		cout << "Argument should be a natural number\n";
		return 1;
	}

	// Initialize with the first two primes
	vector<uint64_t> primes;
	primes.reserve(number_of_primes);
	primes.push_back(2);
	primes.push_back(3);

	uint64_t candidate = 5;  // Start testing from 5
	uint64_t test_prime_limit = 2;  // Index to determine how many primes to test against

	while (primes.size() < number_of_primes) {
		// Increment test_prime_limit as long as the square of the current prime is <= candidate
		while (test_prime_limit < primes.size() && primes[test_prime_limit - 1] * primes[test_prime_limit - 1] <= candidate) {
			test_prime_limit++;
		}

		// Check if the candidate is a prime
		bool is_prime = true;
		for (uint64_t i = 1; i < test_prime_limit; ++i) {
			if (candidate % primes[i] == 0) {
				is_prime = false;
				break;
			}
		}

		if (is_prime) {
			primes.push_back(candidate);
		}

		candidate += 2;  // Increment by 2 to check only odd numbers
	}

	cout << primes[number_of_primes-1]<< endl;
	return 0;
}
