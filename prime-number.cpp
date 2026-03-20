#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>

// Function to check if a string represents a positive integer
bool isPositiveInteger(const char* str) {
    if (str == nullptr || *str == '\0') return false;

    // Check if the string is a valid number
    char* endptr;
    long val = strtol(str, &endptr, 10);

    // Check for conversion errors or negative numbers
    if (endptr == str || *endptr != '\0' || val <= 0) {
        return false;
    }

    // Check for overflow
    if (val > ULLONG_MAX) {
        return false;
    }

    return true;
}

// Function to find the nth prime number
uint64_t findNthPrime(size_t n) {
    if (n == 0 || n == 1) return 2;
    if (n == 2) return 3;

    std::vector<uint64_t> primes = {2, 3};
    size_t test_prime_limit = 1;
    uint64_t candidate = 5;

    while (primes.size() < n) {
        // Update test_prime_limit if needed
        if (primes[test_prime_limit] * primes[test_prime_limit] <= candidate) {
            test_prime_limit++;
        }

        // Test primality against known primes
        bool is_prime = true;
        if (test_prime_limit > 1) {
            for (size_t i = 1; i < test_prime_limit; ++i) {
                if (candidate % primes[i] == 0) {
                    is_prime = false;
                    break;
                }
            }
        }

        if (is_prime) {
            primes.push_back(candidate);
        }

        candidate += 2; // Only test odd numbers
    }

    return primes.back();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: prime-number <number_of_primes>\n";
        return 1;
    }

    if (!isPositiveInteger(argv[1])) {
        std::cerr << "argument should be a natural number\n";
        return 1;
    }

    size_t n = std::strtoul(argv[1], nullptr, 10);
    uint64_t prime = findNthPrime(n);
    std::cout << prime << "\n";

    return 0;
}
