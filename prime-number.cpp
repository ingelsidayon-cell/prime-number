#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdint>

// Function to validate and convert command line argument
uint64_t validateArgument(const std::string& arg) {
    try {
        size_t pos = 0;
        uint64_t result = std::stoull(arg, &pos);
        if (pos != arg.length()) {
            throw std::invalid_argument("Invalid characters in argument");
        }
        return result;
    } catch (const std::exception&) {
        throw std::invalid_argument("argument should be a natural number");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_primes>\n";
        return 1;
    }

    uint64_t target_count;
    try {
        target_count = validateArgument(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Handle special cases
    if (target_count == 0) {
        std::cerr << "argument should be a natural number" << std::endl;
        return 1;
    }

    if (target_count == 1) {
        std::cout << "2" << std::endl;
        return 0;
    }

    if (target_count == 2) {
        std::cout << "3" << std::endl;
        return 0;
    }

    // Initialize primes vector with first two primes
    std::vector<uint64_t> primes;
    primes.reserve(target_count+2);
    primes.push_back(2);
    primes.push_back(3);

    uint64_t candidate = 5;  // First candidate to test
    uint64_t test_prime_limit = 1;  // Index to determine how many primes to test against
    
    while (primes.size() < target_count) {
        // Update test_prime_limit if needed
        while (primes[test_prime_limit] * primes[test_prime_limit] <= candidate) {
            test_prime_limit++;
        }

        // Test candidate against primes
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

        // Move to next odd candidate
        candidate += 2;
    }

    std::cout << primes[target_count-1] << std::endl;
    return 0;
}
