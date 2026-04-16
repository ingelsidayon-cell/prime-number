#include <iostream>
#include <vector>
#include <cstdint>
#include <format>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 2) {
        std::cerr << "Usage: prime-number <number_of_primes>\n";
        return 1;
    }

    std::string arg = argv[1];
    try {
        // Parse the command line argument as a natural number
        size_t number_of_primes = std::stoul(arg);

        if (number_of_primes < 1) {
            std::cerr << "argument should be a natural number\n";
            return 1;
        }

        // Initialize vector of primes with the first two known primes
        std::vector<uint64_t> primes;
        primes.reserve(number_of_primes);
        primes.push_back(2);
        primes.push_back(3);

        // Start checking from the first odd number after 3
        uint64_t candidate = 5;
        uint64_t test_prime_limit = 2;

        while (primes.size() < number_of_primes) {
            // Adjust test_prime_limit to include all relevant primes
            while (test_prime_limit < primes.size() &&
                   primes[test_prime_limit - 1] * primes[test_prime_limit - 1] <= candidate) {
                test_prime_limit++;
            }

            // Check divisibility against primes up to current test_prime_limit
            bool is_prime = true;
            for (size_t i = 1; i < test_prime_limit; ++i) {
                if (candidate % primes[i] == 0) {
                    is_prime = false;
                    break;
                }
            }

            if (is_prime) {
                primes.push_back(candidate);
            }

            candidate += 2; // Only check odd numbers
        }

        // Output the nth prime
        std::cout << std::format("{}", primes[number_of_primes - 1]) << std::endl;
        return 0;
    } catch (...) {
        // Catch any conversion errors
        std::cerr << "argument should be a natural number\n";
        return 1;
    }
}
