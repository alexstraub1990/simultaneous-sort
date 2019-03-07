#include "simultaneous_sort.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

int main()
{
    // Create some test arrays
    std::vector<int>         a{  0,   7,   6,   1,   8,   3  };
    std::array<double, 6>    b{ 0.4, 1.0, 3.0, 5.2, 1.4, 9.0 };
    std::vector<std::string> c{ "a", "b", "c", "d", "e", "f" };

    // Sort (a) in ascending order and reorder all others
    std::cout << "Ascending (first row): " << std::endl;

    sort(a, b, c);

    std::cout << a[0] << "\t" << a[1] << "\t" << a[2] << "\t" << a[3] << "\t" << a[4] << "\t" << a[5] << std::endl;
    std::cout << b[0] << "\t" << b[1] << "\t" << b[2] << "\t" << b[3] << "\t" << b[4] << "\t" << b[5] << std::endl;
    std::cout << c[0] << "\t" << c[1] << "\t" << c[2] << "\t" << c[3] << "\t" << c[4] << "\t" << c[5] << std::endl << std::endl;

    // Sort (b) in decending order and reorder all others
    std::cout << "Decending (second row): " << std::endl;

    sort_with([](const double lhs, const double rhs) { return lhs > rhs; } , b, a, c);

    std::cout << a[0] << "\t" << a[1] << "\t" << a[2] << "\t" << a[3] << "\t" << a[4] << "\t" << a[5] << std::endl;
    std::cout << b[0] << "\t" << b[1] << "\t" << b[2] << "\t" << b[3] << "\t" << b[4] << "\t" << b[5] << std::endl;
    std::cout << c[0] << "\t" << c[1] << "\t" << c[2] << "\t" << c[3] << "\t" << c[4] << "\t" << c[5] << std::endl << std::endl;

    // Test with large randomly-filled arrays
    std::vector<int> random_vector(10000);
    std::vector<double> double_vector(10000);

    std::iota(random_vector.begin(), random_vector.end(), 0);

    double value = 0.0;
    std::transform(double_vector.begin(), double_vector.end(), double_vector.begin(), [&value](double) { return value; value += 0.1; });

    const std::vector<int> base = random_vector;

    std::random_device rd;
    std::mt19937 g(rd());

    bool correct = true;

    for (std::size_t test_index = 0; test_index < 100; ++test_index)
    {
        std::shuffle(random_vector.begin(), random_vector.end(), g);

        sort(random_vector, double_vector);

        correct &= random_vector == base;
    }

    if (!correct)
    {
        std::cerr << "Oops! Something went wrong..." << std::endl;
    }

    return static_cast<int>(!correct);
}
