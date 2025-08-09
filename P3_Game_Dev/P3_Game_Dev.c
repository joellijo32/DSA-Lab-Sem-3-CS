#include <stdio.h>

void inputSparseMatrix(int rows, int cols, int mat[100][100], int nonZero) {
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

void addMatrices(int rows, int cols, int A[100][100], int B[100][100], int result[100][100]) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = A[i][j] + B[i][j];
}

void transposeMatrix(int rows, int cols, int mat[100][100], int trans[100][100]) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            trans[j][i] = mat[i][j];
}

void printMatrix(int rows, int cols, int mat[100][100]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%3d ", mat[i][j]);
        printf("\n");
    }
}

int main() {
    int rows, cols;
    int buildings[100][100] = {0}, vehicles[100][100] = {0}, characters[100][100] = {0};
    int scene[100][100] = {0}, temp[100][100] = {0}, finalFrame[100][100] = {0};

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

    printf("\nScene Matrix (Before Transpose):\n");
    printMatrix(rows, cols, scene);

    transposeMatrix(rows, cols, scene, finalFrame);

    printf("\nFinal Transposed Frame sent to GPU:\n");
    printMatrix(cols, rows, finalFrame);

    return 0;
}
