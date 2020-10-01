#include <iostream>     // std::cout and printf
#include <vector>       // std::vector
//#include <math.h>       // quick maffs


enum class _OutputFormat {
    COMMA_NO_SPACE,
    COMMA_SPACE,
    PARENTHESES,
    BRACES,
    BRACKETS
};

int input;
bool is_prime(int);
std::vector<int>* prime_factorize(int);
void print_prime_factors_inner(std::vector<int>&);
void print_prime_factors(std::vector<int>&, _OutputFormat);


/// <summary>
/// Checks to see if <c>n</c> is prime or not.
/// </summary>
/// <param name="n">integer to be ckecked</param>
/// <returns>true if <c>n</c> is prime, false if not</returns>
bool is_prime(unsigned int n)
{
    if (n <= 1)
        return false;
    unsigned int upper = (unsigned int)sqrt((float)n);

    for (unsigned int i = 2; i < upper; i++) {
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
std::vector<unsigned int>* prime_factorize(unsigned int n)
{
    std::vector<unsigned int>* factors = new std::vector<unsigned int>;
    std::vector<unsigned int>* all_factors = new std::vector<unsigned int>;
    for (unsigned int i = 2; i < n; i++)
    {
        if (n % 1 == 0 && is_prime(i))
            factors->push_back(i);
    }
    unsigned int i = 0;
    while (n != 1) {
        if (n % factors->at(i) == 0)
            all_factors->push_back(factors->at(i));
        else
            i++;
    }
    return all_factors;
}

/// <summary>
/// Prints the prime factors in a number of different ways. The default is set to (square)BRACKETS []
/// </summary>
/// <param name="result"><c>std::vector</c> made up of prime factors</param>
/// <param name="format">which output format you would like</param>
void print_prime_factors(std::vector<int>& result, _OutputFormat format = _OutputFormat::BRACKETS)
{
    if (result.empty()) {
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
            for (auto n : result)
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
void print_prime_factors_inner(std::vector<int>& result)
{
    for (auto n : result)
        std::cout << n << ", ";
    std::cout << "\b\b";
}


int main(int argc, char** argv)
{
    extern int input;

    /**
    * TODO: Print error message when given decimal input
    */

    if (argc != 2) {
        fprintf(stderr, "Usage: %s [number]\n", argv[0]);
        return EXIT_FAILURE;
    }
    else if (atoi(argv[1]) <= 0) {
        fprintf(stderr, "Usage: %s [number]\n", argv[0]);
        return EXIT_FAILURE;
    }
    else if (atoi(argv[1]) >= INT_MAX){
        fprintf(stderr, "Input number is too big! Input limits are %i to %i\n", 0, INT_MAX);
        return EXIT_FAILURE;
    }
    else {
        input = atoi(argv[1]);
        std::vector<int>* result = prime_factorize(input);
        print_prime_factors(*result);
        delete result;
    }

    return EXIT_SUCCESS;
}