#include <iostream>
#include <vector>
#include <format>

// Function to check if a number is prime
bool is_prime(const std::vector<uint64_t>& primes, uint64_t candidate) {
    uint64_t test_prime_limit = primes.size();
    while (primes[test_prime_limit - 1] * primes[test_prime_limit - 1] <= candidate) {
        ++test_prime_limit;
    }
    for (size_t i = 0; i < test_prime_limit; ++i) {
        if (candidate % primes[i] == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    uint64_t number_of_primes;
    std::cin >> number_of_primes;

    if (number_of_primes <= 0) {
        std::cerr << "Number of primes must be greater than 0." << std::endl;
        return 1;
    }

    std::vector<uint64_t> primes;
    primes.reserve(number_of_primes);
    primes.push_back(2);
    if (number_of_primes > 1) {
        primes.push_back(3);
    }
    uint64_t candidate = 5;
    uint64_t test_prime_limit = 2;

    while (primes.size() < number_of_primes) {
        if (is_prime(primes, candidate)) {
            primes.push_back(candidate);
        }
        ++candidate;
    }

    // Output the prime numbers
    for (const auto& prime : primes) {
        std::cout << std::format("{} ", prime);
    }
    std::cout << std::endl;

    return 0;
}
