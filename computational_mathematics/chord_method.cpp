#include <cstdlib>
#include <iostream> 
#include <iomanip>
#include <cmath>

#define N 3
#define e 0.00000001 

using namespace std;


double f(double x)
{
    return (x * x - 3);
}


double count_c(double a, double b)
{
    return ((a * f(b) - b * f(a)) / (f(b) - f(a)));
}


double chord_method(double a, double b)
{
    double c1 = count_c(a, b);
    double c2 = 0;
    int steps = 0;
    do
    //for (int i = 0; i < N; i++)
    {
        c1 = count_c(a, b);
        if (f(a) * f(c1) < 0)
        {
            b = c1;
            steps++;
            continue;
        }
        if (f(c1) * f(b) < 0)
        {
            a = c1;
            steps++;
        } 
        c2 = count_c(a, b);
    } while (c2 - c1 > e);

    cout << endl << steps << endl;
    return count_c(a, b);
}


int main()
{
    double a = 1;
    double b = 2;

    double result = chord_method(a, b);
    //cout << endl << "Result: " << result << endl << endl;
    printf("\n Result: %.10lf \n", result);
    return 0;
}