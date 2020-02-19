#include <cstdlib>
#include <iostream> 
#include <iomanip>
#include <math.h>

#define e 3
#define N 3

//double M[N][N+1] = {{-3, 1, 2, 1}, {2, 1, -3, -4}, {-4, 2, 1, -2}}; 
//double M[N][N+1] = {{1, -2, 3, 2}, {3, 1, -1, 3}, {2, 5, 2, 9}}; 
double M[N][N+1] = {{5, -1, 2, 3}, {-1, 4, 1, 6}, {2, -1, -10, -21}}; 



using namespace std;


void print_matrix()
{
    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j <= N; j++)
        {
            cout << M[i][j] << "  ";
        }
    }
    
    cout << endl << endl;
}


void print_matrix(double ( &M)[3][3])
{
    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j < N; j++)
        {
            cout << M[i][j] << "  ";
        }
    }
    
    cout << endl << endl;
}


void print_vector(double B[])
{
    for (int i = 0; i < N; i ++)
    {
        cout << " " << B[i] << endl;
    }
}


void divide()
{
    for (int i = 0; i < N; i++)
    {
        double elem = M[i][i];
        for(int j = 0; j <= N; j++)
        {
            M[i][j] /= elem;
        }
    }
}


void iterating (double ( &C)[3][3], double B[])
{
    double R[N], X[N], Temp[N];
    for (int i = 0; i < N; i++)
    {
        X[i] = B[i];
    }
    //Multiplying matrix and vector
    for (int i = 0; i < e; i++)
    {
        for (int i = 0; i < N; i++)
        {
            R[i] = 0;
            Temp[i] = B[i];
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                R[i] += C[i][j] * X[j];
            }
        }

        for (int i = 0; i < N; i++)
        {
            X[i] = B[i] - R[i];
        }
    }
    print_vector(X);
} 



int main ()
{
    print_matrix();
    divide();
    print_matrix();

    double C[N][N];
    
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j != i)
            {
                C[i][j] = M[i][j];
            }
            else 
            {
                C[i][j] = 0;
            }
        }
    }

    double B[N];
    for (int i = 0; i < N; i++)
    {
        B[i] = M[i][N];
    }

    //print_matrix(C);
    //print_vector(B);
    iterating(C, B);

    return 0;
}