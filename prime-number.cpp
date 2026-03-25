#include <vector>
#include <cmath>
#include <iostream>
#include <cstdint>


using namespace std;

int main() {
    int n;
    cout << "Enter the position of the prime you want: ";
    cin >> n;

    vector<uint64_t> primes;

    if (n >= 1) {
        primes.push_back(2);
    }

    if (n >= 2) {
        primes.push_back(3);
    }

    uint64_t candidate = 5;
    while (primes.size() < n) {
        bool is_prime_candidate = true;

        for (auto p : primes) {
            if (p * p > candidate) {
                break;
            }
            if (candidate % p == 0) {
                is_prime_candidate = false;
                break;
            }
        }

        if (is_prime_candidate) {
            primes.push_back(candidate);
        }

        candidate += 2; // Check next odd number
    }

    cout << "The " << n << "-th prime is: " << primes.back() << endl;

    return 0;
}
