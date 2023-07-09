#ifndef SPP_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H
#define SPP_S21_MATRIXPLUS_1_SRC_S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

  S21Matrix Matrix_decomposition(int ignoring_rows, int ignoring_cols) const;
  void Copy_data(const S21Matrix &other);
  void Initialize_this_matrix();
  void Free_matrix();
  double Determinant_gausa() const;
  void Line_division(int rows, double divider);
  void Row_subtraction(const int row);
  bool Line_change();

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other) const noexcept;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);
  double &operator()(int rows, int cols) const;
  double *operator[](int row) const;

  int Get_rows() const noexcept;
  int Get_cols() const noexcept;
  void Set_rows(const int new_value_rows);
  void Set_cols(const int new_value_cols);
};

#endif