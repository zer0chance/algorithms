#include <cstdlib>
#include <iostream> 
#include <iomanip>

#define N 3

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


void gauss_metod_simple()
{
    //Forward part
    for (int k = 0; k < N - 1; k++)
    {
        for (int i = k + 1; i < N; i++)
        {
            double ratio = M[i][k] / M[k][k];
            for (int j = k; j <= N; j++)
            {
                M[i][j] += M[k][j] * ratio * -1;
            }
        }
    }    


    //Making 1 in main diagonal
    for (int k = 0; k < N; k++)
    {
        double elem = M[k][k];
        for (int i = k; i <= N; i++)
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
            for (int j = N; j >= k; j--)
            {
                M[i][j] += M[k][j] * ratio * -1;
            }
        }
    }    
}


void gauss_metod_upgrade()
{
    //Forward part
    for (int k = 0; k < N - 1; k++)
    {
        int row = k;
        for (int z = k + 1; z < N; z++)
        {
            if (M[z][k] > M[row][k]) row = z;            
        }
        if (row != k)
        {
            for (int j = k; j <= N; j++)
            {
                double temp = M[k][j];
                M[k][j] = M[row][j];
                M[row][j] = temp;
            }
        }

        for (int i = k + 1; i < N; i++)
        {
            double ratio = M[i][k] / M[k][k];
            for (int j = k; j <= N; j++)
            {
                M[i][j] += M[k][j] * ratio * -1;
            }
        }
    }    


    //Making 1 in main diagonal
    for (int k = 0; k < N; k++)
    {
        double elem = M[k][k];
        for (int i = k; i <= N; i++)
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
            for (int j = N; j >= k; j--)
            {
                M[i][j] += M[k][j] * ratio * -1;
            }
        }
    }    
}


int main(int argc, char** argv)
{
    print_matrix();

    int method = 0;
    cout << "Simple or upgraded method? 1/2 : ";
    while (method != 1 && method != 2)
    {
        cin >> method;
    }

    if (method == 1) 
        gauss_metod_simple();
    else 
        gauss_metod_upgrade();
    
    print_matrix();
    
    return 0;
}