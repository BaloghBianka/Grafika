#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

typedef struct {
    float stack[STACK_SIZE][3][3];
    int top;
} MatrixStack;

void init_stack(MatrixStack* stack) {
    stack->top = -1;
}

int push_matrix(MatrixStack* stack, const float matrix[3][3]) {
    if (stack->top >= STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        return 0;
    }
    stack->top++;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            stack->stack[stack->top][i][j] = matrix[i][j];
        }
    }
    return 1;
}

int pop_matrix(MatrixStack* stack, float matrix[3][3]) {
    if (stack->top < 0) {
        printf("Stack underflow!\n");
        return 0;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix[i][j] = stack->stack[stack->top][i][j];
        }
    }
    stack->top--;
    return 1;
}

int main(int argc, char* argv[])
{
    float a[3][3] = {
        { 1.0f, -2.0f,  3.0f},
        { 5.0f, -3.0f,  0.0f},
        {-2.0f,  1.0f, -4.0f}
    };
    float b[3][3];
    float c[3][3];

    MatrixStack stack;
    init_stack(&stack);

    printf("Pushing initial matrix onto stack:\n");
    push_matrix(&stack, a);
    print_matrix(a);

    printf("Initializing zero matrix:\n");
    init_zero_matrix(b);
    b[1][1] =  8.0f;
    b[2][0] = -3.0f;
    b[2][2] =  5.0f;

    printf("Matrix A:\n");
    print_matrix(a);
    printf("Matrix B:\n");
    print_matrix(b);
    
    printf("Adding matrices A + B:\n");
    add_matrices(a, b, c);
    print_matrix(c);

    printf("Initializing identity matrix:\n");
    init_identity_matrix(b);
    print_matrix(b);

    printf("Scaling matrix A by 2.0:\n");
    scale_matrix(a, 2.0f);
    print_matrix(a);

    printf("Multiplying matrices A * B:\n");
    multiply_matrices(a, b, c);
    print_matrix(c);

    float point[3] = {1.0f, 2.0f, 1.0f};
    printf("Transforming point (1,2) using matrix B:\n");
    transform_point(b, point);
    printf("Transformed point: (%f, %f)\n", point[0], point[1]);

    printf("Applying scale transformation (2.0, 3.0):\n");
    init_identity_matrix(b);
    scale(b, 2.0f, 3.0f);
    print_matrix(b);

    printf("Applying shift transformation (+1, -1):\n");
    shift(b, 1.0f, -1.0f);
    print_matrix(b);

    printf("Applying rotation transformation (45 degrees):\n");
    rotate(b, 45.0f * (3.14159f / 180.0f));
    print_matrix(b);

    printf("Undo last transformation (rotation):\n");
    pop_matrix(&stack, a);
    print_matrix(a);

    printf("Undo another transformation (shift):\n");
    pop_matrix(&stack, a);
    print_matrix(a);

    printf("Undo to original matrix:\n");
    pop_matrix(&stack, a);
    print_matrix(a);

    return 0;
}