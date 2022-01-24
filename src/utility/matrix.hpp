#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <typeinfo>
#include <limits>
#include <iostream>
#include <stdexcept>

// TODO: add operators for double_matrix;
//       add matrix multiplication

template<std::size_t rows, std::size_t columns, typename Type>
class Matrix
{
public:

    using value_type       = Type;
    using const_value_type = const Type;
    using reference        = value_type &;
    using const_reference  = const_value_type &;
    using pointer          = value_type *;
    using const_pointer    = const_value_type *;
    using iterator         = value_type*;
    using const_iterator   = const value_type*;
    using size_type        = std::size_t;
    using const_size_type  = const std::size_t;

    /**
     * @brief Matrix is default constructor (does nothing).
     */
    Matrix() : m_data() {}

    // Constructors for vectors
    /**
     * @brief Matrix is parametrized constructor for vector 1x1.
     * @param x is initial value.
     */
    explicit Matrix(const_reference x) : m_data() {
        static_assert (rows * columns == 1, "MATRIX::ERROR, matrix size ins't equal 1!");
        static_assert (rows == 1 && columns == 1, "MATRIX::ERROR, rows|columns count isn't equal 1!" );

        m_data[0] = x;
    }
    /**
     * @brief Matrix is parametrized constructor for vector 1x2.
     * @param x is x initial value.
     * @param y is y initial value.
     */
    Matrix(const_reference x,
           const_reference y) : m_data() {
        static_assert (rows * columns == 2, "MATRIX::ERROR, matrix size ins't equal 2!");
        static_assert ((rows == 1 && columns == 2) || (columns == 1 && rows == 2),
                      "MATRIX::ERROR, rows|columns count isn't equal 1|2!" );
        m_data[0] = x;
        m_data[1] = y;
    }
    /**
     * @brief Matrix is parametrized constructor for vector 1x3.
     * @param x is x initial value.
     * @param y is y initial value.
     * @param z is z initial value.
     */
    Matrix(const_reference x,
           const_reference y,
           const_reference z) : m_data() {
        static_assert (rows * columns == 3, "MATRIX::ERROR, matrix size ins't equal 3!");
        static_assert ((rows == 1 && columns == 3) || (columns == 1 && rows == 3),
                      "MATRIX::ERROR, rows|columns count isn't equal 1|3!" );
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
    }
    /**
     * @brief Matrix is parametrized constructor for vector 1x4.
     * @param x is x initial value.
     * @param y is y initial value.
     * @param z is z initial value.
     * @param w is w initial value.
     */
    Matrix(const_reference x,
           const_reference y,
           const_reference z,
           const_reference w) : m_data() {
        static_assert (rows * columns == 4, "MATRIX::ERROR, matrix size ins't equal 4!");
        static_assert ((rows == 1 && columns == 4) ||
                       (columns == 1 && rows == 4),
                      "MATRIX::ERROR, rows|columns count isn't equal 1|4!" );
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
        m_data[3] = w;
    }
    /**
     * @brief Matrix is parametrized constructor for vector 1xn.
     * @param x is the first initial value.
     * @param y is the second initial value.
     * @param z is the third initial value.
     * @param w is the fourth initial value.
     * @param args is from the fourts to n inital values.
     */
    template<typename ...ArgsType>
    Matrix(const_reference x,
           const_reference y,
           const_reference z,
           const_reference w,
           const ArgsType&... args) : m_data() {
        static_assert (rows * columns == sizeof...(args) + 4, "MATRIX::ERROR, matrix size ins't equal args + 4!");
        static_assert (rows == 1, "MATRIX::ERROR, rows count isn't equal 1!" );
        static_assert (columns == sizeof...(args) + 4, "MATRIX::ERROR, rows count isn't equal args + 4!" );
        m_data[0] = x;
        m_data[1] = y;
        m_data[2] = z;
        m_data[3] = w;
        int i = 4;
        auto tmp = {(m_data[i++] = args, 0)...};
        static_cast<void>(tmp);
    }

    // Constructor for any matrixes
    /**
     * @brief Matrix is parametrized constructor for matrices of any sizes.
     * @param list is initializer_list of initializer_lists.
     */
    explicit Matrix(const std::initializer_list<std::initializer_list<value_type>> & list) :
        m_data()
    {
        size_type listSize = 0;
        if(list.begin() != list.end()){
            listSize = list.begin()->size();
        }

        if(columns == 1 && list.size() == 1){
            assert(listSize == rows);
            std::copy(list.begin()->begin(), list.end()->end(), m_data.data());
        } else {
            assert(list.size() == rows);
            assert(listSize == columns);

            size_type rowIndex = 0;
            for(const auto &row : list) {
                assert(listSize == row.size());
                size_type columnIndex = 0;
                for(const auto &e : row) {
                    this->coeffRef(rowIndex, columnIndex) = e;
                    ++columnIndex;
                }
                ++rowIndex;
            }
        }
    }

    ~Matrix() {}

public:
    bool operator==(const Matrix &other) const {
        bool result = false;
        if(this->rowsCount() == other.rowsCount() &&
           this->columnsCount() == other.columnsCount()) {
            result = std::equal(this->begin(), this->end(), other.begin());
        } else {
            result = false;
        }
        return result;
    }

public:
    // Access methods
    /**
     * @return the number of rows.
     */
    constexpr size_type rowsCount() const noexcept {
        return rows;
    }
    /**
     * @return the number of columns.
     */
    constexpr size_type columnsCount() const noexcept {
        return columns;
    }
    /**
     * @return the the number of coefficients, which is rows * columns.
     */
    constexpr size_type size() const noexcept {
        return this->rowsCount() * this->columnsCount();
    }
    /**
     * @return a reference coefficient at given index, with bounds
     * checking. If pos is not within the range of the container,
     * an exception of type std::out_of_range is thrown.
     */
    reference coeffRef(const_size_type index) {
        assert(index < rows * columns);
        if(index < rows * columns) {
            return this->m_data[index];
        } else {
            throw std::out_of_range("ERROR::MATRIX, index out of range!");
        }
    }
    /**
     * @return a const reference to the coefficient at given index,
     * with bounds checking. If pos is not within the range of the
     * container, an exception of type std::out_of_range is thrown.
     */
    const_reference coeffRef(const_size_type index) const {
        assert(index < rows * columns);
        if(index < rows * columns) {
            return this->m_data[index];
        } else {
            throw std::out_of_range("ERROR::MATRIX, index out of range!");
        }
    }
    /**
     * @return a reference to the coefficient at given row and column,
     * with bounds checking. If pos is not within the range of the
     * container, an exception of type std::out_of_range is thrown.
     */
    reference coeffRef(const_size_type row, const_size_type column) {
        assert (row >= 0 && row < rows && column >= 0 && column < columns);
        if(row >= 0 && row < rows && column >= 0 && column < columns) {
            return this->m_data[row * columns + column];
        } else {
            throw std::out_of_range("ERROR::MATRIX, invalide row and/or column, out of range!");
        }
    }
    /**
     * @return a reference to the coefficient at given row and column,
     * with bounds checking. If pos is not within the range of the
     * container, an exception of type std::out_of_range is thrown.
     */
    const_reference coeffRef(const_size_type row, const_size_type column) const {
        assert (row >= 0 && row < rows && column >= 0 && column < columns);
        if(row >= 0 && row < rows && column >= 0 && column < columns) {
            return this->m_data[row * columns + column];
        } else {
            throw std::out_of_range("ERROR::MATRIX, invalide row and/or column, out of range!");
        }
    }
    /**
     * @return the coefficient at given index, with bounds checking.
     * If pos is not within the range of the container, an exception
     * of type std::out_of_range is thrown.
     */
    value_type coeff(const_size_type index) const {
        assert(index < rows * columns);
        if(index < rows * columns) {
            return this->m_data[index];
        } else {
            throw std::out_of_range("ERROR::MATRIX, index out of range!");
        }
    }
    /**
     * @return the coefficient at given row and column, with bounds
     * checking. If pos is not within the range of the container,
     * an exception of type std::out_of_range is thrown.
     */
    value_type coeff(const_size_type row, const_size_type column) const {
        assert (row >= 0 && row < rows && column >= 0 && column < columns);
        if(row >= 0 && row < rows && column >= 0 && column < columns) {
            return this->m_data[row * columns + column];
        } else {
            throw std::out_of_range("ERROR::MATRIX, invalide row and/or column, out of range!");
        }
    }
    /**
     * equivalent to operator[](0).
     */
    reference x() {
        static_assert(rows * columns >= 1, "MATRIX::ERROR, matrix size less than 1!");
        return this->m_data[0];
    }
    /**
     * equivalent to operator[](1).
     */
    reference y() {
        static_assert (rows * columns >= 2, "MATRIX::ERROR, matrix size less than 2!");
        return this->m_data[1];
    }
    /**
     * equivalent to operator[](2).
     */
    reference z() {
        static_assert (rows * columns >= 3, "MATRIX::ERROR, matrix size less than 3!");
        return this->m_data[2];
    }
    /**
     * equivalent to operator[](3).
     */
    reference w() {
        static_assert (rows * columns >= 4, "MATRIX::ERROR, matrix size less than 4!");
        return this->m_data[3];
    }
    /**
     * equivalent to operator[](0).
     */
    value_type x() const {
        static_assert(rows * columns >= 1, "MATRIX::ERROR, matrix size less than 1!");
        return this->m_data[0];
    }
    /**
     * equivalent to operator[](1).
     */
    value_type y() const {
        static_assert (rows * columns >= 2, "MATRIX::ERROR, matrix size less than 2!");
        return this->m_data[1];
    }
    /**
     * equivalent to operator[](2).
     */
    value_type z() const {
        static_assert (rows * columns >= 3, "MATRIX::ERROR, matrix size less than 3!");
        return this->m_data[2];
    }
    /**
     * equivalent to operator[](3).
     */
    value_type w() const {
        static_assert (rows * columns >= 4, "MATRIX::ERROR, matrix size less than 4!");
        return this->m_data[3];
    }
    /**
     * @brief operator() is synonymous to operator[](Index), with bounds
     * checking. If pos is not within the range of the container, an
     * exception of type std::out_of_range is thrown.
     * @return the coefficient at given index.
     */
    reference operator()(size_type index) {
        assert(index >= 0 && index < rows * columns);
        return this->coeffRef(index);
    }
    /**
     * @return the coefficient at given the given row and column, with
     * bounds checking. If pos is not within the range of the container,
     * an exception of type std::out_of_range is thrown.
     */
    reference operator()(size_type row, size_type column) {
        assert(row    >= 0 && row    < this->rowsCount() &&
               column >= 0 && column < this->columnsCount());
        return this->coeffRef(row, column);

    }
    /**
     * @brief operator() is synonymous to operator[](Index) const, with
     * bounds checking. If pos is not within the range of the container,
     * an exception of type std::out_of_range is thrown.
     * @return the coefficient at given index.
     */
    value_type operator()(size_type index) const {
        assert(index >= 0 && index < this->size());
        return this->coeff(index);
    }
    /**
     * @return the coefficient at given the given row and column, with
     * bounds checking. If pos is not within the range of the container,
     * an exception of type std::out_of_range is thrown.
     * @see Matrix::operator()(size_type, size_type), Matrix::operator[](size_type).
     */
    value_type operator()(size_type row, size_type column) const {
        assert(row    >= 0 && row    < this->rowsCount() &&
               column >= 0 && column < this->columnsCount());
        return this->coeff(row, column);
    }
    /**
     * @return a reference to the coefficient at given index.
     * No bounds checking is performed.
     */
    reference operator[](size_type index) {
        assert(index < this->size());
        return this->m_data[index];
    }
    /**
     * @return the coefficient at given index.
     * No bounds checking is performed.
     */
    value_type operator[](size_type index) const {
        assert(index >= 0 && index < this->size());
        return this->m_data[index];
    }
    /**
     * @return a pointer to the data array of this matrix.
     */
    pointer data() {
        return this->m_data.data();
    }
    /**
     * @return a const pointer to the data array of this matrix.
     */
    const_pointer data() const {
        return this->m_data.data();
    }
    /**
     * @brief begin is only for vectors (either row-vectors or column-vectors).
     * @return an iterator to the first element of the 1D vector or array,
     * i.e. matrices which are known at compile-time to have either one row
     * or one column.
     */
    iterator begin(){
        return iterator(this->data());
    }
    /**
     * @brief begin is const version of begin().
     */
    const_iterator begin() const {
        return const_iterator(this->data());
    }
    /**
     * @brief cbegin is only for vectors (either row-vectors or column-vectors),
     * i.e. matrices which are known at compile-time to have either one row or
     * one column.
     * @return a read-only const_iterator to the first element of the 1D vector or array
     */
    const_iterator cbegin() const {
        return const_iterator(this->data());
    }
    /**
     * @brief end is only for vectors (either row-vectors or column-vectors),
     * i.e. matrices which are known at compile-time to have either one row
     * or one column.
     * @return an iterator to the element following the last element of
     * the 1D vector or array.
     */
    iterator end() {
        return iterator(this->data() + this->size());
    }
    /**
     * @brief end const version of end()
     */
    const_iterator end() const {
        return const_iterator(this->data() + this->size());
    }
    /**
     * @brief cend is only for vectors (either row-vectors or column-vectors),
     * i.e. matrices which are known at compile-time to have either one row or
     * one column.
     * @return a read-only const_iterator to the element following the last
     * element of the 1D vector or array.
     */
    const_iterator cend() const {
        return const_iterator(this->data() + this->size());
    }

public:
    // Matrix arithmetics
    /**
     * @brief operator+= replaces *this by *this + other.
     * @return a reference to *this
     */
    Matrix& operator+=(const Matrix& mat)
    {
        for (size_t i = 0; i < rows * columns; i++)
            this->coeffRef(i) += mat[i];
        return (*this);
    }
    /**
     * @return a matrix in which each element compute like *this[i] + mat[i].
     */
    Matrix operator+(const Matrix& mat) const
    {
        Matrix res = (*this);
        res += mat;
        return res;
    }
    /**
     * @brief operator-= replaces *this by *this - other.
     * @return a reference to *this
     */
    Matrix operator-=(const Matrix& mat)
    {
        for (size_t i = 0; i < rows * columns; i++)
            this->coeffRef(i) -= mat[i];
        return (*this);
    }
    /**
     * @return a matrix in which each element compute like *this[i] - mat[i].
     */
    Matrix operator-(const Matrix& mat) const
    {
        Matrix res = (*this);
        res -= mat;
        return res;
    }

    // Numeric arithmetics
    /**
     * @brief operator*= replaces *this by *this * num.
     */
    void operator*=(const double& num)
    {
        for (size_t i = 0; i < rows * columns; i++)
            this->coeffRef(i) *= num;
    }
    /**
     * @return a matrix in which each element compute like *this[i] * num.
     */
    Matrix operator*(const double& num) const
    {
        Matrix res = (*this);
        res *= num;
        return res;
    }
    /**
     * @brief operator /= replaces *this by *this / num.
     */
    void operator/=(const double& num)
    {
        for (size_t i = 0; i < rows * columns; i++)
            this->coeffRef(i) /= num;
    }
    /**
     * @return a matrix in which each element compute like *this[i] / num.
     */
    Matrix operator/(const double& num) const
    {
        Matrix res = (*this);
        res /= num;
        return res;
    }

public:
    /**
     * @brief fill sets all coefficients in this expression to value val.
     */
    void fill(const_reference value) {
        std::fill(this->m_data.begin(), this->m_data.end(), value);
    }
    /**
     * @return true if *this contains at least one Not A Number (NaN).
     */
    bool hasNAN() {
        const auto it = std::find_if(this->begin(), this->end(), [](const_reference value){
                                        return std::isnan(value);
                                     });
        return it == this->end() ? false : true;
    }
    /**
     * @return true if *this is approximately equal to the zero matrix,
     * within the precision given by ulp.
     */
    bool isZero(int ulp = 2) {
        const auto it = std::find_if_not(this->begin(), this->end(), [&](const_reference value){
                                         return (std::fabs(value - 0) <= std::numeric_limits<value_type>::epsilon() *
                                                                         std::fabs(value + 0) * ulp ||
                                                                         std::fabs(value - 0) < std::numeric_limits<value_type>::min());
                                         });
        return it == this->end() ? true : false;
    }
    /**
     * @return the maximum of all coefficients of *this.
     */
    value_type maxCoeff() const {
        return *std::max_element(this->begin(), this->end());
    }
    /**
     * @return the minimum of all coefficients of *this.
     */
    value_type minCoeff() const {
        return *std::min_element(this->begin(), this->end());
    }
    /**
     * @return an expression of the transpose of *this.
     */
    const Matrix getTransposed() const
    {
        Matrix<rows, columns, value_type> res;
        for (size_t i = 0; i < columns; i++)
            for (size_t j = 0; j < rows; j++)
                res(i,j) = (*this)(j,i);
        return res;
    }
    /**
     * @brief transpose is the "in place" version of getTransposed():
     * it replaces *this by its own transpose.
     */
    void transpose()
    {
        *this = getTransposed();
    }
    /**
     * @return the matrix inverse of this matrix.
     * @warning It is only for matrixes: 2x2, 3x3, 4x4.
     */
    const Matrix getInversed() const;
    /**
     * @brief inverse is the "in place" version of getInversed():
     * it replaces *this by its own inverse.
     * @warning It is only for matrixes: 2x2, 3x3, 4x4.
     */
    void inverse()
    {
        *this = getInversed();
    }
    /**
     * @return the determinant of this matrix.
     * @warning It is only for matrixes: 2x2, 3x3, 4x4.
     */
    double det() const;
    /**
     * @brief norm is the square root of the sum of the square of all the
     * matrix entries. For vectors, this is also equals to the square root
     * of the dot product of *this with itself.
     * @return the l2 norm of *this.
     * @warning It is for matrxies: 1x2, 1x3, 1x4, 2x1, 3x1, 4x1.
     */
    double norm() const {
        return std::sqrt(std::accumulate(this->begin(), this->end(), 0.0,
                                         [](double result, const_reference value) {
                                             return result += value * value;
                                         }));
    }
    /**
     * @return the trace of *this, i.e. the sum of the coefficients on the
     * main diagonal.
     * @note *this can be any matrix, not necessarily square.
     */
    double trace() const
    {
        double val = 0;
        for (size_t i = 0; i < (std::min)(rows, columns); i++)
            val += (*this)(i, i);
        return val;
    }
    /**
     * @brief replaceCol replaces the column of the matrix with the passed
     * matrix-column.
     * @param columnIndex is column index which will be replaced.
     * @param col is matrix-column on wich *this matrix column will be
     * replaced.
     */
    void replaceCol(size_t columnIndex, const Matrix<rows, 1, value_type>& col)
    {
        assert(columnIndex < columns);
        for (size_t i = 0; i < rows; i++)
            (*this)(i, columnIndex) = col(i);
    }
    /**
     * @brief replaceRow replaces the row of the matrix with the passed
     * matrix-row.
     * @param rowIndex is row index which will be replaced.
     * @param row is matrix-row on wich *this matrix row will be replaced.
     */
    void replaceRow(size_t rowIndex, const Matrix<1, columns, value_type>& row)
    {
        assert(rowIndex < rows);
        for (size_t i = 0; i < columns; i++)
            (*this)(rowIndex, i) = row(i);
    }
    /**
     * @return a row with index rowIndex.
     */
    Matrix<1, columns, value_type> getRow(size_t rowIndex) const
    {
        assert(rowIndex < rows);
        Matrix<1, columns, value_type> res;
        for (size_t i = 0; i < columns; i++)
            res(0, i) = (*this)(rowIndex, i);
        return res;
    }
    /**
     * @return a column with index columnIndex.
     */
    Matrix<rows, 1, value_type> getCol(size_t columnIndex) const
    {
        assert(columnIndex < columns);
        Matrix<rows, 1, value_type> res;
        for (size_t i = 0; i < rows; i++)
            res(i, 0) = (*this)(i, columnIndex);
        return res;
    }
    /**
     * @return sets matrix in which all coefficients are one.
     */
    static Matrix ones()
    {
        Matrix res;
        for (size_t i = 0; i < rows * columns; i++)
            res[i] = 1.0;
        return res;
    }
    /**
     * @return returns matrix in which all coefficients on main diagonal are
     * one.
     */
    static Matrix eye()
    {
        Matrix res;
        for (size_t i = 0; i < std::min(columns, rows); i++)
            res(i, i) = 1.0;
        return res;
    }

public:
    /**
     * @return the cross product of *this and other.
     * @warning defined for Matrix<3, 1, double> only.
     */
    Matrix cross(const Matrix &other) const;
    /**
     * @return the dot product of *this with other.
     * @note This is only for vectors (either row-vectors or column-vectors),
     * i.e. matrices which are known at compile-time to have either one row
     * or one column.
     */
    double dot(const Matrix &other) const;
    /**
     * @return module of the vector.
     * @note This is only for vectors (either row-vectors or column-vectors),
     * i.e. matrices which are known at compile-time to have either one
     * row or one column.
     */
    double mod() const {
        return std::sqrt(this->mod2());
    }
    /**
     * @return modulus square of the vector.
     * @note This is only for vectors (either row-vectors or column-vectors),
     * i.e. matrices which are known at compile-time to have either one
     * row or one column.
     */
    double mod2() const {
        return std::accumulate(this->begin(), this->end(), 0.0,
                               [](double result, const_reference value){
                                   return result += value * value;
                               });
    }
    /**
     * @return normalized vector, i.e. divides it by its own norm.
     * @note This is only for vectors (either row-vectors or column-vectors),
     * i.e. matrices which are known at compile-time to have either one
     * row or one column.
     */
    Matrix getNormalized() const {
        return *this / this->mod();
    }
    /**
     * @brief normalize normalizes the vector, i.e. divides it by its own norm.
     * @note This is only for vectors (either row-vectors or column-vectors),
     * i.e. matrices which are known at compile-time to have either one
     * row or one column.
     */
    void normalize() {
        *this = *this / this->mod();
    }

private:
    std::array<value_type, rows * columns> m_data;
};

template <>
const Matrix<2, 2, double> Matrix<2, 2, double>::getInversed() const;
template <>
const Matrix<3, 3, double> Matrix<3, 3, double>::getInversed() const;
template <>
const Matrix<4, 4, double> Matrix<4, 4, double>::getInversed() const;

template <>
double Matrix<2, 2, double>::det() const;
template <>
double Matrix<3, 3, double>::det() const;
template <>
double Matrix<4, 4, double>::det() const;

template<>
Matrix<3, 1, double> Matrix<3, 1, double>::cross(const Matrix<3, 1, double> &other) const;

template<>
Matrix<1, 3, double> Matrix<1, 3, double>::cross(const Matrix<1, 3, double> &other) const;

template<>
double Matrix<2, 1, double>::dot(const Matrix<2, 1, double> &other) const;

template<>
double Matrix<3, 1, double>::dot(const Matrix<3, 1, double> &other) const;

template<>
double Matrix<4, 1, double>::dot(const Matrix<4, 1, double> &other) const;

template<>
double Matrix<1, 2, double>::dot(const Matrix<1, 2, double> &other) const;

template<>
double Matrix<1, 3, double>::dot(const Matrix<1, 3, double> &other) const;

template<>
double Matrix<1, 4, double>::dot(const Matrix<1, 4, double> &other) const;

template<std::size_t rows1, std::size_t columns1_rows2,
         std::size_t columns2, typename Type>
const Matrix<rows1, columns2, Type> operator*(const Matrix<rows1, columns1_rows2, Type> &a,
                                              const Matrix<columns1_rows2, columns2, Type> &b) {
    Matrix<rows1, columns2, Type> res;
    for (size_t i = 0; i < rows1; i++)
        for (size_t j = 0; j < columns2; j++)
            for (size_t k = 0; k < columns1_rows2; k++)
                res(i,j) += a(i,k) * b(k,j);
    return res;
}

template <size_t rows, size_t columns, typename Type>
const Matrix<rows, columns, Type> operator*(const double& num, const Matrix<rows, columns, Type>& mat)
{
    return mat * num;
}

#define RFMATH_MAKE_TYPEDEFS(Type, TypeSuffix, Size, SizeSuffix) \
using Matrix##SizeSuffix##TypeSuffix = Matrix<Size, Size, Type>; \
using Vector##SizeSuffix##TypeSuffix = Matrix<Size, 1, Type>; \
using RowVector##SizeSuffix##TypeSuffix = Matrix<1, Size, Type>;

#define RFMATH_MAKE_TYPEDEFS_ALL_SIZES(Type, TypeSuffix) \
RFMATH_MAKE_TYPEDEFS(Type, TypeSuffix, 2, 2) \
RFMATH_MAKE_TYPEDEFS(Type, TypeSuffix, 3, 3) \
RFMATH_MAKE_TYPEDEFS(Type, TypeSuffix, 4, 4)

RFMATH_MAKE_TYPEDEFS_ALL_SIZES(int,    i)
RFMATH_MAKE_TYPEDEFS_ALL_SIZES(float,  f)
RFMATH_MAKE_TYPEDEFS_ALL_SIZES(double, d)

#undef RFMATH_MAKE_TYPEDEFS_ALL_SIZES
#undef RFMATH_MAKE_TYPEDEFS

#define RFMATH_MAKE_TYPEDEFS(Size, SizeSuffix)        \
template<typename Type>                              \
using Matrix##SizeSuffix = Matrix<Size, Size, Type>; \
template<typename Type>                              \
using Vector##SizeSuffix = Matrix<Size, 1, Type>;    \
template<typename Type>                              \
using RowVector##SizeSuffix = Matrix<1, Size, Type>;

RFMATH_MAKE_TYPEDEFS(2, 2)
RFMATH_MAKE_TYPEDEFS(3, 3)
RFMATH_MAKE_TYPEDEFS(4, 4)

template <typename Type, int Size>
using Vector = Matrix<Size, 1, Type>;

#undef RFMATH_MAKE_TYPEDEFS

#endif // MATRIX_H
