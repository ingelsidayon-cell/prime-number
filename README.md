This was a test of local models, to see if they could write code that was 
not in their memories.

unsloth/Qwen3-Coder-30B-A3B-Instruct-1M-GGUF managed it.  The rest generally failed or crashed.

Note that because unsloth/Qwen3-Coder-30B-A3B-Instruct-1M-GGUF managed it once, might not succeed twice.

They mostly could not.  I don't know if the big cloud models can do any better.

I tried to get them to follow the instructions:

----------

Give me a c++ program that sieves the prime numbers, using the algorithm that it builds a list of prime numbers rather than having a list of all numbers less than the limit, and tests each number against prime numbers previously found and pushed into the vector of primes.   Assume all integers will fit in uint64_t.  Ignore the overflow issue.

Take the number of primes, `number_of_primes`, to be generated as a command line argument, which argument is the number of primes to find, not the highest number to be tested for primality -- there should be a vector of primes in which all primes are pushed, but not a vector of numbers, into which all numbers are pushed.   The program should output the final prime.

The program should be called prime-number, and `prime-number 1` should output 2,   `prime-number 2` should output 3, `prime-number 3` should output 5, `prime-number 4` should output 7, `prime-number 5` should output 11, and `prime-number 983`  should output 7753, and  `prime-number 12345678` should output 224284387

If the argument is not a positive integer, should issue the error message "argument should be a natural number"

We initialise primes to hold 2 and 3, and set test_prime_limit=2,  We test candidates for primality starting at five and incrementing by two.

```C++
	// Initialize primes vector with first two primes
	std::vector<uint64_t> primes;
	primes.reserve(number_of_primes);
	primes.push_back(2);
	primes.push_back(3);
	uint64_t candidate = 5;  // First candidate to test
	uint64_t test_prime_limit = 2;  // Index to determine how many primes to test against
```

However when the argument `number_of_primes` is 1 or 2, the while loop `while (primes.size() < target_count) {` never executes, and it immediately drops through to output the answer , so the initialisation of `candidate` and `test_prime_limit` has no effect, so it will not matter that they are invalid for cases 1 and 2.  So we should find it unneccessary  to special case `prime-number 1` and `prime-number 2`

For each candidate, if primes[test_prime_limit-1]*primes[test_prime_limit-1] is less than or equal to  the candidate, we increment test_prime_limit
 
we then test the candidate against primes from primes[1] to primes[test_prime_limit-1]. 


If the candidate passes test for each prime it is tested against, push it to primes.

Do not check against the sqrt of candidate, as the check on test_prime_limit `primes[test_prime_limit]*primes[test_prime_limit] is less than or equal to  the candidate limit already accomplishes the same thing.

Use the C++20 feature std::format for output.

Generate C++ code to accomplish this, and a CMakeLists.txt file to build the code.

The CMakeLists.txt file should force C++20 compilation with

```cmake
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

----------


Common errors.  

1. Fails to correctly handle not a natural number.

2. Inserts random code regarding sqrt of candidate.

3. Test primes[0]to primes [test_prime_limit-1]

4. Fails to push the passing candidate, resulting in wild reads and a crash with the uninformative error message floating point error.