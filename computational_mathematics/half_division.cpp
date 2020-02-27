#include <cstdlib>
#include <iostream> 
#include <iomanip>
#include <cmath>

#define N 3

using namespace std;

double f(double x)
{
    return (x * x - 3);
}


double count_c(double a, double b)
{
    return ((a + b) / 2);
}


double half_division_method(double a, double b)
{
    for (int i = 0; i < N; i++)
    {
        double c = count_c(a, b);
        if (f(a) * f(c) < 0)
        {
            b = c;
            continue;
        }
        if (f(c) * f(b) < 0)
        {
            a = c;
        } 
    }

    return count_c(a, b);
}


int main()
{
    double a = 1;
    double b = 2;

    double result = half_division_method(a, b);
    cout << endl << "Result: " << result << endl << endl;

    return 0;
}