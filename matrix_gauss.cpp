#include <cstdlib>
#include <iostream> 
#include <iomanip>

#define N 3

//double M[N][N+1] = {{1, -2, 3, 2}, {3, 1, -1, 3}, {2, 5, 2, 9}}; 
double M[N][N+1] = {{-3, 1, 2, 1}, {2, 1, -3, -4}, {-4, 2, 1, -2}}; 


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


int main(int argc, char** argv)
{
    print_matrix();

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
            // double ratio = M[i][k] / M[k][k];
            // for (int j = k; j <= N; j++)
            // {
            //     M[i][j] += M[k][j] * ratio * -1;
            // }
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

   
    
    print_matrix();
    
    return 0;
}