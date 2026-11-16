
#include <stdio.h>
#include <math.h>

int main() {
    int a[5][5], b[5][5];
    int r, c, i, j;
    int zero = 1, diagonal = 1;
    int upper = 1, lower = 1;
    int symmetric = 1, skew = 1;
    int identity = 1, scalar = 1;
    int idempotent = 1, nilpotent = 1;

    printf("Enter rows and columns: ");
    scanf("%d %d", &r, &c);

    if (r < 1 || r > 5 || c < 1 || c > 5) {
        printf("Invalid matrix size!");
        return 0;
    }

    printf("Enter matrix elements:\n");

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // Check basic matrix types

    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {

            if (a[i][j] != 0)
                zero = 0;

            if (i != j && a[i][j] != 0)
                diagonal = 0;

            if (i > j && a[i][j] != 0)
                upper = 0;

            if (i < j && a[i][j] != 0)
                lower = 0;
        }
    }

    if (r == c) {
        for (i = 0; i < r; i++) {
            for (j = 0; j < c; j++) {

                if (a[i][j] != a[j][i])
                    symmetric = 0;

                if (a[i][j] != -a[j][i])
                    skew = 0;

                if (i == j) {
                    if (a[i][j] != 1)
                        identity = 0;

                    if (i > 0 && a[i][j] != a[0][0])
                        scalar = 0;
                }
            }
        }

        // Check idempotent matrix (A*A = A)

        for (i = 0; i < r; i++) {
            for (j = 0; j < c; j++) {
                int sum = 0;

                for (int k = 0; k < r; k++)
                    sum += a[i][k] * a[k][j];

                if (sum != a[i][j])
                    idempotent = 0;
            }
        }

        // Check nilpotent matrix (A^n = 0)

        int temp[5][5], power[5][5];

        for (i = 0; i < r; i++)
            for (j = 0; j < c; j++)
                power[i][j] = a[i][j];

        for (int p = 1; p < r; p++) {
            for (i = 0; i < r; i++) {
                for (j = 0; j < r; j++) {
                    temp[i][j] = 0;

                    for (int k = 0; k < r; k++)
                        temp[i][j] += power[i][k] * a[k][j];
                }
            }

            for (i = 0; i < r; i++)
                for (j = 0; j < r; j++)
                    power[i][j] = temp[i][j];
        }

        for (i = 0; i < r; i++) {
            for (j = 0; j < r; j++) {
                if (power[i][j] != 0)
                    nilpotent = 0;
            }
        }
    }

    // Display basic types

    printf("\n--- MATRIX TYPES ---\n");

    if (r == c)
        printf("Square Matrix\n");
    else
        printf("Rectangular Matrix\n");

    if (zero)
        printf("Zero Matrix\n");

    if (r == 1)
        printf("Row Matrix\n");

    if (c == 1)
        printf("Column Matrix\n");

    if (r == c) {
        if (diagonal)
            printf("Diagonal Matrix\n");

        if (identity)
            printf("Identity Matrix\n");

        if (scalar && diagonal)
            printf("Scalar Matrix\n");

        if (upper)
            printf("Upper Triangular Matrix\n");

        if (lower)
            printf("Lower Triangular Matrix\n");

        if (symmetric)
            printf("Symmetric Matrix\n");

        if (skew)
            printf("Skew-Symmetric Matrix\n");

        if (idempotent)
            printf("Idempotent Matrix\n");

        if (nilpotent)
            printf("Nilpotent Matrix\n");

        // Check determinant for singular/non-singular

        double d = 0;
        int t[5][5];

        for (i = 0; i < r; i++)
            for (j = 0; j < r; j++)
                t[i][j] = a[i][j];

        // Determinant using simple expansion
        if (r == 1)
            d = a[0][0];

        else if (r == 2)
            d = a[0][0] * a[1][1] - a[0][1] * a[1][0];

        else if (r == 3) {
            d = a[0][0] * (a[1][1]*a[2][2] - a[1][2]*a[2][1])
              - a[0][1] * (a[1][0]*a[2][2] - a[1][2]*a[2][0])
              + a[0][2] * (a[1][0]*a[2][1] - a[1][1]*a[2][0]);
        }

        // For larger matrices, use row elimination
        else {
            double x[5][5];

            for (i = 0; i < r; i++)
                for (j = 0; j < r; j++)
                    x[i][j] = a[i][j];

            d = 1;

            for (i = 0; i < r; i++) {
                if (fabs(x[i][i]) < 0.000001) {
                    int found = 0;

                    for (j = i + 1; j < r; j++) {
                        if (fabs(x[j][i]) > 0.000001) {
                            for (int k = 0; k < r; k++) {
                                double swap = x[i][k];
                                x[i][k] = x[j][k];
                                x[j][k] = swap;
                            }
                            d = -d;
                            found = 1;
                            break;
                        }
                    }

                    if (!found) {
                        d = 0;
                        break;
                    }
                }

                double pivot = x[i][i];
                d *= pivot;

                for (j = i + 1; j < r; j++) {
                    double factor = x[j][i] / pivot;

                    for (int k = i; k < r; k++)
                        x[j][k] -= factor * x[i][k];
                }
            }
        }

        if (fabs(d) < 0.000001)
            printf("Singular Matrix\n");
        else
            printf("Non-Singular Matrix\n");
    }

    // Compare with another matrix

    int r2, c2, equal = 1;

    printf("\nEnter rows and columns of second matrix: ");
    scanf("%d %d", &r2, &c2);

    if (r2 > 0 && r2 <= 5 && c2 > 0 && c2 <= 5) {
        printf("Enter second matrix elements:\n");

        for (i = 0; i < r2; i++)
            for (j = 0; j < c2; j++)
                scanf("%d", &b[i][j]);

        if (r == r2 && c == c2) {
            for (i = 0; i < r; i++) {
                for (j = 0; j < c; j++) {
                    if (a[i][j] != b[i][j])
                        equal = 0;
                }
            }

            if (equal)
                printf("Equal Matrices\n");
            else
                printf("Not Equal Matrices\n");
        }
        else {
            printf("Not Equal Matrices\n");
        }
    }
    else {
        printf("Invalid second matrix size!\n");
    }

    return 0;
}
