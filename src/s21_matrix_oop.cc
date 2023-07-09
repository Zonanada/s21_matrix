#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw std::out_of_range(
        "Incorrect input, rows and columns must be greater than zero");
  }
  Initialize_this_matrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  Initialize_this_matrix();
  Copy_data(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { Free_matrix(); }

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.Get_rows() || cols_ != other.Get_cols()) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int z = 0; z < cols_; z++) {
      if (fabs(matrix_[i][z] - other.matrix_[i][z]) > 0.0000001) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }

  for (int i = 0; i < rows_; i++) {
    for (int z = 0; z < cols_; z++) {
      matrix_[i][z] += other.matrix_[i][z];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }

  for (int i = 0; i < rows_; i++) {
    for (int z = 0; z < cols_; z++) {
      matrix_[i][z] -= other.matrix_[i][z];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int z = 0; z < cols_; z++) {
      matrix_[i][z] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (rows_ != other.cols_ && cols_ != other.rows_) {
    throw std::out_of_range(
        "Invalid input, the number of rows must equal the number of columns of "
        "another matrix");
  }

  S21Matrix res_mult(rows_, other.Get_cols());
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        res_mult.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(res_mult);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix transponse_matrix(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transponse_matrix.matrix_[j][i] = matrix_[i][j];
    }
  }
  return transponse_matrix;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input, matrix must be square");
  }

  S21Matrix matrix_res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_res.matrix_[i][j] = Matrix_decomposition(i, j).Determinant();
      if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
        matrix_res.matrix_[i][j] *= -1;
    }
  }

  return matrix_res;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input, matrix must be square");
  }
  if (rows_ == 1 && cols_ == 1) return matrix_[0][0];
  if (rows_ == 2 && cols_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }
  return Determinant_gausa();
}

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix matrix_result(rows_, cols_);
  S21Matrix copy_this(*this);

  double determinant_this = copy_this.Determinant();

  if (fabs(determinant_this) > 1e-6) {
    S21Matrix minore_matrix = copy_this.CalcComplements();
    S21Matrix matrix_transponse = minore_matrix.Transpose();
    matrix_result.Copy_data(matrix_transponse);
  } else {
    throw std::out_of_range("Incorrect input, determinant must not be zero");
  }
  return matrix_result;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix copy_this(*this);
  copy_this.SumMatrix(other);
  return copy_this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix copy_this(*this);
  copy_this.SubMatrix(other);
  return copy_this;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix copy_this(*this);
  copy_this.MulNumber(num);
  return copy_this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix copy_this(*this);
  copy_this.MulMatrix(other);
  return copy_this;
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return (*this).EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (rows_ != other.Get_rows() || cols_ != other.Get_cols()) {
    Free_matrix();
    rows_ = other.Get_rows();
    cols_ = other.Get_cols();
    Initialize_this_matrix();
  }
  Copy_data(other);
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    Free_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(int rows, int cols) const {
  if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[rows][cols];
}

double *S21Matrix::operator[](int row) const {
  if (row >= rows_ || row < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row];
}

int S21Matrix::Get_rows() const noexcept { return rows_; }

int S21Matrix::Get_cols() const noexcept { return cols_; }

void S21Matrix::Set_rows(const int new_value_rows) {
  if (new_value_rows < 1) {
    throw std::out_of_range("Must be a positive value");
  }
  if (rows_ != new_value_rows) {
    S21Matrix tmp(new_value_rows, cols_);
    tmp.Copy_data(*this);
    *this = std::move(tmp);
  }
}

void S21Matrix::Set_cols(const int new_value_cols) {
  if (new_value_cols < 1) {
    throw std::out_of_range("Must be a positive value");
  }
  if (cols_ != new_value_cols) {
    S21Matrix tmp(rows_, new_value_cols);
    tmp.Copy_data(*this);
    *this = std::move(tmp);
  }
}

S21Matrix S21Matrix::Matrix_decomposition(int ignoring_rows,
                                          int ignoring_cols) const {
  S21Matrix decomp(rows_ - 1, cols_ - 1);
  int decomp_rows = 0;
  int decomp_cols = 0;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i != ignoring_rows && j != ignoring_cols) {
        decomp.matrix_[decomp_rows][decomp_cols] = matrix_[i][j];
        decomp_rows++;
        if (decomp_rows == cols_ - 1) {
          decomp_rows = 0;
          decomp_cols++;
        }
      }
    }
  }
  return decomp;
}

void S21Matrix::Free_matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
    matrix_[i] = nullptr;
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

void S21Matrix::Copy_data(const S21Matrix &other) {
  for (int i = 0; i < rows_ && i < other.rows_; i++) {
    for (int j = 0; j < cols_ && j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::Initialize_this_matrix() {
  matrix_ = new double *[rows_];
  if (matrix_ == nullptr) throw std::out_of_range("Memory allocation error");

  for (double **ptr_row = matrix_; ptr_row - matrix_ < rows_; ptr_row++) {
    *ptr_row = new double[cols_]();
    if (ptr_row == nullptr) throw std::out_of_range("Memory allocation error");
  }
}

void S21Matrix::Line_division(const int rows, const double divider) {
  for (int i = 0; i < cols_; i++) {
    matrix_[rows][i] /= divider;
  }
}

bool S21Matrix::Line_change() {
  int line = 1;
  for (int i = 1; i < rows_; i++) {
    if (fabs(matrix_[line][0]) < 1e-6) {
      line++;
    } else {
      break;
    }
    if (i == rows_ - 1) return false;
  }
  for (int i = 0; i < cols_; i++) {
    double tmp = matrix_[0][i];
    matrix_[0][i] = matrix_[line][i];
    matrix_[line][i] = tmp;
  }
  return true;
}

void S21Matrix::Row_subtraction(const int row) {
  for (int i = row + 1; i < rows_; i++) {
    bool first_num = true;
    for (int z = row; z < cols_; z++) {
      if (first_num && fabs(matrix_[i][row]) < 1e-6) break;
      first_num = false;
      matrix_[i][z] -= matrix_[row][z];
    }
  }
}

double S21Matrix::Determinant_gausa() const {
  S21Matrix copy_this(*this);
  if (fabs(matrix_[0][0]) < 1e-6 && !copy_this.Line_change()) return 0;
  double *numbers_with_abbreviations = new double[rows_ * 2]();
  int cout_num = 0;
  for (int i = 0; i < cols_ - 1; i++) {
    for (int j = i; j < rows_; j++) {
      if (fabs(copy_this[j][i]) > 1e-6) {
        numbers_with_abbreviations[cout_num] = copy_this[j][i];
        cout_num++;
        copy_this.Line_division(j, copy_this[j][i]);
      }
    }
    copy_this.Row_subtraction(i);
  }
  numbers_with_abbreviations[cout_num] = copy_this[rows_ - 1][cols_ - 1];
  double result = numbers_with_abbreviations[0];
  for (int i = 1; i < cout_num + 1; i++) {
    if (fabs(numbers_with_abbreviations[i]) < 1e-6) return 0;
    result *= numbers_with_abbreviations[i];
  }
  delete[] numbers_with_abbreviations;
  return result;
}