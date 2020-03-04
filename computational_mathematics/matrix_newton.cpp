#include <cstdlib>
#include <iostream> 
#include <iomanip>
#include <cmath>

#define N 3
#define NEW_LINE cout << endl << endl;

double M[N][N+1] = {{-3, 1, 2, 1}, {2, 1, -3, -4}, {-4, 2, 1, -2}}; 
//double M[N][N+1] = {{1, -2, 3, 2}, {3, 1, -1, 3}, {2, 5, 2, 9}}; 


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

    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j < N + N; j++)
            cout << M[i][j] << " "; 
    }
    
    NEW_LINE

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


    for (int i = 0; i < N; i++)
    {
        cout << endl;
        for (int j = 0; j < N + N; j++)
            cout << M[i][j] << " "; 
    }

    NEW_LINE

    return M; 
}



int main(int argc, char** argv)
{
    double W[N][N] = {{1, 1, 1}, {2, 1, -4}, {3, -4, 1}};
    double **W_inv = inverse_matrix(W);
     
    return 0;
}