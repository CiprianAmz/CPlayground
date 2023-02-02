#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum Direction {
    UP = 0,
    DOWN = 1
};

typedef struct {
    int** elements; 
    int size;
} SquareMatrix;

SquareMatrix read_input(char file_name[]) {
    SquareMatrix result = {};
    int i = 0;
    FILE* file = NULL;

    file = fopen (file_name, "r");
    assert(file != NULL);
    fscanf (file, "%d", &result.size);
    result.elements = (int**) malloc(result.size * sizeof(int*));
    for(int i = 0; i < result.size; i++) {
        result.elements[i] = (int*) malloc(result.size * sizeof(int));

        // reading elements for current collumn
        for(int j = 0; j < result.size; j++) {
            fscanf(file, "%d", &result.elements[i][j]);
        }
    }
    fclose (file);

    return result;
}

void free_matrix_memory(SquareMatrix matrix) {
    int i = 0;

    for(i = 0; i < matrix.size; i++) {
        free(matrix.elements[i]); 
    }
    free(matrix.elements);
}

void print_element(SquareMatrix matrix, int row, int column, enum Direction direction) {
    if (direction == DOWN) {
        printf("%d ", matrix.elements[row][column]);
    }
    else {
        printf("%d ", matrix.elements[column][row]);
    }
}

void print_diagonal_from_first_half(SquareMatrix matrix, int diagonal_number, enum Direction direction) {
    int diagonal_limit = 0;
    int i = 0;

    // Computing the maximum index for a certain diagonal.
    // Formula applies to first diagonal half of the matrix.
    // Example: For a matrix with n = 3:
    //   for diagonal 0 -> 3 - (3 - 0) = 0 (max index for i or j would be 0)
    //   for diagonal 2 -> 3 - (3 - 2) = 2 (max index for i or j would be 2)
    diagonal_limit = matrix.size - (matrix.size - diagonal_number);
    for (i = 0; i <= diagonal_limit; i++) {
        int row = i;
        int column = diagonal_limit - i;

        print_element(matrix, row, column, direction);
    }
}

void print_diagonal_from_second_half(SquareMatrix matrix, int diagonal_number, enum Direction direction) {
    int diagonal_limit = 0;
    int i = 0;

    // Formula applies to second diagonal half of the matrix.
    // Example: For a matrix with n = 3:
    //   for diagonal 3 -> 3 - (3 - 3) - 2 = 1 (max index for i or j would be 1)
    //   for diagonal 4 -> 3 - (4 - 3) - 2 = 0 (max index for i or j would be 0)
    diagonal_limit = matrix.size - (diagonal_number - matrix.size) - 2;
    for (i = 0; i <= diagonal_limit; i++) {
        int row = matrix.size - 1 - i;
        int column =  matrix.size - 1 - (diagonal_limit - i);

        print_element(matrix, row, column, direction);
    }
}

void parse_diagonaly(SquareMatrix matrix, int diagonal_number, enum Direction direction) {
    if (diagonal_number < matrix.size) {
        print_diagonal_from_first_half(matrix, diagonal_number, direction);
    }
    else {
        print_diagonal_from_second_half(matrix, diagonal_number, direction);
    }
}

enum Direction flip_direction(enum Direction direction) {
    if (direction == UP) {
        return DOWN;
    }
    else {
        return UP;
    }
}

int main() {
    SquareMatrix matrix = {};
    int i = 0;
    int diagonals_number = 0;
    enum Direction dir = DOWN;

    matrix = read_input("input5x5.in");
    diagonals_number = matrix.size * 2 - 1;

    for (i = 0; i < diagonals_number; i++) {
        parse_diagonaly(matrix, i, dir);
        dir = flip_direction(dir); 
    }

    free_matrix_memory(matrix);

    return 0;
}
