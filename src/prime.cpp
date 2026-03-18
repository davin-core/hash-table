#include<cmath>
#include "prime.h"

// check if it is a prime number 

bool _is_prime(int n) {
    if (n <= 1) return false; // 0 and 1 are not prime
    if (n <= 3) return true;  // 2 and 3 are prime
    if (n % 2 == 0 || n % 3 == 0) return false; // eliminate multiples of 2 and 3

    for (int i = 5; i * i <= n; i += 6) { // check for factors from 5 to sqrt(n)
        if (n % i == 0 || n % (i + 2) == 0) return false; // check for factors of the form 6k ± 1
    }
    return true;
}

// find the next prime number after n 
int next_prime(int n) {
    while (true) {
        if (_is_prime(n)) return n; // if n is prime, return it
        n++; // otherwise, check the next number
    }
}