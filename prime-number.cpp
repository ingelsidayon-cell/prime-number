#include <iostream>
#include <cstring>
#include <vector>
#include <cstdint>
#include <string_view>
#include <stdexcept>
#include <format>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: prime-number <number_of_primes>\n";
        return 1;
    }

    // Parse command line argument
    const char* target_str = argv[1];
    uint64_t number_of_primes = 0;

    try {
        size_t chars_read = 0;
        number_of_primes = std::stoull(target_str, &chars_read);
        
        if (chars_read != strlen(target_str) || number_of_primes < 1) {
            throw std::invalid_argument("argument should be a natural number");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    // Initialize primes vector with first two primes
    std::vector<uint64_t> primes;
    primes.reserve(number_of_primes);
    primes.push_back(2);
    if (number_of_primes == 1) {
        std::cout << std::format("{}", primes.back()) << "\n";
        return 0;
    }
    primes.push_back(3);

    if (number_of_primes == 2) {
        std::cout << std::format("{}", primes.back()) << "\n";
        return 0;
    }

    uint64_t candidate = 5;  // First candidate to test
    uint64_t test_prime_limit = 2;  // Index to determine how many primes to test against

    while (primes.size() < number_of_primes) {
        // Check if we need to increment the test prime limit
        if (primes[test_prime_limit-1] * primes[test_prime_limit-1] <= candidate) {
            ++test_prime_limit;
        }

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

        candidate += 2; // Increment by 2 to skip even numbers
    }

    std::cout << std::format("{}", primes.back()) << "\n";
    return 0;
}
