#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstdint>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: prime-number <number_of_primes>" << endl;
        return 1;
    }

    string arg = argv[1];
    if (arg.empty()) {
        cout << "argument should be a natural number" << endl;
        return 1;
    }

    bool isNatural = true;
    for (char c : arg) {
        if (!isdigit(c)) {
            isNatural = false;
            break;
        }
    }
    if (!isNatural || arg[0] == '0') {
        cout << "argument should be a natural number" << endl;
        return 1;
    }

    unsigned long long number_of_primes = stoull(arg);
    if (number_of_primes == 0) {
        cout << "argument should be a natural number" << endl;
        return 1;
    }

    vector<uint64_t> primes;
    primes.reserve(number_of_primes);
    primes.push_back(2);
    primes.push_back(3);

    if (number_of_primes == 1) {
        cout << primes[0] << endl;
        return 0;
    } else if (number_of_primes == 2) {
        cout << primes[1] << endl;
        return 0;
    }

    uint64_t candidate = 5;
    uint64_t test_prime_limit = 2;

    while (primes.size() < number_of_primes) {
        // Check if we need to increase test_prime_limit
        if (primes[test_prime_limit - 1] * primes[test_prime_limit - 1] <= candidate) {
            test_prime_limit++;
        }

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

        candidate += 2;
    }

    cout << primes.back() << endl;
    return 0;
}