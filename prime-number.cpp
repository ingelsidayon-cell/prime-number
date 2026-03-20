#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdint>

bool is_positive_integer(const std::string& str) {
    if (str.empty() || str[0] == '-') {
        return false;
    }
    
    for (char c : str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    
    return true;
}

uint64_t parse_positive_integer(const std::string& str) {
    if (!is_positive_integer(str)) {
        return 0;
    }
    
    char* end_ptr;
    uint64_t result = strtoull(str.c_str(), &end_ptr, 10);
    
    if (*end_ptr != '\0') {
        return 0;
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_primes>\n";
        return 1;
    }
    
    uint64_t target_count = parse_positive_integer(argv[1]);
    
    if (target_count == 0) {
        std::cerr << "argument should be a natural number\n";
        return 1;
    }
    
    std::vector<uint64_t> primes;
    
    // Handle special cases
    if (target_count == 0) {
        return 0;
    } else if (target_count == 1) {
        std::cout << "2\n";
        return 0;
    } else if (target_count == 2) {
        std::cout << "3\n";
        return 0;
    }
    
    // Initialize primes with first two primes
    primes.push_back(2);
    primes.push_back(3);
    
    uint64_t test_prime_limit = 1;
    uint64_t candidate = 5;
    
    while (primes.size() < target_count) {
        // Check if we need to extend our prime testing limit
        if (primes[test_prime_limit] * primes[test_prime_limit] <= candidate) {
            test_prime_limit++;
        }

        // Check if candidate is prime using primes[test_prime_limit-1] as upper bound
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

        candidate += 2; // Only test odd numbers
    }

    std::cout << primes[target_count - 1] << "\n";

    return 0;
}
