// PHYS 30762 Programming in C++
// Author: Enrico Zammit Lonardelli
// Date: 11/03/2020
// Assignment 6
// A matrix class to store matrix data and perform arithmetic operations
// together with deep copying and moving operations deponstrations.

#include <iostream>
#include <regex>
#include <string>
#include <iterator>
#include <cmath>
class matrix
{
  friend std::ostream &operator<<(std::ostream &os, const matrix &mat);
  friend std::istream &operator>>(std::istream &is, matrix &mat);

private:
  double *matrix_data{nullptr};
  size_t rows{0};
  size_t columns{0};
  size_t last_filled_row{0};

public:
  matrix() = default;
  matrix(size_t r, size_t c)
  {
    rows = r;
    columns = c;
    matrix_data = new double[rows * columns];
  };
  matrix(const matrix &arr);
  matrix &operator=(const matrix &arr);
  matrix(matrix &&arr);
  matrix &operator=(matrix &&arr);
  ~matrix() { delete[] matrix_data; };
  size_t get_rows() const { return rows; }
  size_t get_cols() const { return columns; }
  size_t index(size_t m, size_t n) const
  {
    if (m > 0 && m <= rows && n > 0 && n <= columns)
      return (n - 1) + (m - 1) * columns;
    else
    {
      throw "Error: out of range";
    }
  }
  size_t get_size() const
  {
    return rows * columns;
  }
  double &operator()(const size_t m, const size_t n) const { return matrix_data[index(m, n)]; }
  matrix operator+(const matrix &addend) const;
  matrix operator-(const matrix &addend) const;
  matrix operator*(const matrix &multiplier) const;
  matrix get_reduced_matrix(const size_t m, const size_t n) const;
  double determinant(matrix submatrix) const;
};
double matrix::determinant(matrix submatrix) const
{
  int determinant;
  if (submatrix.rows != submatrix.columns)
  {
    throw "Matrix is not a square matrix";
  }
  if (submatrix.rows == 2 && submatrix.columns == 2)
  {
    determinant = submatrix(1, 1) * submatrix(2, 2) - submatrix(1, 2) * submatrix(2, 1);
    return determinant;
  }
  for (int j{1}; j <= submatrix.columns; j += 1)
  {
    determinant += std::pow(-1, 1 + j) * submatrix(1, j) * submatrix.determinant(submatrix.get_reduced_matrix(1, j));
  }
  return determinant;
}
matrix matrix::operator+(const matrix &addend) const
{
  matrix addition{rows, columns};
  if (rows == addend.rows && columns == addend.columns)
  {
    for (size_t i{1}; i <= rows; i += 1)
    {
      for (size_t j{1}; j <= columns; j += 1)
      {
        addition.matrix_data[index(i, j)] = matrix_data[index(i, j)] + addend(i, j);
      }
    }
  }
  else
  {
    throw "Operation not possible. Matrices must have same dimensions.";
  }
  return addition;
}
matrix matrix::operator-(const matrix &addend) const
{
  matrix subtraction{rows, columns};
  if (rows == addend.rows && columns == addend.columns)
  {
    for (size_t i{1}; i <= rows; i += 1)
    {
      for (size_t j{1}; j <= columns; j += 1)
      {
        subtraction.matrix_data[index(i, j)] = matrix_data[index(i, j)] - addend(i, j);
      }
    }
  }
  else
  {
    throw "Operation not possible. Matrices must have same dimensions.";
  }
  return subtraction;
}
matrix matrix::operator*(const matrix &multiplier) const
{
  matrix product{rows, multiplier.columns};
  if (rows == multiplier.columns)
  {
    for (size_t i{1}; i <= rows; i += 1)
    {
      for (size_t j{1}; j <= multiplier.columns; j += 1)
      {
        product.matrix_data[index(i, j)] = 0;
        for (size_t n{1}; n <= columns; n += 1)
        {
          product.matrix_data[index(i, j)] += matrix_data[index(i, n)] * multiplier(n, j);
        }
      }
    }
  }
  else
  {
    throw "Operation not possible. Matrix A must have the same number of columns as rows in matrix B.";
  }
  return product;
}
matrix matrix::get_reduced_matrix(const size_t m, const size_t n) const
{
  matrix reduced_matrix(rows - 1, columns - 1);
  reduced_matrix.last_filled_row = rows - 1;
  size_t reduced_i{1};
  for (size_t i{1}; i <= rows; i += 1)
  {
    if (i != m)
    {
      size_t reduced_j{1};
      for (size_t j{1}; j <= columns; j += 1)
      {
        if (j != n)
        {
          reduced_matrix.matrix_data[reduced_matrix.index(reduced_i, reduced_j)] = matrix_data[index(i, j)];
          reduced_j += 1;
        }
      }
      reduced_i += 1;
    }
  }
  return reduced_matrix;
}
matrix::matrix(const matrix &arr)
{
  matrix_data = nullptr;
  rows = arr.get_rows();
  columns = arr.get_cols();
  last_filled_row = arr.last_filled_row;
  // Now copy size and declare new array
  if (rows * columns > 0)
  {
    matrix_data = new double[rows * columns];
    // Copy values into new array
    for (size_t i{1}; i <= rows; i += 1)
    {
      for (size_t j{1}; j <= columns; j += 1)
      {
        matrix_data[index(i, j)] = arr(i, j);
      }
    }
  }
}

matrix &matrix::operator=(const matrix &arr)
{
  if (&arr == this)
    return *this; // no self assignment
  // First delete this object's array
  delete[] matrix_data;
  matrix_data = nullptr;
  rows = arr.get_rows();
  columns = arr.get_cols();
  last_filled_row = arr.last_filled_row;
  // Now copy size and declare new array
  if (rows * columns > 0)
  {
    matrix_data = new double[rows * columns];
    // Copy values into new array
    for (size_t i{1}; i <= rows; i += 1)
    {
      for (size_t j{1}; j <= columns; j += 1)
      {
        matrix_data[index(i, j)] = arr(i, j);
      }
    }
  }
  return *this;
}

matrix::matrix(matrix &&arr)
{
  rows = arr.rows;
  columns = arr.columns;
  last_filled_row = arr.last_filled_row;
  matrix_data = arr.matrix_data;
  arr.rows = 0;
  arr.columns = 0;
  arr.last_filled_row = 0;
  arr.matrix_data = nullptr;
}

matrix &matrix::operator=(matrix &&arr)
{
  std::swap(rows, arr.rows);
  std::swap(columns, arr.columns);
  std::swap(last_filled_row, arr.last_filled_row);
  std::swap(matrix_data, arr.matrix_data);
  return *this;
}

std::ostream &operator<<(std::ostream &os, const matrix &mat)
{
  if (mat.rows == 0 && mat.columns == 0)
  {
    os << "Matrix is empty!" << std::endl;
    return os;
  }
  for (size_t i{1}; i <= mat.rows; i += 1)
  {
    for (size_t j{1}; j <= mat.columns; j += 1)
    {
      if (j == 1)
      {
        if (i == 1)
        {
          os << "( ";
        }
        else
        {
          os << "| ";
        }
      }
      os << mat(i, j) << " ";
      if (j == mat.columns)
      {
        if (i == mat.rows)
        {
          os << ")";
        }
        else
        {
          os << "|";
        }
      }
    }
    os << std::endl;
  }
  return os;
}

std::istream &operator>>(std::istream &is, matrix &output_matrix)
{
  std::string input;
  std::getline(is, input);
  bool isRow{true};
  const std::regex find_elements{"[+-]?[0-9]+[.]?[0-9]*"};
  matrix matrix_to_append;
  auto words_begin =
      std::sregex_iterator(input.begin(), input.end(), find_elements);
  auto words_end = std::sregex_iterator();

  int matches_found = std::distance(words_begin, words_end);

  if (matches_found > 0)
  {
    if (isRow)
    {
      matrix mat(1, matches_found);
      int j{1};
      for (std::sregex_iterator i = words_begin; i != words_end; ++i)
      {
        std::smatch match = *i;
        mat.matrix_data[mat.index(1, j)] = stod(match.str());
        j += 1;
      }
      matrix_to_append = std::move(mat);
    }
    else
    {
      matrix mat{matches_found, 1};
      int j{1};
      for (std::sregex_iterator i = words_begin; i != words_end; ++i)
      {
        std::smatch match = *i;
        mat.matrix_data[mat.index(j, 1)] = stod(match.str());
        j += 1;
      }
      matrix_to_append = std::move(mat);
    }
  }
  if (matrix_to_append.rows != 1)
  {
    throw "Please add one row at a time.";
  }
  if (matrix_to_append.columns != output_matrix.columns)
  {
    throw "Please make sure you are following the dimensions of the matrix.";
  }
  for (int j{1}; j <= matrix_to_append.columns; j += 1)
  {
    output_matrix.matrix_data[output_matrix.index(output_matrix.last_filled_row + 1, j)] = matrix_to_append(1, j);
  }
  output_matrix.last_filled_row += 1;
  return is;
}

int main()
{

  std::cout << "Demonstration of default constructor." << std::endl;
  matrix a1;
  std::cout << "Matrix a1:\n"
            << a1 << std::endl;
  std::cout << "Demonstration of parametrized constructor." << std::endl;
  const size_t m{3};
  const size_t n{3};
  matrix a2{m, n};
  std::cout << "Input for matrix 2 of size:"
            << "(" << m << "," << n << ")" << std::endl;
  for (size_t i{1}; i <= a2.get_rows(); i += 1)
  {
    matrix input_row;
    std::cout << "Please input row " << i << " of " << a2.get_rows() << " as a sequence of elements delimited by any non-numeric character/s or spaces."
              << std::endl;
    std::cin >> a2;
  }
  std::cout << "Matrix a2:\n"
            << a2 << std::endl;
  std::cout << "Deep copy a3 from a2 using copy assignment." << std::endl;
  matrix a3 = a2;
  std::cout << "Matrix a3:\n"
            << a3 << std::endl;
  std::cout << "Contents of original matrix a2 modified for proof that copied matrix is unchanged." << std::endl;
  a2 = a2 + a3;
  std::cout << "Matrix a2:\n"
            << a2;
  std::cout << "Matrix a3:\n"
            << a3 << std::endl;
  std::cout << "Deep copy a4 from a2 using copy constructor." << std::endl;
  matrix a4{a2};
  std::cout << "Matrix a4:\n"
            << a4 << std::endl;
  std::cout << "Row and Col 2,2 of original matrix a2 deleted for proof that copied matrix is unchanged." << std::endl;
  a2 = a2.get_reduced_matrix(2, 2);
  std::cout << "Matrix a2:\n"
            << a2;
  std::cout << "Matrix a4:\n"
            << a4 << std::endl;
  std::cout << "Move a2 into a4 using move copy constructor." << std::endl;
  matrix a5{std::move(a2)};
  std::cout << "Matrix a2:\n"
            << a2;
  std::cout << "Matrix a5:\n"
            << a5 << std::endl;
  std::cout << "Move a5 into a6 using move assignment." << std::endl;
  matrix a6 = std::move(a5);
  std::cout << "Matrix a5:\n"
            << a5;
  std::cout << "Matrix a6:\n"
            << a6 << std::endl;
  std::cout << "\n--Arithmetic Operations--\n"
            << std::endl;
  const size_t m_a{3};
  const size_t n_a{3};
  matrix a{m_a, n_a};
  std::cout << "Input for matrix a of size:"
            << "(" << m_a << "," << n_a << ")" << std::endl;
  for (size_t i{1}; i <= a.get_rows(); i += 1)
  {
    matrix input_row;
    std::cout << "Please input row " << i << " of " << a.get_rows() << " as a sequence of elements delimited by any non-numeric character/s or spaces."
              << std::endl;
    std::cin >> a;
  }

  const size_t m_b{3};
  const size_t n_b{3};
  matrix b{m_b, n_b};
  std::cout << "Input for matrix b of size:"
            << "(" << m_b << "," << n_b << ")" << std::endl;
  for (size_t i{1}; i <= b.get_rows(); i += 1)
  {
    matrix input_row;
    std::cout << "Please input row " << i << " of " << b.get_rows() << " as a sequence of elements delimited by any non-numeric character/s or spaces."
              << std::endl;
    std::cin >> b;
  }
  std::cout << "Matrix a:\n"
            << a;
  std::cout << "Matrix b:\n"
            << b;
  std::cout << "(Matrix a + Matrix b)\n"
            << a + b;
  std::cout << "(Matrix a - Matrix b)\n"
            << a - b;
  std::cout << "(Matrix a * Matrix b)\n"
            << a * b;

  std::cout << "Determinant of Matrix a: "
            << a.determinant(a) << std::endl;
  return 0;
}