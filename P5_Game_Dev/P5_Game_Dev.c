#include <stdio.h>

#define MAX 100

void inputSparseMatrix(int rows, int cols, int mat[MAX][MAX], int nonZero) {
    int r, c, val;
    for (int i = 0; i < nonZero; i++) {
        printf("Enter row, col, value for object %d: ", i + 1);
        scanf("%d %d %d", &r, &c, &val);
        if (r < rows && c < cols)
            mat[r][c] = val;
        else
            printf("Invalid position. Skipped.\n");
    }
}

void addMatrices(int rows, int cols, int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX]) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = A[i][j] + B[i][j];
}

void transposeMatrix(int rows, int cols, int mat[MAX][MAX], int trans[MAX][MAX]) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            trans[j][i] = mat[i][j];
}

void printMatrix(int rows, int cols, int mat[MAX][MAX]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%3d ", mat[i][j]);
        printf("\n");
    }
}

int main() {
    int rows, cols;
    int buildings[MAX][MAX] = {0}, vehicles[MAX][MAX] = {0}, characters[MAX][MAX] = {0};
    int scene[MAX][MAX] = {0}, temp[MAX][MAX] = {0}, finalFrame[MAX][MAX] = {0};

    printf("Enter scene size (rows cols): ");
    scanf("%d %d", &rows, &cols);

    int nz_buildings, nz_vehicles, nz_characters;
    printf("Enter number of objects in Layer 1 (Buildings): ");
    scanf("%d", &nz_buildings);
    inputSparseMatrix(rows, cols, buildings, nz_buildings);

    printf("Enter number of objects in Layer 2 (Vehicles): ");
    scanf("%d", &nz_vehicles);
    inputSparseMatrix(rows, cols, vehicles, nz_vehicles);

    printf("Enter number of objects in Layer 3 (Characters): ");
    scanf("%d", &nz_characters);
    inputSparseMatrix(rows, cols, characters, nz_characters);

    addMatrices(rows, cols, buildings, vehicles, temp);
    addMatrices(rows, cols, temp, characters, scene);

    transposeMatrix(rows, cols, scene, finalFrame);

    printf("\nFinal Transposed Frame sent to GPU:\n");
    printMatrix(cols, rows, finalFrame);

    return 0;
}
