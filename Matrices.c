#include <stdio.h>

#define N 3

// Functions to print a matrix

void print(int mat[N][N]);
void printDB(double mat[N][N]); // to print double type result matrix

// Function to get sum

void add(int mat1[N][N], int mat2[N][N], int result[N][N]);

// Function to get difference

void sub(int mat1[N][N], int mat2[N][N], int result[N][N]);

// Function to get product

void mult(int mat1[N][N], int mat2[N][N], int result[N][N]);

// Helper functions to calculate minor

void getMinor(int n, int mat[n][n], int row, int col, int minor[n - 1][n - 1]);
int cofactor(int row, int col, int detVal);

// Function to return determinant

int det(int n, int mat[n][n]);

// Function to prigetnt transverse

void transverse(int mat[N][N], int result[N][N]);

// Function to get adjoint

void adj(int n, int mat[n][n], int result[n][n]);

// Function to get inverse

void inv(int mat[N][N], double resultDB[N][N]);

int main()
{
    // take values in a NxN matrix
    int mat1[N][N] = {0};
    int mat2[N][N] = {0};
    int result[N][N];
    double resultDB[N][N];
    int (*vars[])[N] = {mat1, mat2};
    int x = 0;
    printf("Enter number of matrices: ");
    scanf("%d", &x);
    for (int n = 0; n < x; n++)
    {
        printf("Enter matrix %d: \n", n + 1);
        for (int i = 0; i < N; i++)
        {
            if (scanf("%d %d %d", &vars[n][i][0], &vars[n][i][1], &vars[n][i][2]) != N) // not made for any value of N other than 3 yet!!
            {
                printf("Invalid Output\n");
                return 1;
            }
        }
    }
    inv(mat1, resultDB);
    printDB(resultDB);
    return 0;
}

// =====================Function definitions======================

void print(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%4d", mat[i][j]);
        }
        printf("\n");
    }
}

void printDB(double mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%.1f ", mat[i][j]);
        }
        printf("\n");
    }
}

void add(int mat1[N][N], int mat2[N][N], int result[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void sub(int mat1[N][N], int mat2[N][N], int result[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
}

void mult(int mat1[N][N], int mat2[N][N], int result[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

int det(int n, int mat[n][n])
{
    if (n == 1)
    {
        return mat[0][0];
    }
    if (n == 2)
    {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
    int res = 0;

    for (int p = 0; p < n; p++) // p -> column to be removed from the original matrix to make it smaller
    {
        int minor[n - 1][n - 1];
        getMinor(n, mat, 0, p, minor);

        // expanding along row 0, varying column p
        res += (p % 2 == 0 ? 1 : -1) * mat[0][p] * det(n - 1, minor);
    }

    return res;
}

void transverse(int mat[N][N], int result[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result[i][j] = mat[j][i];
        }
    }
}

void getMinor(int n, int mat[n][n], int row, int col, int minor[n - 1][n - 1])
{
    int r = 0, c = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == row)
            continue;
        c = 0;
        for (int j = 0; j < n; j++)
        {
            if (j == col)
                continue;
            minor[r][c++] = mat[i][j];
        }
        r++;
    }
}

int cofactor(int row, int col, int detVal)
{
    return ((row + col) % 2 == 0 ? 1 : -1) * detVal;
}

void adj(int n, int mat[n][n], int result[n][n])
{
    if (n == 1)
    {
        result[0][0] = 1;
        return;
    }
    int temp[n - 1][n - 1];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            getMinor(n, mat, i, j, temp);
            result[j][i] = cofactor(i, j, det(n - 1, temp));
        }
    }
}

void inv(int mat[N][N], double resultDB[N][N])
{
    int determinant = det(N, mat);
    if (determinant == 0)
    {
        printf("Determinant is zero, hence inverse doesn't exist.");
        return;
    }
    int adjMat[N][N];
    adj(N, mat, adjMat);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            resultDB[i][j] = (double)adjMat[i][j] / determinant;
        }
    }
}
