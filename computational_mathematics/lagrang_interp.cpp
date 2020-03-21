#include <iostream>
#include <cmath>

#define N 4

using namespace std;


double X[N] = {1, 2, 3, 4};
double Y[N] = {1.0000, 1.4142, 1.7321, 2.0000};


double P(double x)
{
    double result = 0;

    for (int i = 0; i < N; i++)
    {
        double fraction = 1;  
        for (int j = 0; j < N; j++)
        {
            if (i != j)
                fraction *= (x - X[j]) / (X[i] - X[j]);    
        } 
        result += Y[i] * fraction;
    }

    return result;    
}


int main()
{
    printf(" \n\n Result: %lf\n\n", P(static_cast<double>(1)));

    return 0;
}