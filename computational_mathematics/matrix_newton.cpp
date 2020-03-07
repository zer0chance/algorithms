#include <cstdlib>
#include <iostream> 
#include <iomanip>
#include <cmath>

#define N 3
#define NEW_LINE cout << endl << endl;
#define e 0.00000001


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


double** inverse_matrix(double** W)
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

    double** RES = new double*[N];
    for (int i = 0; i < N; i++)
        RES[i] = new double[N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            RES[i][j] = M[i][j + N];   

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


double** W1(double* X)
{
    double** W = new double*[3];
    for (int i = 0; i < 3; i++) W[i] = new double[3];

    W[0][0] = 2 * X[0];
    W[0][1] = 2 * X[1];
    W[0][2] = 2 * X[2];

    W[1][0] = 4 * X[0];
    W[1][1] = 2 * X[1];
    W[1][2] = -4;

    W[2][0] = 6 * X[0];
    W[2][1] = -4;
    W[2][2] = 2 * X[2];

    return W;
}

double* matrix_vector(double** W, double* X) //multiply matrix on vector
{
    double* RES = new double[N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            RES[i] += W[i][j] * X[j];

    return RES;        
}


double* matrix_newton()
{
    double* X0 = new double[N];
    double* Xt = new double[N];

    double** W;
    double** W_inv;
    int step = 0;

    for (int i = 0; i < N; i++)
    {
        X0[i] = 0.5;
        Xt[i] = 0;
    }


    while (abs(X0[0] - Xt[0]) > e || abs(X0[1] - Xt[1]) > e || abs(X0[2] - Xt[2]) > e)
    {
        step++;
        W = W1(X0);
        W_inv = inverse_matrix(W);
        for (int i = 0; i < N; i++)
        {
            Xt[i] = X0[i];
        }
        double* FX = F(X0);
        double* Mult = matrix_vector(W_inv, FX);
        for (int j = 0; j < N; j++)
        {
            X0[j] -= Mult[j]; 
        } 

        cout << endl << "Step " << step << ": ";
        for (int j = 0; j < N; j++)
        {
            cout << setprecision(10) << X0[j] << " ";

        } 
    }
    
    return X0;
}
 

int main(int argc, char** argv)
{     
    double* RES = matrix_newton(/*W*/);

    NEW_LINE  
     
    return 0;
}