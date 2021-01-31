#include "Vector3.h"

Vector3::Vector3() : Matrix(1, 3)
{
}

Vector3::Vector3(double x, double y, double z) : Matrix(1, 3)
{
    setX(x);
    setY(y);
    setZ(z);
}

Vector3::Vector3(const Vector3& vector) : Matrix(1, 3)
{
    Matrix::fill(vector);
}

Vector3::Vector3(const Matrix& matrix) : Matrix(matrix)
{
    if (matrix.getRowCount() == 3 && matrix.getColumnCount() == 1)
    {
        allocate(1, 3);
        Matrix::fill(Matrix::transposed(matrix));
    }
    else if (matrix.getRowCount() != 1 || matrix.getColumnCount() != 3)
        throw Exception::Matrix::NotVector3("Can't initialize a Vector3 with this size (!= (1,3)).");
}

Vector3::Vector3(const Matrix&& matrix) : Matrix(matrix)
{
    if (matrix.getRowCount() == 3 || matrix.getColumnCount() == 1)
    {
        allocate(1, 3);
        Matrix::fill(Matrix::transposed(matrix));
    }
    else if (matrix.getRowCount() != 1 || matrix.getColumnCount() != 3)
        throw Exception::Matrix::NotVector3("Can't initialize a Vector3 with this size (!= (1,3)).");
}

Vector3::Vector3(const std::initializer_list<double>& initializerList) : Matrix(1, 3)
{
    fill(initializerList);
}

double Vector3::x() const
{
    return value(0, 0);
}

double Vector3::y() const
{
    return value(0, 1);
}

double Vector3::z() const
{
    return value(0, 2);
}

void Vector3::setX(double value)
{
    setValue(0, 0, value);
}

void Vector3::setY(double value)
{
    setValue(0, 1, value);
}

void Vector3::setZ(double value)
{
    setValue(0, 2, value);
}

Vector3& Vector3::operator=(const Matrix& matrix)
{
    if (!isVector3(matrix))
        throw Exception::Matrix::NotVector3("The matrix can't be cast to a Vector3.");

    allocate(1, 3);
    Matrix::fill(matrix);

    return *this;
}

Vector3& Vector3::operator=(const Vector3& vector)
{
    if (this == &vector)
        return *this;

    allocate(1, 3);

    setX(vector.x());
    setY(vector.y());
    setZ(vector.z());

    return *this;
}

void Vector3::fill(const std::initializer_list<double>& initializerList)
{
    std::size_t column = 0;
    for (const auto& value : initializerList)
    {
        if (column >= 3)
            throw Exception::Vector3::WrongInitializerList();

        setValue(0, column, value);
        column++;
    }
}

bool isVector3(const Matrix& matrix)
{
    return (matrix.getRowCount() == 1 && matrix.getColumnCount() == 3);
}