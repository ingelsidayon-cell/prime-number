// prime-number.cpp
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <charconv>
#include <format>

bool isPrime(uint64_t candidate, const std::vector<uint64_t>& primes, uint64_t& test_prime_limit) {
    // If we need to check more primes, extend our limit
    while (primes[test_prime_limit - 1] * primes[test_prime_limit - 1] <= candidate) {
        test_prime_limit++;
    }
    
    // Test against all primes up to sqrt(candidate)
    for (size_t i = 1; i < test_prime_limit; i++) {
        if (candidate % primes[i] == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_primes>" << std::endl;
        return 1;
    }
    
    std::string input(argv[1]);
    uint64_t number_of_primes;
    
    // Parse the command line argument
    auto [ptr, ec] = std::from_chars(input.data(), input.data() + input.size(), number_of_primes);
    if (ec != std::errc{} || ptr != input.data() + input.size()) {
        std::cerr << "argument should be a natural number" << std::endl;
        return 1;
    }
    
    if (number_of_primes == 0) {
        std::cerr << "argument should be a natural number" << std::endl;
        return 1;
    }
    
    // Initialize primes vector with first two primes
    std::vector<uint64_t> primes;
    primes.reserve(number_of_primes);
    primes.push_back(2);
    primes.push_back(3);
    uint64_t candidate = 5;  // First candidate to test
    uint64_t test_prime_limit = 2;  // Index to determine how many primes to test against
    
    // Generate primes until we have enough
    while (primes.size() < number_of_primes) {
        if (isPrime(candidate, primes, test_prime_limit)) {
            primes.push_back(candidate);
        }
        candidate += 2;  // Only check odd numbers
    }
    
    // Output the final prime
    std::cout << std::format("{}", primes[number_of_primes - 1]) << std::endl;
    
    return 0;
}
