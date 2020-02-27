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


double derivative(double x)
{
    return (2 * x);
}


double newton_method(double a, double b, double x0)
{
    double x;
    for (int i = 0; i < N; i++)
    {
        x = x0 - f(x0) / derivative(x0);
        x0 = x;
    }

    return (x0 - f(x0) / derivative(x0));
}


int main()
{
    double a = 1;
    double b = 2;

    double result = newton_method(a, b, 2);
    cout << endl << "Result: " << result << endl << endl;

    return 0;
}   