#include "acutest.h"
#include "matrix.h" // Your matrix library header
#include <cmath>

// Helper function to compare doubles with tolerance
bool doubleEquals(double a, double b, double epsilon = 1e-9) {
    return std::abs(a - b) < epsilon;
}

// Helper function to compare matrices
bool matricesEqual(const Matrix& m1, const Matrix& m2, double epsilon = 1e-9) {
    if (m1.rowsize != m2.rowsize || m1.columnsize != m2.columnsize) {
        return false;
    }
    
    for (int i = 0; i < m1.rowsize; i++) {
        for (int j = 0; j < m1.columnsize; j++) {
            if (!doubleEquals(m1.matrix[i][j], m2.matrix[i][j], epsilon)) {
                return false;
            }
        }
    }
    return true;
}

// ============================================================================
// Constructor Tests
// ============================================================================

void test_default_constructor(void) {
    Matrix m;
    
    TEST_CHECK(m.rowsize == 2);
    TEST_CHECK(m.columnsize == 2);
    TEST_CHECK(m.matrix.size() == 2);
    TEST_CHECK(m.matrix[0].size() == 2);
    
    // Check all elements are zero
    for (int i = 0; i < m.rowsize; i++) {
        for (int j = 0; j < m.columnsize; j++) {
            TEST_CHECK_(doubleEquals(m.matrix[i][j], 0.0), 
                       "Element [%d][%d] should be 0.0, got %f", i, j, m.matrix[i][j]);
        }
    }
}

void test_constructor_with_dimension(void) {
    Matrix m({}, std::make_tuple(3, 4));
    
    TEST_CHECK(m.rowsize == 3);
    TEST_CHECK(m.columnsize == 4);
    TEST_CHECK(m.matrix.size() == 3);
    TEST_CHECK(m.matrix[0].size() == 4);
    
    // Check all elements are zero
    for (int i = 0; i < m.rowsize; i++) {
        for (int j = 0; j < m.columnsize; j++) {
            TEST_CHECK(doubleEquals(m.matrix[i][j], 0.0));
        }
    }
}

void test_constructor_with_data(void) {
    Mat data = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    Matrix m(data, std::make_tuple(2, 3));
    
    TEST_CHECK(m.rowsize == 2);
    TEST_CHECK(m.columnsize == 3);
    TEST_CHECK(doubleEquals(m.matrix[0][0], 1.0));
    TEST_CHECK(doubleEquals(m.matrix[0][1], 2.0));
    TEST_CHECK(doubleEquals(m.matrix[0][2], 3.0));
    TEST_CHECK(doubleEquals(m.matrix[1][0], 4.0));
    TEST_CHECK(doubleEquals(m.matrix[1][1], 5.0));
    TEST_CHECK(doubleEquals(m.matrix[1][2], 6.0));
}

void test_constructor_1x1(void) {
    Matrix m({}, std::make_tuple(1, 1));
    
    TEST_CHECK(m.rowsize == 1);
    TEST_CHECK(m.columnsize == 1);
    TEST_CHECK(doubleEquals(m.matrix[0][0], 0.0));
}

void test_constructor_tall_matrix(void) {
    Matrix m({}, std::make_tuple(5, 2));
    
    TEST_CHECK(m.rowsize == 5);
    TEST_CHECK(m.columnsize == 2);
    TEST_CHECK(m.matrix.size() == 5);
    TEST_CHECK(m.matrix[0].size() == 2);
}

void test_constructor_wide_matrix(void) {
    Matrix m({}, std::make_tuple(2, 5));
    
    TEST_CHECK(m.rowsize == 2);
    TEST_CHECK(m.columnsize == 5);
    TEST_CHECK(m.matrix.size() == 2);
    TEST_CHECK(m.matrix[0].size() == 5);
}

void test_constructor_with_negative_data(void) {
    Mat data = {{-1.5, -2.5}, {-3.5, -4.5}};
    Matrix m(data, std::make_tuple(2, 2));
    
    TEST_CHECK(doubleEquals(m.matrix[0][0], -1.5));
    TEST_CHECK(doubleEquals(m.matrix[0][1], -2.5));
    TEST_CHECK(doubleEquals(m.matrix[1][0], -3.5));
    TEST_CHECK(doubleEquals(m.matrix[1][1], -4.5));
}

// ============================================================================
// getRow and getCol Tests
// ============================================================================

void test_getRow(void) {
    Mat data = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    Matrix m(data, std::make_tuple(3, 3));
    
    vec row0 = m.getRow(0);
    TEST_CHECK(row0.size() == 3);
    TEST_CHECK(doubleEquals(row0[0], 1.0));
    TEST_CHECK(doubleEquals(row0[1], 2.0));
    TEST_CHECK(doubleEquals(row0[2], 3.0));
    
    vec row2 = m.getRow(2);
    TEST_CHECK(row2.size() == 3);
    TEST_CHECK(doubleEquals(row2[0], 7.0));
    TEST_CHECK(doubleEquals(row2[1], 8.0));
    TEST_CHECK(doubleEquals(row2[2], 9.0));
}

void test_getCol(void) {
    Mat data = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    Matrix m(data, std::make_tuple(3, 3));
    
    vec col0 = m.getCol(0);
    TEST_CHECK(col0.size() == 3);
    TEST_CHECK(doubleEquals(col0[0], 1.0));
    TEST_CHECK(doubleEquals(col0[1], 4.0));
    TEST_CHECK(doubleEquals(col0[2], 7.0));
    
    vec col2 = m.getCol(2);
    TEST_CHECK(col2.size() == 3);
    TEST_CHECK(doubleEquals(col2[0], 3.0));
    TEST_CHECK(doubleEquals(col2[1], 6.0));
    TEST_CHECK(doubleEquals(col2[2], 9.0));
}

void test_getRow_single_row_matrix(void) {
    Mat data = {{1.0, 2.0, 3.0, 4.0, 5.0}};
    Matrix m(data, std::make_tuple(1, 5));
    
    vec row0 = m.getRow(0);
    TEST_CHECK(row0.size() == 5);
    TEST_CHECK(doubleEquals(row0[0], 1.0));
    TEST_CHECK(doubleEquals(row0[1], 2.0));
    TEST_CHECK(doubleEquals(row0[2], 3.0));
    TEST_CHECK(doubleEquals(row0[3], 4.0));
    TEST_CHECK(doubleEquals(row0[4], 5.0));
}

void test_getCol_single_column_matrix(void) {
    Mat data = {{1.0}, {2.0}, {3.0}, {4.0}};
    Matrix m(data, std::make_tuple(4, 1));
    
    vec col0 = m.getCol(0);
    TEST_CHECK(col0.size() == 4);
    TEST_CHECK(doubleEquals(col0[0], 1.0));
    TEST_CHECK(doubleEquals(col0[1], 2.0));
    TEST_CHECK(doubleEquals(col0[2], 3.0));
    TEST_CHECK(doubleEquals(col0[3], 4.0));
}

void test_getRow_with_negatives(void) {
    Mat data = {{-1.0, 2.0, -3.0}, {4.0, -5.0, 6.0}};
    Matrix m(data, std::make_tuple(2, 3));
    
    vec row0 = m.getRow(0);
    TEST_CHECK(doubleEquals(row0[0], -1.0));
    TEST_CHECK(doubleEquals(row0[1], 2.0));
    TEST_CHECK(doubleEquals(row0[2], -3.0));
}

void test_getCol_from_non_square(void) {
    Mat data = {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}};
    Matrix m(data, std::make_tuple(2, 4));
    
    vec col1 = m.getCol(1);
    TEST_CHECK(col1.size() == 2);
    TEST_CHECK(doubleEquals(col1[0], 2.0));
    TEST_CHECK(doubleEquals(col1[1], 6.0));
    
    vec col3 = m.getCol(3);
    TEST_CHECK(col3.size() == 2);
    TEST_CHECK(doubleEquals(col3[0], 4.0));
    TEST_CHECK(doubleEquals(col3[1], 8.0));
}

// ============================================================================
// Matrix Multiplication (dot) Tests
// ============================================================================

void test_dot_basic(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0}, {7.0, 8.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    Matrix result = Matrix::dot(m1, m2);
    
    TEST_CHECK(result.rowsize == 2);
    TEST_CHECK(result.columnsize == 2);
    
    // Expected: [[19, 22], [43, 50]]
    TEST_CHECK_(doubleEquals(result.matrix[0][0], 19.0), 
               "result[0][0] should be 19.0, got %f", result.matrix[0][0]);
    TEST_CHECK_(doubleEquals(result.matrix[0][1], 22.0),
               "result[0][1] should be 22.0, got %f", result.matrix[0][1]);
    TEST_CHECK_(doubleEquals(result.matrix[1][0], 43.0),
               "result[1][0] should be 43.0, got %f", result.matrix[1][0]);
    TEST_CHECK_(doubleEquals(result.matrix[1][1], 50.0),
               "result[1][1] should be 50.0, got %f", result.matrix[1][1]);
}

void test_dot_non_square(void) {
    Mat data1 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    Mat data2 = {{7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0}};
    
    Matrix m1(data1, std::make_tuple(2, 3));
    Matrix m2(data2, std::make_tuple(3, 2));
    
    Matrix result = Matrix::dot(m1, m2);
    
    TEST_CHECK(result.rowsize == 2);
    TEST_CHECK(result.columnsize == 2);
    
    // Expected: [[58, 64], [139, 154]]
    TEST_CHECK(doubleEquals(result.matrix[0][0], 58.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 64.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 139.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 154.0));
}

void test_dot_identity(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat identity = {{1.0, 0.0}, {0.0, 1.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix id(identity, std::make_tuple(2, 2));
    
    Matrix result = Matrix::dot(m1, id);
    
    TEST_CHECK(matricesEqual(result, m1));
}

void test_dot_1x3_times_3x1(void) {
    Mat data1 = {{1.0, 2.0, 3.0}};
    Mat data2 = {{4.0}, {5.0}, {6.0}};
    
    Matrix m1(data1, std::make_tuple(1, 3));
    Matrix m2(data2, std::make_tuple(3, 1));
    
    Matrix result = Matrix::dot(m1, m2);
    
    TEST_CHECK(result.rowsize == 1);
    TEST_CHECK(result.columnsize == 1);
    // Expected: 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    TEST_CHECK_(doubleEquals(result.matrix[0][0], 32.0),
               "1x3 times 3x1 should give 32, got %f", result.matrix[0][0]);
}

void test_dot_3x2_times_2x4(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
    Mat data2 = {{7.0, 8.0, 9.0, 10.0}, {11.0, 12.0, 13.0, 14.0}};
    
    Matrix m1(data1, std::make_tuple(3, 2));
    Matrix m2(data2, std::make_tuple(2, 4));
    
    Matrix result = Matrix::dot(m1, m2);
    
    TEST_CHECK(result.rowsize == 3);
    TEST_CHECK(result.columnsize == 4);
    
    // Expected result:
    // Row 0: [1*7+2*11, 1*8+2*12, 1*9+2*13, 1*10+2*14] = [29, 32, 35, 38]
    TEST_CHECK(doubleEquals(result.matrix[0][0], 29.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 32.0));
    TEST_CHECK(doubleEquals(result.matrix[0][2], 35.0));
    TEST_CHECK(doubleEquals(result.matrix[0][3], 38.0));
    
    // Row 1: [3*7+4*11, 3*8+4*12, 3*9+4*13, 3*10+4*14] = [65, 72, 79, 86]
    TEST_CHECK(doubleEquals(result.matrix[1][0], 65.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 72.0));
    TEST_CHECK(doubleEquals(result.matrix[1][2], 79.0));
    TEST_CHECK(doubleEquals(result.matrix[1][3], 86.0));
    
    // Row 2: [5*7+6*11, 5*8+6*12, 5*9+6*13, 5*10+6*14] = [101, 112, 123, 134]
    TEST_CHECK(doubleEquals(result.matrix[2][0], 101.0));
    TEST_CHECK(doubleEquals(result.matrix[2][1], 112.0));
    TEST_CHECK(doubleEquals(result.matrix[2][2], 123.0));
    TEST_CHECK(doubleEquals(result.matrix[2][3], 134.0));
}

void test_dot_4x1_times_1x4(void) {
    Mat data1 = {{2.0}, {3.0}, {4.0}, {5.0}};
    Mat data2 = {{1.0, 2.0, 3.0, 4.0}};
    
    Matrix m1(data1, std::make_tuple(4, 1));
    Matrix m2(data2, std::make_tuple(1, 4));
    
    Matrix result = Matrix::dot(m1, m2);
    
    TEST_CHECK(result.rowsize == 4);
    TEST_CHECK(result.columnsize == 4);
    
    // This creates an outer product
    // Expected: [[2, 4, 6, 8], [3, 6, 9, 12], [4, 8, 12, 16], [5, 10, 15, 20]]
    TEST_CHECK(doubleEquals(result.matrix[0][0], 2.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 4.0));
    TEST_CHECK(doubleEquals(result.matrix[0][2], 6.0));
    TEST_CHECK(doubleEquals(result.matrix[0][3], 8.0));
    
    TEST_CHECK(doubleEquals(result.matrix[1][0], 3.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 6.0));
    TEST_CHECK(doubleEquals(result.matrix[1][2], 9.0));
    TEST_CHECK(doubleEquals(result.matrix[1][3], 12.0));
    
    TEST_CHECK(doubleEquals(result.matrix[2][0], 4.0));
    TEST_CHECK(doubleEquals(result.matrix[2][1], 8.0));
    TEST_CHECK(doubleEquals(result.matrix[2][2], 12.0));
    TEST_CHECK(doubleEquals(result.matrix[2][3], 16.0));
    
    TEST_CHECK(doubleEquals(result.matrix[3][0], 5.0));
    TEST_CHECK(doubleEquals(result.matrix[3][1], 10.0));
    TEST_CHECK(doubleEquals(result.matrix[3][2], 15.0));
    TEST_CHECK(doubleEquals(result.matrix[3][3], 20.0));
}

void test_dot_3x3_times_3x3(void) {
    Mat data1 = {{1.0, 0.0, 2.0}, {0.0, 3.0, 0.0}, {4.0, 0.0, 5.0}};
    Mat data2 = {{6.0, 7.0, 0.0}, {0.0, 8.0, 9.0}, {10.0, 0.0, 11.0}};
    
    Matrix m1(data1, std::make_tuple(3, 3));
    Matrix m2(data2, std::make_tuple(3, 3));
    
    Matrix result = Matrix::dot(m1, m2);
    
    TEST_CHECK(result.rowsize == 3);
    TEST_CHECK(result.columnsize == 3);
    
    // Expected result:
    // Row 0: [1*6+0*0+2*10, 1*7+0*8+2*0, 1*0+0*9+2*11] = [26, 7, 22]
    TEST_CHECK(doubleEquals(result.matrix[0][0], 26.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 7.0));
    TEST_CHECK(doubleEquals(result.matrix[0][2], 22.0));
    
    // Row 1: [0*6+3*0+0*10, 0*7+3*8+0*0, 0*0+3*9+0*11] = [0, 24, 27]
    TEST_CHECK(doubleEquals(result.matrix[1][0], 0.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 24.0));
    TEST_CHECK(doubleEquals(result.matrix[1][2], 27.0));
    
    // Row 2: [4*6+0*0+5*10, 4*7+0*8+5*0, 4*0+0*9+5*11] = [74, 28, 55]
    TEST_CHECK(doubleEquals(result.matrix[2][0], 74.0));
    TEST_CHECK(doubleEquals(result.matrix[2][1], 28.0));
    TEST_CHECK(doubleEquals(result.matrix[2][2], 55.0));
}

void test_dot_with_zeros(void) {
    Mat data1 = {{1.0, 2.0, 3.0}, {0.0, 0.0, 0.0}};
    Mat data2 = {{0.0, 1.0}, {0.0, 2.0}, {0.0, 3.0}};
    
    Matrix m1(data1, std::make_tuple(2, 3));
    Matrix m2(data2, std::make_tuple(3, 2));
    
    Matrix result = Matrix::dot(m1, m2);
    
    TEST_CHECK(result.rowsize == 2);
    TEST_CHECK(result.columnsize == 2);
    
    // Row 0: [1*0+2*0+3*0, 1*1+2*2+3*3] = [0, 14]
    TEST_CHECK(doubleEquals(result.matrix[0][0], 0.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 14.0));
    
    // Row 1: all zeros
    TEST_CHECK(doubleEquals(result.matrix[1][0], 0.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 0.0));
}

void test_dot_with_negatives(void) {
    Mat data1 = {{-1.0, 2.0}, {3.0, -4.0}};
    Mat data2 = {{5.0, -6.0}, {-7.0, 8.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    Matrix result = Matrix::dot(m1, m2);
    
    // Expected: [[-1*5+2*(-7), -1*(-6)+2*8], [3*5+(-4)*(-7), 3*(-6)+(-4)*8]]
    //         = [[-5-14, 6+16], [15+28, -18-32]]
    //         = [[-19, 22], [43, -50]]
    TEST_CHECK(doubleEquals(result.matrix[0][0], -19.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 22.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 43.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], -50.0));
}

void test_dot_incompatible_dimensions(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0}, {7.0, 8.0}, {9.0, 10.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(3, 2));
    
    bool caught = false;
    try {
        Matrix result = Matrix::dot(m1, m2);
    } catch (const std::invalid_argument& e) {
        caught = true;
    }
    
    TEST_CHECK_(caught, "Should throw exception for incompatible dimensions");
}

// ============================================================================
// Scalar Multiplication Tests
// ============================================================================

void test_const_multiplication_basic(void) {
    Mat data = {{1.0, 2.0}, {3.0, 4.0}};
    Matrix m(data, std::make_tuple(2, 2));
    
    Matrix result = Matrix::Constmultiplication(m, 3);
    
    TEST_CHECK(result.rowsize == 2);
    TEST_CHECK(result.columnsize == 2);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 3.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 6.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 9.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 12.0));
}

void test_const_multiplication_zero(void) {
    Mat data = {{5.0, -3.0}, {2.0, 7.0}};
    Matrix m(data, std::make_tuple(2, 2));
    
    Matrix result = Matrix::Constmultiplication(m, 0);
    
    for (int i = 0; i < result.rowsize; i++) {
        for (int j = 0; j < result.columnsize; j++) {
            TEST_CHECK(doubleEquals(result.matrix[i][j], 0.0));
        }
    }
}

void test_const_multiplication_negative(void) {
    Mat data = {{1.0, 2.0}, {3.0, 4.0}};
    Matrix m(data, std::make_tuple(2, 2));
    
    Matrix result = Matrix::Constmultiplication(m, -2);
    
    TEST_CHECK(doubleEquals(result.matrix[0][0], -2.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], -4.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], -6.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], -8.0));
}

void test_const_multiplication_non_square(void) {
    Mat data = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    Matrix m(data, std::make_tuple(2, 3));
    
    Matrix result = Matrix::Constmultiplication(m, 2);
    
    TEST_CHECK(result.rowsize == 2);
    TEST_CHECK(result.columnsize == 3);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 2.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 4.0));
    TEST_CHECK(doubleEquals(result.matrix[0][2], 6.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 8.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 10.0));
    TEST_CHECK(doubleEquals(result.matrix[1][2], 12.0));
}

void test_const_multiplication_fractional(void) {
    Mat data = {{10.0, 20.0}, {30.0, 40.0}};
    Matrix m(data, std::make_tuple(2, 2));
    
    // Note: function takes int, so this tests integer multiplication
    Matrix result = Matrix::Constmultiplication(m, 3);
    
    TEST_CHECK(doubleEquals(result.matrix[0][0], 30.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 60.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 90.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 120.0));
}

void test_const_multiplication_large_scalar(void) {
    Mat data = {{1.0, 2.0}, {3.0, 4.0}};
    Matrix m(data, std::make_tuple(2, 2));
    
    Matrix result = Matrix::Constmultiplication(m, 100);
    
    TEST_CHECK(doubleEquals(result.matrix[0][0], 100.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 200.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 300.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 400.0));
}

void test_const_multiplication_one(void) {
    Mat data = {{5.5, -3.2}, {2.1, 7.8}};
    Matrix m(data, std::make_tuple(2, 2));
    
    Matrix result = Matrix::Constmultiplication(m, 1);
    
    TEST_CHECK(matricesEqual(result, m));
}

// ============================================================================
// Matrix Addition Tests
// ============================================================================

void test_add_basic(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0}, {7.0, 8.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    Matrix result = Matrix::AddMatrix(m1, m2);
    
    TEST_CHECK(result.rowsize == 2);
    TEST_CHECK(result.columnsize == 2);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 6.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 8.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 10.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 12.0));
}

void test_add_with_negatives(void) {
    Mat data1 = {{1.0, -2.0}, {3.0, -4.0}};
    Mat data2 = {{-5.0, 6.0}, {7.0, 8.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    Matrix result = Matrix::AddMatrix(m1, m2);
    
    TEST_CHECK(doubleEquals(result.matrix[0][0], -4.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 4.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 10.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 4.0));
}

void test_add_non_square(void) {
    Mat data1 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    Mat data2 = {{7.0, 8.0, 9.0}, {10.0, 11.0, 12.0}};
    
    Matrix m1(data1, std::make_tuple(2, 3));
    Matrix m2(data2, std::make_tuple(2, 3));
    
    Matrix result = Matrix::AddMatrix(m1, m2);
    
    TEST_CHECK(result.rowsize == 2);
    TEST_CHECK(result.columnsize == 3);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 8.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 10.0));
    TEST_CHECK(doubleEquals(result.matrix[0][2], 12.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 14.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 16.0));
    TEST_CHECK(doubleEquals(result.matrix[1][2], 18.0));
}

void test_add_incompatible_dimensions(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0, 7.0}, {8.0, 9.0, 10.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 3));
    
    bool caught = false;
    try {
        Matrix result = Matrix::AddMatrix(m1, m2);
    } catch (const std::invalid_argument& e) {
        caught = true;
        TEST_MSG("Exception message: %s", e.what());
    }
    
    TEST_CHECK_(caught, "Should throw exception for incompatible dimensions in AddMatrix");
}

void test_add_single_row(void) {
    Mat data1 = {{1.0, 2.0, 3.0, 4.0}};
    Mat data2 = {{5.0, 6.0, 7.0, 8.0}};
    
    Matrix m1(data1, std::make_tuple(1, 4));
    Matrix m2(data2, std::make_tuple(1, 4));
    
    Matrix result = Matrix::AddMatrix(m1, m2);
    
    TEST_CHECK(result.rowsize == 1);
    TEST_CHECK(result.columnsize == 4);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 6.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 8.0));
    TEST_CHECK(doubleEquals(result.matrix[0][2], 10.0));
    TEST_CHECK(doubleEquals(result.matrix[0][3], 12.0));
}

void test_add_single_column(void) {
    Mat data1 = {{1.0}, {2.0}, {3.0}};
    Mat data2 = {{4.0}, {5.0}, {6.0}};
    
    Matrix m1(data1, std::make_tuple(3, 1));
    Matrix m2(data2, std::make_tuple(3, 1));
    
    Matrix result = Matrix::AddMatrix(m1, m2);
    
    TEST_CHECK(result.rowsize == 3);
    TEST_CHECK(result.columnsize == 1);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 5.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 7.0));
    TEST_CHECK(doubleEquals(result.matrix[2][0], 9.0));
}

void test_add_large_matrices(void) {
    Mat data1 = {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}, {9.0, 10.0, 11.0, 12.0}};
    Mat data2 = {{12.0, 11.0, 10.0, 9.0}, {8.0, 7.0, 6.0, 5.0}, {4.0, 3.0, 2.0, 1.0}};
    
    Matrix m1(data1, std::make_tuple(3, 4));
    Matrix m2(data2, std::make_tuple(3, 4));
    
    Matrix result = Matrix::AddMatrix(m1, m2);
    
    TEST_CHECK(result.rowsize == 3);
    TEST_CHECK(result.columnsize == 4);
    
    // All elements should be 13
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            TEST_CHECK_(doubleEquals(result.matrix[i][j], 13.0),
                       "Element [%d][%d] should be 13.0, got %f", i, j, result.matrix[i][j]);
        }
    }
}

void test_add_zero_matrix(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{0.0, 0.0}, {0.0, 0.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    Matrix result = Matrix::AddMatrix(m1, m2);
    
    TEST_CHECK(matricesEqual(result, m1));
}

// ============================================================================
// Matrix Subtraction Tests
// ============================================================================

void test_subtract_basic(void) {
    Mat data1 = {{5.0, 6.0}, {7.0, 8.0}};
    Mat data2 = {{1.0, 2.0}, {3.0, 4.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    Matrix result = Matrix::SubtractMatix(m1, m2);
    
    TEST_CHECK(result.rowsize == 2);
    TEST_CHECK(result.columnsize == 2);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 4.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 4.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 4.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 4.0));
}

void test_subtract_with_negatives(void) {
    Mat data1 = {{1.0, -2.0}, {3.0, -4.0}};
    Mat data2 = {{-5.0, 6.0}, {7.0, 8.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    Matrix result = Matrix::SubtractMatix(m1, m2);
    
    TEST_CHECK(doubleEquals(result.matrix[0][0], 6.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], -8.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], -4.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], -12.0));
}

void test_subtract_same_matrix(void) {
    Mat data = {{5.0, 6.0}, {7.0, 8.0}};
    Matrix m(data, std::make_tuple(2, 2));
    
    Matrix result = Matrix::SubtractMatix(m, m);
    
    for (int i = 0; i < result.rowsize; i++) {
        for (int j = 0; j < result.columnsize; j++) {
            TEST_CHECK_(doubleEquals(result.matrix[i][j], 0.0),
                       "Subtracting matrix from itself should yield zero at [%d][%d]", i, j);
        }
    }
}

void test_subtract_non_square(void) {
    Mat data1 = {{10.0, 11.0, 12.0}, {13.0, 14.0, 15.0}};
    Mat data2 = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    
    Matrix m1(data1, std::make_tuple(2, 3));
    Matrix m2(data2, std::make_tuple(2, 3));
    
    Matrix result = Matrix::SubtractMatix(m1, m2);
    
    TEST_CHECK(result.rowsize == 2);
    TEST_CHECK(result.columnsize == 3);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 9.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 9.0));
    TEST_CHECK(doubleEquals(result.matrix[0][2], 9.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 9.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 9.0));
    TEST_CHECK(doubleEquals(result.matrix[1][2], 9.0));
}

void test_subtract_incompatible_dimensions(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0, 7.0}, {8.0, 9.0, 10.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 3));
    
    bool caught = false;
    try {
        Matrix result = Matrix::SubtractMatix(m1, m2);
    } catch (const std::invalid_argument& e) {
        caught = true;
        TEST_MSG("Exception message: %s", e.what());
    }
    
    TEST_CHECK_(caught, "Should throw exception for incompatible dimensions in SubtractMatix");
}

void test_subtract_single_row(void) {
    Mat data1 = {{10.0, 20.0, 30.0}};
    Mat data2 = {{1.0, 2.0, 3.0}};
    
    Matrix m1(data1, std::make_tuple(1, 3));
    Matrix m2(data2, std::make_tuple(1, 3));
    
    Matrix result = Matrix::SubtractMatix(m1, m2);
    
    TEST_CHECK(result.rowsize == 1);
    TEST_CHECK(result.columnsize == 3);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 9.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 18.0));
    TEST_CHECK(doubleEquals(result.matrix[0][2], 27.0));
}

void test_subtract_single_column(void) {
    Mat data1 = {{10.0}, {20.0}, {30.0}, {40.0}};
    Mat data2 = {{5.0}, {10.0}, {15.0}, {20.0}};
    
    Matrix m1(data1, std::make_tuple(4, 1));
    Matrix m2(data2, std::make_tuple(4, 1));
    
    Matrix result = Matrix::SubtractMatix(m1, m2);
    
    TEST_CHECK(result.rowsize == 4);
    TEST_CHECK(result.columnsize == 1);
    TEST_CHECK(doubleEquals(result.matrix[0][0], 5.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 10.0));
    TEST_CHECK(doubleEquals(result.matrix[2][0], 15.0));
    TEST_CHECK(doubleEquals(result.matrix[3][0], 20.0));
}

void test_subtract_resulting_in_negatives(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0}, {7.0, 8.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    Matrix result = Matrix::SubtractMatix(m1, m2);
    
    TEST_CHECK(doubleEquals(result.matrix[0][0], -4.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], -4.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], -4.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], -4.0));
}

void test_subtract_zero_matrix(void) {
    Mat data1 = {{5.5, -3.2, 7.1}, {2.4, 8.9, -1.6}};
    Mat data2 = {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
    
    Matrix m1(data1, std::make_tuple(2, 3));
    Matrix m2(data2, std::make_tuple(2, 3));
    
    Matrix result = Matrix::SubtractMatix(m1, m2);
    
    TEST_CHECK(matricesEqual(result, m1));
}

// ============================================================================
// Edge Case Tests
// ============================================================================

void test_single_element_matrix(void) {
    Mat data = {{42.0}};
    Matrix m(data, std::make_tuple(1, 1));
    
    TEST_CHECK(m.rowsize == 1);
    TEST_CHECK(m.columnsize == 1);
    TEST_CHECK(doubleEquals(m.matrix[0][0], 42.0));
    
    Matrix doubled = Matrix::Constmultiplication(m, 2);
    TEST_CHECK(doubleEquals(doubled.matrix[0][0], 84.0));
}

void test_large_matrix_dimensions(void) {
    Matrix m({}, std::make_tuple(100, 100));
    
    TEST_CHECK(m.rowsize == 100);
    TEST_CHECK(m.columnsize == 100);
    TEST_CHECK(m.matrix.size() == 100);
    TEST_CHECK(m.matrix[0].size() == 100);
}

void test_floating_point_precision(void) {
    Mat data = {{0.1, 0.2}, {0.3, 0.4}};
    Matrix m(data, std::make_tuple(2, 2));
    
    Matrix result = Matrix::Constmultiplication(m, 10);
    
    TEST_CHECK(doubleEquals(result.matrix[0][0], 1.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 2.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 3.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 4.0));
}

void test_commutative_addition(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0}, {7.0, 8.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    Matrix result1 = Matrix::AddMatrix(m1, m2);
    Matrix result2 = Matrix::AddMatrix(m2, m1);
    
    TEST_CHECK_(matricesEqual(result1, result2), 
               "Matrix addition should be commutative");
}

void test_associative_addition(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0}, {7.0, 8.0}};
    Mat data3 = {{9.0, 10.0}, {11.0, 12.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    Matrix m3(data3, std::make_tuple(2, 2));
    
    Matrix result1 = Matrix::AddMatrix(Matrix::AddMatrix(m1, m2), m3);
    Matrix result2 = Matrix::AddMatrix(m1, Matrix::AddMatrix(m2, m3));
    
    TEST_CHECK_(matricesEqual(result1, result2),
               "Matrix addition should be associative");
}

void test_distributive_scalar_multiplication(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0}, {7.0, 8.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    
    // k(A + B) = kA + kB
    Matrix sum = Matrix::AddMatrix(m1, m2);
    Matrix result1 = Matrix::Constmultiplication(sum, 3);
    
    Matrix scaled1 = Matrix::Constmultiplication(m1, 3);
    Matrix scaled2 = Matrix::Constmultiplication(m2, 3);
    Matrix result2 = Matrix::AddMatrix(scaled1, scaled2);
    
    TEST_CHECK_(matricesEqual(result1, result2),
               "Scalar multiplication should be distributive over addition");
}

void test_dot_associativity(void) {
    Mat data1 = {{1.0, 2.0}, {3.0, 4.0}};
    Mat data2 = {{5.0, 6.0}, {7.0, 8.0}};
    Mat data3 = {{9.0, 10.0}, {11.0, 12.0}};
    
    Matrix m1(data1, std::make_tuple(2, 2));
    Matrix m2(data2, std::make_tuple(2, 2));
    Matrix m3(data3, std::make_tuple(2, 2));
    
    // (AB)C = A(BC)
    Matrix result1 = Matrix::dot(Matrix::dot(m1, m2), m3);
    Matrix result2 = Matrix::dot(m1, Matrix::dot(m2, m3));
    
    TEST_CHECK_(matricesEqual(result1, result2),
               "Matrix multiplication should be associative");
}

void test_very_small_values(void) {
    Mat data = {{0.0001, 0.0002}, {0.0003, 0.0004}};
    Matrix m(data, std::make_tuple(2, 2));
    
    Matrix result = Matrix::Constmultiplication(m, 10000);
    
    TEST_CHECK(doubleEquals(result.matrix[0][0], 1.0));
    TEST_CHECK(doubleEquals(result.matrix[0][1], 2.0));
    TEST_CHECK(doubleEquals(result.matrix[1][0], 3.0));
    TEST_CHECK(doubleEquals(result.matrix[1][1], 4.0));
}

// ============================================================================
// Test List
// ============================================================================

TEST_LIST = {
    // Constructor tests
    { "default-constructor", test_default_constructor },
    { "constructor-with-dimension", test_constructor_with_dimension },
    { "constructor-with-data", test_constructor_with_data },
    { "constructor-1x1", test_constructor_1x1 },
    { "constructor-tall-matrix", test_constructor_tall_matrix },
    { "constructor-wide-matrix", test_constructor_wide_matrix },
    { "constructor-with-negative-data", test_constructor_with_negative_data },
    
    // getRow and getCol tests
    { "getRow", test_getRow },
    { "getCol", test_getCol },
    { "getRow-single-row-matrix", test_getRow_single_row_matrix },
    { "getCol-single-column-matrix", test_getCol_single_column_matrix },
    { "getRow-with-negatives", test_getRow_with_negatives },
    { "getCol-from-non-square", test_getCol_from_non_square },
    
    // Matrix multiplication tests
    { "dot-basic", test_dot_basic },
    { "dot-non-square", test_dot_non_square },
    { "dot-identity", test_dot_identity },
    { "dot-1x3-times-3x1", test_dot_1x3_times_3x1 },
    { "dot-3x2-times-2x4", test_dot_3x2_times_2x4 },
    { "dot-4x1-times-1x4", test_dot_4x1_times_1x4 },
    { "dot-3x3-times-3x3", test_dot_3x3_times_3x3 },
    { "dot-with-zeros", test_dot_with_zeros },
    { "dot-with-negatives", test_dot_with_negatives },
    { "dot-incompatible-dimensions", test_dot_incompatible_dimensions },
    
    // Scalar multiplication tests
    { "const-multiplication-basic", test_const_multiplication_basic },
    { "const-multiplication-zero", test_const_multiplication_zero },
    { "const-multiplication-negative", test_const_multiplication_negative },
    { "const-multiplication-non-square", test_const_multiplication_non_square },
    { "const-multiplication-fractional", test_const_multiplication_fractional },
    { "const-multiplication-large-scalar", test_const_multiplication_large_scalar },
    { "const-multiplication-one", test_const_multiplication_one },
    
    // Matrix addition tests
    { "add-basic", test_add_basic },
    { "add-with-negatives", test_add_with_negatives },
    { "add-non-square", test_add_non_square },
    { "add-incompatible-dimensions", test_add_incompatible_dimensions },
    { "add-single-row", test_add_single_row },
    { "add-single-column", test_add_single_column },
    { "add-large-matrices", test_add_large_matrices },
    { "add-zero-matrix", test_add_zero_matrix },
    
    // Matrix subtraction tests
    { "subtract-basic", test_subtract_basic },
    { "subtract-with-negatives", test_subtract_with_negatives },
    { "subtract-same-matrix", test_subtract_same_matrix },
    { "subtract-non-square", test_subtract_non_square },
    { "subtract-incompatible-dimensions", test_subtract_incompatible_dimensions },
    { "subtract-single-row", test_subtract_single_row },
    { "subtract-single-column", test_subtract_single_column },
    { "subtract-resulting-in-negatives", test_subtract_resulting_in_negatives },
    { "subtract-zero-matrix", test_subtract_zero_matrix },
    
    // Edge case tests
    { "single-element-matrix", test_single_element_matrix },
    { "large-matrix-dimensions", test_large_matrix_dimensions },
    { "floating-point-precision", test_floating_point_precision },
    { "commutative-addition", test_commutative_addition },
    { "associative-addition", test_associative_addition },
    { "distributive-scalar-multiplication", test_distributive_scalar_multiplication },
    { "dot-associativity", test_dot_associativity },
    { "very-small-values", test_very_small_values },
    
    { NULL, NULL }
};
