#include "../s21_matrix_oop.h"

#include <gtest/gtest.h>

void fill_matrix(const S21Matrix &fill) {
  int num = 0;
  for (int i = 0; i < fill.Get_rows(); i++) {
    for (int z = 0; z < fill.Get_cols(); z++) {
      fill[i][z] = num;
      num++;
    }
  }
}

void fill_matrix_back(const S21Matrix &fill) {
  int num = 0;
  for (int i = fill.Get_rows() - 1; i > -1; i--) {
    for (int z = fill.Get_cols() - 1; z > -1; z--) {
      fill[i][z] = num;
      num++;
    }
  }
}

TEST(construktor_def, construktor_def_true) {
  S21Matrix def_matrix;
  EXPECT_EQ(def_matrix.Get_rows(), 0);
  EXPECT_EQ(def_matrix.Get_cols(), 0);
}

TEST(constructor, constructor_false) {
  EXPECT_THROW(S21Matrix first(1, 0);, std::out_of_range);
}

TEST(EqMatrixt, EqMatrix_true) {
  S21Matrix first(5, 5);
  S21Matrix second(5, 5);
  fill_matrix(first);
  fill_matrix(second);
  ASSERT_TRUE(first == second);
}

TEST(EqMatrixt, EqMatrix_false) {
  S21Matrix first(100, 100);
  S21Matrix second(100, 100);
  fill_matrix(first);
  fill_matrix(second);
  second(50, 50) = 123.321;
  ASSERT_FALSE(first == second);
}

TEST(EqMatrixt, EqMatrix_false_2) {
  S21Matrix first(100, 100);
  S21Matrix second(100, 99);
  ASSERT_FALSE(first.EqMatrix(second));
}

TEST(SumMatrix, SumMatrix_true) {
  S21Matrix first(4, 3);
  S21Matrix second(4, 3);
  S21Matrix res(4, 3);
  fill_matrix(first);
  fill_matrix(second);
  first += second;
  res(0, 1) = 2;
  res(0, 2) = 4;
  res(1, 0) = 6;
  res(1, 1) = 8;
  res(1, 2) = 10;
  res(2, 0) = 12;
  res(2, 1) = 14;
  res(2, 2) = 16;
  res(3, 0) = 18;
  res(3, 1) = 20;
  res(3, 2) = 22;
  ASSERT_TRUE(first.EqMatrix(res));
}

TEST(SumMatrix, SumMatrix_true_2) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);
  fill_matrix(first);
  fill_matrix(second);
  S21Matrix sum = first + second;
  S21Matrix res(2, 2);
  res[0][1] = 2;
  res[1][0] = 4;
  res[1][1] = 6;
  ASSERT_TRUE(sum.EqMatrix(res));
}

TEST(SumMatrix, SumMatrix_false) {
  S21Matrix first(4, 3);
  S21Matrix second(4, 4);
  fill_matrix(first);
  fill_matrix(second);
  EXPECT_THROW(first.SumMatrix(second), std::out_of_range);
}

TEST(SubMatrix, SubMatrix_true) {
  S21Matrix first(5, 6);
  S21Matrix second(5, 6);
  S21Matrix res(5, 6);
  fill_matrix(first);
  fill_matrix_back(second);
  res(0, 0) = -29;
  res(0, 1) = -27;
  res(0, 2) = -25;
  res(0, 3) = -23;
  res(0, 4) = -21;
  res(0, 5) = -19;
  res(1, 0) = -17;
  res(1, 1) = -15;
  res(1, 2) = -13;
  res(1, 3) = -11;
  res(1, 4) = -9;
  res(1, 5) = -7;
  res(2, 0) = -5;
  res(2, 1) = -3;
  res(2, 2) = -1;
  res(2, 3) = 1;
  res(2, 4) = 3;
  res(2, 5) = 5;
  res(3, 0) = 7;
  res(3, 1) = 9;
  res(3, 2) = 11;
  res(3, 3) = 13;
  res(3, 4) = 15;
  res(3, 5) = 17;
  res(4, 0) = 19;
  res(4, 1) = 21;
  res(4, 2) = 23;
  res(4, 3) = 25;
  res(4, 4) = 27;
  res(4, 5) = 29;
  first -= second;
  ASSERT_TRUE(first.EqMatrix(res));
}

TEST(SubMatrix, SubMatrix_true_2) {
  S21Matrix first(5, 6);
  S21Matrix second(5, 6);
  S21Matrix res(5, 6);
  fill_matrix(first);
  fill_matrix(second);
  S21Matrix sub = first - second;
  ASSERT_TRUE(sub.EqMatrix(res));
}

TEST(SubMatrix, SubMatrix_err) {
  S21Matrix first(43, 23);
  S21Matrix second(43, 24);
  fill_matrix(first);
  fill_matrix(second);
  EXPECT_THROW(first.SubMatrix(second), std::out_of_range);
}

TEST(MulMatrix, MulMatrix_true) {
  S21Matrix first(4, 3);
  S21Matrix second(3, 4);
  S21Matrix res(4, 4);
  fill_matrix(first);
  fill_matrix(second);
  first *= second;
  res(0, 0) = 20;
  res(0, 1) = 23;
  res(0, 2) = 26;
  res(0, 3) = 29;
  res(1, 0) = 56;
  res(1, 1) = 68;
  res(1, 2) = 80;
  res(1, 3) = 92;
  res(2, 0) = 92;
  res(2, 1) = 113;
  res(2, 2) = 134;
  res(2, 3) = 155;
  res(3, 0) = 128;
  res(3, 1) = 158;
  res(3, 2) = 188;
  res(3, 3) = 218;
  ASSERT_TRUE(first.EqMatrix(res));
}

TEST(MulMatrix, MulMatrix_true_2) {
  S21Matrix first(2, 2);
  S21Matrix second(2, 2);
  S21Matrix res(2, 2);
  fill_matrix(first);
  fill_matrix(second);
  res[0][0] = 2;
  res[0][1] = 3;
  res[1][0] = 6;
  res[1][1] = 11;
  S21Matrix mult = first * second;
  ASSERT_TRUE(mult.EqMatrix(res));
}

TEST(MulMatrix, MulMatrix_err) {
  S21Matrix first(4, 3);
  S21Matrix second(4, 3);
  fill_matrix(first);
  fill_matrix(second);
  EXPECT_THROW(first.MulMatrix(second), std::out_of_range);
}

TEST(MulNumber, MulNumber_true) {
  S21Matrix first(4, 4);
  fill_matrix(first);
  first *= 7;
  S21Matrix res(4, 4);
  res(0, 1) = 7;
  res(0, 2) = 14;
  res(0, 3) = 21;
  res(1, 0) = 28;
  res(1, 1) = 35;
  res(1, 2) = 42;
  res(1, 3) = 49;
  res(2, 0) = 56;
  res(2, 1) = 63;
  res(2, 2) = 70;
  res(2, 3) = 77;
  res(3, 0) = 84;
  res(3, 1) = 91;
  res(3, 2) = 98;
  res(3, 3) = 105;
  ASSERT_TRUE(first.EqMatrix(res));
}

TEST(MulNumber, MulNumber_true2) {
  S21Matrix first(5, 6);
  S21Matrix res(5, 6);
  fill_matrix_back(first);
  first *= 3.5;
  res(0, 0) = 101.5;
  res(0, 1) = 98;
  res(0, 2) = 94.5;
  res(0, 3) = 91;
  res(0, 4) = 87.5;
  res(0, 5) = 84;
  res(1, 0) = 80.5;
  res(1, 1) = 77;
  res(1, 2) = 73.5;
  res(1, 3) = 70;
  res(1, 4) = 66.5;
  res(1, 5) = 63;
  res(2, 0) = 59.5;
  res(2, 1) = 56;
  res(2, 2) = 52.5;
  res(2, 3) = 49;
  res(2, 4) = 45.5;
  res(2, 5) = 42;
  res(3, 0) = 38.5;
  res(3, 1) = 35;
  res(3, 2) = 31.5;
  res(3, 3) = 28;
  res(3, 4) = 24.5;
  res(3, 5) = 21;
  res(4, 0) = 17.5;
  res(4, 1) = 14;
  res(4, 2) = 10.5;
  res(4, 3) = 7;
  res(4, 4) = 3.5;
  res(4, 5) = 0;
  ASSERT_TRUE(first == res);
}

TEST(MulNumber, MulNumber_true_3) {
  S21Matrix first(2, 2);
  S21Matrix res(2, 2);
  fill_matrix(first);
  res[0][1] = 2;
  res[1][0] = 4;
  res[1][1] = 6;
  S21Matrix mult = first * 2;
  ASSERT_TRUE(mult == res);
}

TEST(Transpose, Transpose_true) {
  S21Matrix first(4, 3);
  S21Matrix res(3, 4);
  fill_matrix(first);
  S21Matrix transponse = first.Transpose();
  res(0, 1) = 3;
  res(0, 2) = 6;
  res(0, 3) = 9;
  res(1, 0) = 1;
  res(1, 1) = 4;
  res(1, 2) = 7;
  res(1, 3) = 10;
  res(2, 0) = 2;
  res(2, 1) = 5;
  res(2, 2) = 8;
  res(2, 3) = 11;
  ASSERT_TRUE(transponse.EqMatrix(res));
}

TEST(Transpose, Transpose_true2) {
  S21Matrix first(5, 2);
  S21Matrix res(2, 5);
  fill_matrix_back(first);
  S21Matrix transponse = first.Transpose();
  res(0, 0) = 9;
  res(0, 1) = 7;
  res(0, 2) = 5;
  res(0, 3) = 3;
  res(0, 4) = 1;
  res(1, 0) = 8;
  res(1, 1) = 6;
  res(1, 2) = 4;
  res(1, 3) = 2;
  res(1, 4) = 0;

  ASSERT_TRUE(transponse.EqMatrix(res));
}

TEST(CalcComplements, CalcComplements_true) {
  S21Matrix first(3, 3);
  S21Matrix res(3, 3);

  first(0, 0) = 1;
  first(0, 1) = 2;
  first(0, 2) = 3;
  first(1, 0) = 0;
  first(1, 1) = 4;
  first(1, 2) = 2;
  first(2, 0) = 5;
  first(2, 1) = 2;
  first(2, 2) = 1;

  res(0, 0) = 0;
  res(0, 1) = 10;
  res(0, 2) = -20;
  res(1, 0) = 4;
  res(1, 1) = -14;
  res(1, 2) = 8;
  res(2, 0) = -8;
  res(2, 1) = -2;
  res(2, 2) = 4;

  S21Matrix calcCompl = first.CalcComplements();
  ASSERT_TRUE(calcCompl == res);
}

TEST(CalcComplements, CalcComplements_false) {
  S21Matrix first(3, 4);
  fill_matrix(first);
  EXPECT_THROW(first.CalcComplements(), std::out_of_range);
}

TEST(Determinant, Determinant_true) {
  S21Matrix first(3, 3);
  first(0, 0) = 1;
  first(0, 1) = 3;
  first(0, 2) = 4;
  first(1, 0) = 0;
  first(1, 1) = 2;
  first(1, 2) = 1;
  first(2, 0) = 1;
  first(2, 1) = 5;
  first(2, 2) = -1;

  double determ = first.Determinant();
  double res = -12;

  ASSERT_DOUBLE_EQ(determ, res);
}

TEST(Determinant, Determinant_false) {
  S21Matrix first(100, 99);
  fill_matrix(first);
  EXPECT_THROW(first.Determinant(), std::out_of_range);
}

TEST(InverseMatrix, InverseMatrix_true) {
  S21Matrix first(3, 3);
  S21Matrix res(3, 3);

  first(0, 0) = 2;
  first(0, 1) = 5;
  first(0, 2) = 7;
  first(1, 0) = 6;
  first(1, 1) = 3;
  first(1, 2) = 4;
  first(2, 0) = 5;
  first(2, 1) = -2;
  first(2, 2) = -3;

  res(0, 0) = -1;
  res(0, 1) = 1;
  res(0, 2) = -1;
  res(1, 0) = 38;
  res(1, 1) = -41;
  res(1, 2) = 34;
  res(2, 0) = -27;
  res(2, 1) = 29;
  res(2, 2) = -24;

  S21Matrix inverce = first.InverseMatrix();
  ASSERT_TRUE(inverce.EqMatrix(res));
}

TEST(InverseMatrix, InverseMatrix_false) {
  S21Matrix first(3, 3);
  fill_matrix(first);
  EXPECT_THROW(first.InverseMatrix(), std::out_of_range);
}

TEST(Set_rows, Set_rows_true) {
  S21Matrix first(2, 2);
  S21Matrix res(3, 2);
  fill_matrix(first);
  first.Set_rows(3);
  res[0][0] = 0;
  res[0][1] = 1;
  res[1][0] = 2;
  res[1][1] = 3;
  ASSERT_TRUE(first.EqMatrix(res));
}

TEST(Set_rows, Set_rows_false) {
  S21Matrix first(2, 2);
  EXPECT_THROW(first.Set_rows(-1), std::out_of_range);
}

TEST(Set_cols, Set_cols_true) {
  S21Matrix first(2, 2);
  S21Matrix res(2, 3);
  fill_matrix(first);
  first.Set_cols(3);
  res[0][0] = 0;
  res[0][1] = 1;
  res[1][0] = 2;
  res[1][1] = 3;
  ASSERT_TRUE(first.EqMatrix(res));
}

TEST(Set_cols, Set_cols_false) {
  S21Matrix first(2, 2);
  EXPECT_THROW(first.Set_cols(-2), std::out_of_range);
}

TEST(reference_to_number, reference_to_number_false) {
  S21Matrix first(3, 3);
  EXPECT_THROW(first(3, 4), std::out_of_range);
}

TEST(reference_to_number, reference_to_number_false_2) {
  S21Matrix first(3, 3);
  EXPECT_THROW(first[-1], std::out_of_range);
}

TEST(equalization_copy, equalization_copy_true) {
  const S21Matrix first(2, 2);
  S21Matrix second;
  fill_matrix(first);
  second = first;
  ASSERT_TRUE(second == first);
}

TEST(move_constructor, move_constructor_true) {
  S21Matrix first(4, 4);
  fill_matrix(first);
  S21Matrix second = std::move(first);
  ASSERT_TRUE(first.Get_cols() == 0);
  ASSERT_TRUE(first.Get_rows() == 0);
}

TEST(line_change, line_change_false) {
  const S21Matrix first(3, 3);
  first[0][1] = 2;
  first[0][2] = 5;
  first[1][1] = 7;
  first[1][2] = -4;
  first[2][1] = -8;
  first[2][2] = 9;
  ASSERT_TRUE(first.Determinant() == 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}