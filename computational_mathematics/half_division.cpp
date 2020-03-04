#include <cstdlib>
#include <iostream> 
#include <iomanip>
#include <cmath>

#define N 100
#define e 0.00000001 

using namespace std;

long double f(long double x)
{
    return (x * x - 3);
}


long double count_c(long double a, long double b)
{
    return ((a + b) / 2);
}


long double half_division_method(long double a, long double b)
{
    //long double c = count_c(a, b);
    int step = 0;
    while (abs(b-a) / 2  > e)
    //for (int i = 0; i < N + 1; i++)
    {
        long double c = count_c(a, b);
        if (f(a) * f(c) < 0)
        {
            b = c;
            step++;
            continue;
        }
        if (f(c) * f(b) < 0)
        {
            a = c;
            step++;
        } 
    }
    cout << endl << step << endl;
    return count_c(a, b);
}


int main()
{
    long double a = 1;
    long double b = 2;

    long double result = half_division_method(a, b);
    //cout << endl << "Result: " << result << endl << endl;
    printf("\n Result: %.10Lf \n", result);
    return 0;
}