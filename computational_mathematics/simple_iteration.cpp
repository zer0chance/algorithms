#include <cstdlib>
#include <iostream> 
#include <iomanip>
#include <cmath>

#define e 0.0001
#define N 3

//double M[N][N+1] = {{-3, 1, 2, 1}, {2, 1, -3, -4}, {-4, 2, 1, -2}}; 
//double M[N][N+1] = {{1, -2, 3, 2}, {3, 1, -1, 3}, {2, 5, 2, 9}}; 
double M[N][N+1] = {{5, -1, 2, 3}, {-1, 4, 1, 6}, {2, -1, -10, -21}}; 


using namespace std;


double max(double a,double b, double c) 
{
   double max = (a < b) ? b : a;
   return ((max < c) ? c : max);
}


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


void iterating (double ( &C)[3][3], double B[], int n)
{
    double R[N], X[N];
    for (int i = 0; i < N; i++)
    {
        X[i] = B[i];
    }
    //Multiplying matrix and vector
    for (int i = 0; i <= n; i++)
    {
        for (int i = 0; i < N; i++)
        {
            R[i] = 0;
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


int epsilon(double ( &C)[3][3], double B[])
{
    double matrix_norm = max(C[0][1] + C[0][2], C[1][0] + C[1][2], C[2][0] + C[2][1]);
    double b_norm = max(B[0], B[1], B[2]);
    return ceil(log( log(e * (1 - matrix_norm) / b_norm) / log(matrix_norm) ));
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

    int n = epsilon(C, B);
    cout << endl << " N = " << n << endl;
    iterating(C, B, n);

    return 0;
}