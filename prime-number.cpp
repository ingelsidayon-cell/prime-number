#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <cctype>

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 2) {
        std::cerr << "argument should be a natural number" << std::endl;
        return 1;
    }
    
    // Parse the argument
    char* endptr;
    unsigned long long arg = std::strtoull(argv[1], &endptr, 10);
    
    // Check if the entire string was consumed and if it's a positive number
    if (*endptr != '\0' || arg == 0) {
        std::cerr << "argument should be a natural number" << std::endl;
        return 1;
    }
    
    // Special cases
    if (arg == 1) {
        std::cout << 2 << std::endl;
        return 0;
    }
    if (arg == 2) {
        std::cout << 3 << std::endl;
        return 0;
    }
    
    // For arg > 2, we need to generate primes
    std::vector<uint64_t> primes;
    primes.push_back(2);  // First prime
    primes.push_back(3);  // Second prime
    
    // We need to find 'arg' primes, so we start with 2 primes already in the vector
    uint64_t count = 2;
    uint64_t candidate = 5;  // Start testing at 5 (first odd number after 3)
    uint64_t test_prime_limit = 1;  // Index to track which primes to test against
    
    while (count < arg) {
        // If the square of the current prime limit is <= candidate,
        // we need to increment the limit
        if (primes[test_prime_limit] * primes[test_prime_limit] <= candidate) {
            test_prime_limit++;
        }
        
        // Test against primes from index 1 to test_prime_limit-1
        bool is_prime = true;
        for (uint64_t i = 1; i < test_prime_limit; i++) {
            if (candidate % primes[i] == 0) {
                is_prime = false;
                break;
            }
        }
        
        // If no divisors found, the candidate is prime
        if (is_prime) {
            primes.push_back(candidate);
            count++;
        }
        
        // Move to next odd candidate
        candidate += 2;
    }
    
    // Output the final prime
    std::cout << primes.back() << std::endl;
    
    return 0;
}
