#include <cstdlib>
#include <iostream> 
#include <iomanip>
#include <cmath>

#define N 3
#define NEW_LINE cout << endl << endl;


using namespace std;


void print_matrix(double** M)
{
    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j <= N; j++)
        {
            cout << M[i][j] << "  ";
        }
    }

    NEW_LINE    
}


double** inverse_matrix(double W[3][3])
{
    double** M;
    M = new double*[N];
    for (int i = 0; i < N; i++)
        M[i] = new double[N + 3];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            M[i][j] = W[i][j];

    for (int i = 0; i < N; i++)
        for (int j = N; j < N + N; j++)
            if (i == j - N) M[i][j] = 1;
            else M[i][j] = 0;

    // // //Output of matrix with inversed:
    // for (int i = 0; i < N; i++)
    // {
    //     cout << endl;
    //     for (int j = 0; j < N + N; j++)
    //         cout << M[i][j] << " "; 
    // }
    
    //NEW_LINE

    //Forward part
    for (int k = 0; k < N - 1; k++)
    {
        for (int i = k + 1; i < N; i++)
        {
            double ratio = M[i][k] / M[k][k];
            for (int j = k; j < N + N; j++)
            {
                M[i][j] += M[k][j] * ratio * -1;
            }
        }
    }    


    //Making 1 in main diagonal
    for (int k = 0; k < N; k++)
    {
        double elem = M[k][k];
        for (int i = k; i < N + N; i++)
        {
            M[k][i] /= elem;
        }
    }    

    
    //Backward part
    for (int k = N - 1; k >= 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            double ratio = M[i][k] / M[k][k];
            for (int j = N + N - 1; j >= k; j--)
            {
                M[i][j] += M[k][j] * ratio * -1;
            }
        }
    }

    // //Output of matrix with inversed:
    // for (int i = 0; i < N; i++)
    // {
    //     cout << endl;
    //     for (int j = 0; j < N + N; j++)
    //         cout << M[i][j] << " "; 
    // }

    // NEW_LINE

    double** RES = new double*[N];
    for (int i = 0; i < N; i++)
        RES[i] = new double[N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            RES[i][j] = M[i][j + N];

    // for (int i = 0; i < N; i++)
    // {
    //     cout << endl;
    //     for (int j = 0; j < N; j++)
    //         cout << RES[i][j] << " "; 
    // }   

    // NEW_LINE     

    return RES; 
}


double* F(double* X)
{
    double* FX = new double [3];

    FX[0] = X[0] * X[0] + X[1] * X[1] + X[2] * X[2] - 1;
    FX[1] = 2 * X[0] * X[0] + X[1] * X[1] - 4 * X[2];
    FX[2] = 3 * X[0] * X[0] - 4 * X[1] + X[2] * X[2];
 
    return FX;
}


double* matrix_vector(double** W, double* X) //multiply matrix on vector
{
    double* RES = new double[N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            RES[i] += W[i][j] * X[j];

    // for (int i = 0; i < N; i++)
    //     printf("%.3lf ", RES[i]);
    //     //cout << RES[i] << " ";

    //NEW_LINE         

    return RES;        
}


double* matrix_newton(double W[N][N])
{
    double* X0 = new double[N];
    for (int i = 0; i < N; i++) X0[i] = 0.5;

    for (int i = 0; i < 3; i++)
    {
        double **W_inv = inverse_matrix(W);
        double* FX = F(X0);
        double* Mult = matrix_vector(W_inv, FX);
        for (int j = 0; j < N; j++)
        {
            X0[j] -= Mult[j]; 
        } 
    }
    
    return X0;
}
 

int main(int argc, char** argv)
{
    double W[N][N] = {{1, 1, 1}, {2, 1, -4}, {3, -4, 1}};

    double* RES = matrix_newton(W);
    

    for (int i = 0; i < N; i++)
        cout << RES[i] << " ";

    NEW_LINE  

     
    return 0;
}