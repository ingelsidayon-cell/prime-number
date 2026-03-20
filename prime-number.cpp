#include <iostream>
#include <vector>
#include <cstdint>

uint64_t findNthPrime(int n) {
    if (n == 0) return 2;
    if (n == 1) return 2;
    if (n == 2) return 3;

    std::vector<uint64_t> primes = {2, 3};
    uint64_t candidate = 5;
    int test_prime_limit = 2; // Starting from the first prime number greater than 3

    while (primes.size() < n) {
        if (static_cast<uint64_t>(primes[test_prime_limit] * primes[test_prime_limit]) <= candidate) {
            ++test_prime_limit;
        }

        bool isPrime = true;
        for (int i = 1; i < test_prime_limit && primes[i] * primes[i] <= candidate; ++i) {
            if (candidate % primes[i] == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime) {
            primes.push_back(candidate);
        }

        candidate += 2; // Test only odd numbers
    }

    return primes.back();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_primes>" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);
    if (n < 0) {
        std::cerr << "Number of primes must be a non-negative integer." << std::endl;
        return 1;
    }

    uint64_t nthPrime = findNthPrime(n);
    std::cout << nthPrime << std::endl;

    return 0;
}
