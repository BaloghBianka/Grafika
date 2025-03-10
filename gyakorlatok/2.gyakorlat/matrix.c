#include "matrix.h"
#include <stdio.h>
#include <math.h>

void init_zero_matrix(float matrix[3][3])
{
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            matrix[i][j] = 0.0f;
}

void init_identity_matrix(float matrix[3][3])
{
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            matrix[i][j] = (i == j) ? 1.0f : 0.0f;
}

void print_matrix(const float matrix[3][3])
{
    int i, j;
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            c[i][j] = a[i][j] + b[i][j];
}

void scale_matrix(float matrix[3][3], float scalar)
{
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            matrix[i][j] *= scalar;
}

void multiply_matrices(const float a[3][3], const float b[3][3], float result[3][3])
{
    int i, j, k;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j) {
            result[i][j] = 0.0f;
            for (k = 0; k < 3; ++k)
                result[i][j] += a[i][k] * b[k][j];
        }
}

void transform_point(const float matrix[3][3], float point[3])
{
    float result[3] = {0.0f, 0.0f, 1.0f};
    int i, j;
    for (i = 0; i < 3; ++i)
        for (j = 0; j < 3; ++j)
            result[i] += matrix[i][j] * point[j];

    for (i = 0; i < 3; ++i)
        point[i] = result[i];
}

void scale(float matrix[3][3], float sx, float sy)
{
    float scale_matrix[3][3] = {
        {sx,  0.0f, 0.0f},
        {0.0f, sy,  0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    multiply_matrices(scale_matrix, matrix, matrix);
}

void shift(float matrix[3][3], float dx, float dy)
{
    float shift_matrix[3][3] = {
        {1.0f, 0.0f, dx},
        {0.0f, 1.0f, dy},
        {0.0f, 0.0f, 1.0f}
    };
    multiply_matrices(shift_matrix, matrix, matrix);
}

void rotate(float matrix[3][3], float angle)
{
    float cos_a = cos(angle);
    float sin_a = sin(angle);

    float rotate_matrix[3][3] = {
        {cos_a, -sin_a, 0.0f},
        {sin_a, cos_a,  0.0f},
        {0.0f,  0.0f,   1.0f}
    };
    multiply_matrices(rotate_matrix, matrix, matrix);
}
