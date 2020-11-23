#include <iostream>     // std::cout and printf
#include <vector>       // std::vector
#include <math.h>       // sqrt
#include <limits.h>     // INT_MAX
#include <stdlib.h>     // strtoull


enum class _OutputFormat {
    COMMA_NO_SPACE,
    COMMA_SPACE,
    PARENTHESES,
    BRACES,
    BRACKETS
};

uint64_t input;                                                     /* Walla bror, dette er input as */
bool is_prime(uint64_t);
std::vector<uint64_t>* prime_factorize(uint64_t);
void print_prime_factors_inner(std::vector<uint64_t>*);
void print_prime_factors(std::vector<uint64_t>*, _OutputFormat);


/// <summary>
/// Checks to see if <c>n</c> is prime or not.
/// </summary>
/// <param name="n">integer to be ckecked</param>
/// <returns>true if <c>n</c> is prime, false if not</returns>
bool is_prime(uint64_t n)
{
    if (n <= 1)
        return false;
    uint64_t upper = (uint64_t)sqrt((float)n);

    for (uint64_t i = 2; i < upper; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

/// <summary>
/// Find prime factors of <c>n</c>.
/// </summary>
/// <param name="n">Integer number to find the prime factors of</param>
/// <returns>Returns a <c>std::vector</c> of prime factors of <c>n</c></returns>
std::vector<uint64_t>* prime_factorize(uint64_t n)
{
    std::vector<uint64_t>* all_factors = new std::vector<uint64_t>;
    std::vector<uint64_t> factors;
    if (n % 2 == 0)
        factors.push_back(2);
    for (uint64_t i = 3; i <= n; i += 2)
    {
        if (n % i == 0 && is_prime(i))
            factors.push_back(i);
    }
    size_t j = 0;
    while (n != 1) {
        if (n % factors.at(j) == 0) {
            all_factors->push_back(factors.at(j));
            n /= factors.at(j);
        } else {
            j++;
        }
    }
    return all_factors;
}

/// <summary>
/// Prints the prime factors in a number of different ways. The default is set to (square)BRACKETS []
/// </summary>
/// <param name="result"><c>std::vector</c> made up of prime factors</param>
/// <param name="format">which output format you would like</param>
void print_prime_factors(std::vector<uint64_t>* result, _OutputFormat format = _OutputFormat::BRACKETS)
{
    if (result->empty()) {
        switch (format)
        {
            /*
            case _OutputFormat::COMMA_NO_SPACE: std::cout <<  ""    << std::endl; break;
            case _OutputFormat::COMMA_SPACE:    std::cout <<  ""    << std::endl; break;
            */
            case _OutputFormat::PARENTHESES:    std::cout << "()"   << std::endl; break;
            case _OutputFormat::BRACES:         std::cout << "{}"   << std::endl; break;
            case _OutputFormat::BRACKETS:       std::cout << "[]"   << std::endl; break;
            default: std::cout << "[]" << std::endl;
        }
    } else {
        switch (format)
        {
        case _OutputFormat::COMMA_NO_SPACE:
            for (auto n : *result)
                std::cout << n << ",";
            std::cout << "\b " << std::endl;
            break;
        case _OutputFormat::COMMA_SPACE:
            print_prime_factors_inner(result);
            std::cout << " " << std::endl;
            break;
        case _OutputFormat::PARENTHESES:
            std::cout << "(";
            print_prime_factors_inner(result);
            std::cout << ")" << std::endl;
            break;
        case _OutputFormat::BRACES:
            std::cout << "{";
            print_prime_factors_inner(result);
            std::cout << "}" << std::endl;
            break;
        case _OutputFormat::BRACKETS:
            std::cout << "[";
            print_prime_factors_inner(result);
            std::cout << "]" << std::endl;
            break;
        }
    }
}

// Helper function for `print_prime_factors`
void print_prime_factors_inner(std::vector<uint64_t> *result)
{
    for (auto n : *result)
        std::cout << n << ", ";
    std::cout << "\b\b";
}

int main(int argc, char** argv)
{
    char* pEnd;
    input = strtoull(argv[1], &pEnd, 10);

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [number]\n", argv[0]);
        fprintf(stderr, "Wrong amount of arguments\n");
        return EXIT_FAILURE;
    }
    else if (input <= 0 || input >= ULLONG_MAX){
        fprintf(stderr, "Input of out range! Input limits are %i to %llu\n", 1, ULLONG_MAX);
        return EXIT_FAILURE;
    }
    else {
        std::vector<uint64_t>* result = prime_factorize(input);
        print_prime_factors(result);
        delete result;
        return EXIT_SUCCESS;
    }
}
