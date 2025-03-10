#ifndef MATRIX_H
#define MATRIX_H

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

//Definiáljunk egy init_identity_matrix függvényt, amelyik az egységmátrixot inicializálja!
void init_identity_matrix(float matrix[3][3]);

//Definiáljunk függvényt a mátrix skalárral való szorzásához!
void scale_matrix(float matrix[3][3], float scalar);

//A multiply_matrices függvényben implementáljunk a mátrix szorzást
void multiply_matrices(const float a[3][3], const float b[3][3], float result[3][3]);

//Definiáljuk a transform_point függvényt, 
void transform_point(const float matrix[3][3], float point[3]);

//Írjunk 3 függvényt a transzformációkhoz, amelyik módosítja az első paraméterében kapott transzformációs mátrixot! A függvények neve legyen scale, shift, rotate! A skálázás és a forgatás origó középpontú legyen!
void scale(float matrix[3][3], float sx, float sy);
void shift(float matrix[3][3], float dx, float dy);
void rotate(float matrix[3][3], float angle);

#endif 
