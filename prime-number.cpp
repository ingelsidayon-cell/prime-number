#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <cctype>
#include <format>

using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        cerr << "Usage: prime-number <number_of_primes>" << endl;
        return 1;
    }

    string arg = argv[1];

    // Check if the argument is a valid natural number (positive integer)
    for (char c : arg) {
        if (!isdigit(c)) {
            cout << "argument should be a natural number" << endl;
            return 1;
        }
    }

    // Convert the input string to an unsigned 64-bit integer
    uint64_t number_of_primes = stoull(arg);

    // Handle invalid cases: non-positive input
    if (number_of_primes < 1) {
        cout << "argument should be a natural number" << endl;
        return 1;
    }

    // Initialize the primes vector with the first two primes (2 and 3)
    vector<uint64_t> primes;
    primes.reserve(number_of_primes);
    primes.push_back(2);
    primes.push_back(3);

    // If only 1 or 2 primes are needed, we're done
    if (number_of_primes <= 2) {
        cout << std::format("{}", primes[number_of_primes - 1]) << std::endl;
        return 0;
    }

    // Start testing from 5, and increment by 2 (only odd numbers)
    uint64_t candidate = 5;
    uint64_t test_prime_limit = 2;

    // Continue generating primes until we have the requested number
    while (primes.size() < number_of_primes) {
        // Check if the square of the current test prime is <= candidate
        if (primes[test_prime_limit - 1] * primes[test_prime_limit - 1] <= candidate) {
            test_prime_limit++;
        }

        // Check if the candidate is divisible by any of the primes up to test_prime_limit-1
        bool is_prime = true;
        for (uint64_t i = 1; i < test_prime_limit; i++) {
            if (candidate % primes[i] == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            primes.push_back(candidate);
        }

        // Move to the next candidate (all odd numbers)
        candidate += 2;
    }

    // Output the last prime in the list
    cout << std::format("{}", primes[number_of_primes - 1]) << std::endl;

    return 0;
}
