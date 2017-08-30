#include "Matrix.h"

Matrix::Matrix(const Matrix &rhs)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mMat[i][j] = rhs.mMat[i][j];
}

Matrix& Matrix::operator+=(const Matrix &rhs)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mMat[i][j] += rhs.mMat[i][j];
	return *this;
}

Matrix& Matrix::operator-=(const Matrix &rhs)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mMat[i][j] -= rhs.mMat[i][j];
	return *this;
}

Matrix& Matrix::operator*=(float rhs)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			mMat[i][j] *= rhs;
	return *this;
}

Matrix& Matrix::operator*=(const Matrix &rhs)
{
	Matrix temp = *this;
	for(int i = 0; i<4; i++)
		for (int j = 0; j < 4; j++)
		{
			float sum = 0;
			for (int k = 0; k < 4; k++)
				sum += temp.mMat[i][k] * rhs.mMat[k][j];
			mMat[i][j] = sum;
		}
	return *this;
}

void Matrix::Invert()
{
	float det = Determinant();
	Matrix inverse;

	{
		inverse.mMat[0][0] = Det3(
			mMat[1][1], mMat[1][2], mMat[1][3],
			mMat[2][1], mMat[2][2], mMat[2][3],
			mMat[3][1], mMat[3][2], mMat[3][3]) / det;

		inverse.mMat[0][1] = -Det3(
			mMat[0][1], mMat[0][2], mMat[0][3],
			mMat[2][1], mMat[2][2], mMat[2][3],
			mMat[3][1], mMat[3][2], mMat[3][3]) / det;

		inverse.mMat[0][2] = Det3(
			mMat[0][1], mMat[0][2], mMat[0][3],
			mMat[1][1], mMat[1][2], mMat[1][3],
			mMat[3][1], mMat[3][2], mMat[3][3]) / det;

		inverse.mMat[0][3] = -Det3(
			mMat[0][1], mMat[0][2], mMat[0][3],
			mMat[1][1], mMat[1][2], mMat[1][3],
			mMat[2][1], mMat[2][2], mMat[2][3]) / det;
	}
	{
		inverse.mMat[1][0] = -Det3(
			mMat[1][0], mMat[1][2], mMat[1][3],
			mMat[2][0], mMat[2][2], mMat[2][3],
			mMat[3][0], mMat[3][2], mMat[3][3]) / det;

		inverse.mMat[1][1] = Det3(
			mMat[0][0], mMat[0][2], mMat[0][3],
			mMat[2][0], mMat[2][2], mMat[2][3],
			mMat[3][0], mMat[3][2], mMat[3][3]) / det;

		inverse.mMat[1][2] = -Det3(
			mMat[0][0], mMat[0][2], mMat[0][3],
			mMat[1][0], mMat[1][2], mMat[1][3],
			mMat[3][0], mMat[3][2], mMat[3][3]) / det;

		inverse.mMat[1][3] = Det3(
			mMat[0][0], mMat[0][2], mMat[0][3],
			mMat[1][0], mMat[1][2], mMat[1][3],
			mMat[2][0], mMat[2][2], mMat[2][3]) / det;
	}
	{
		inverse.mMat[2][0] = Det3(
			mMat[1][0], mMat[1][1], mMat[1][3],
			mMat[2][0], mMat[2][1], mMat[2][3],
			mMat[3][0], mMat[3][1], mMat[3][3]) / det;

		inverse.mMat[2][1] = -Det3(
			mMat[0][0], mMat[0][1], mMat[0][3],
			mMat[2][0], mMat[2][1], mMat[2][3],
			mMat[3][0], mMat[3][1], mMat[3][3]) / det;

		inverse.mMat[2][2] = Det3(
			mMat[0][0], mMat[0][1], mMat[0][3],
			mMat[1][0], mMat[1][1], mMat[1][3],
			mMat[3][0], mMat[3][1], mMat[3][3]) / det;

		inverse.mMat[2][3] = -Det3(
			mMat[0][0], mMat[0][1], mMat[0][3],
			mMat[1][0], mMat[1][1], mMat[1][3],
			mMat[2][0], mMat[2][1], mMat[2][3]) / det;
	}
	{
		inverse.mMat[3][0] = -Det3(
			mMat[1][0], mMat[1][1], mMat[1][2],
			mMat[2][0], mMat[2][1], mMat[2][2],
			mMat[3][0], mMat[3][1], mMat[3][2]) / det;

		inverse.mMat[3][1] = Det3(
			mMat[0][0], mMat[0][1], mMat[0][2],
			mMat[2][0], mMat[2][1], mMat[2][2],
			mMat[3][0], mMat[3][1], mMat[3][2]) / det;

		inverse.mMat[3][2] = -Det3(
			mMat[0][0], mMat[0][1], mMat[0][2],
			mMat[1][0], mMat[1][1], mMat[1][2],
			mMat[3][0], mMat[3][1], mMat[3][2]) / det;

		inverse.mMat[3][3] = Det3(
			mMat[0][0], mMat[0][1], mMat[0][2],
			mMat[1][0], mMat[1][1], mMat[1][2],
			mMat[2][0], mMat[2][1], mMat[2][2]) / det;
	}

	*this = inverse;
}

Matrix Matrix::GetInverse() const
{
	Matrix ret = *this;
	ret.Invert();
	return ret;
}

void Matrix::Transpose()
{
	float temp;
	for(int i = 0; i<4; i++)
		for (int j = 0; j < 4; j++)
		{
			temp = mMat[i][j];
			mMat[i][j] = mMat[j][i];
			mMat[j][i] = temp;
		}
}

Matrix Matrix::GetTranspose() const
{
	Matrix ret = *this;
	ret.Transpose();

	return ret;
}

Vector3 TransformLoc(const Matrix &lhs, const Vector3 &rhs)
{
	return lhs * rhs;
}

Vector3 TransformVec(const Matrix &lhs, const Vector3 &rhs)
{
	Vector3 ret;

	ret[0] = rhs[0] * lhs.mMat[0][0] + rhs[1] * lhs.mMat[0][1] + rhs[2] * lhs.mMat[0][2];
	ret[1] = rhs[0] * lhs.mMat[1][0] + rhs[1] * lhs.mMat[1][1] + rhs[2] * lhs.mMat[1][2];
	ret[2] = rhs[0] * lhs.mMat[2][0] + rhs[1] * lhs.mMat[2][1] + rhs[2] * lhs.mMat[2][2];

	return ret;
}

Matrix ZeroMatrix()
{
	Matrix ret;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ret.mMat[i][j] = 0.f;

	return ret;
}

Matrix IdentityMatrix()
{
	Matrix ret;
	ret.mMat[0][0] = 1.f;
	ret.mMat[0][1] = 0.f;
	ret.mMat[0][2] = 0.f;
	ret.mMat[0][3] = 0.f;

	ret.mMat[1][0] = 0.f;
	ret.mMat[1][1] = 1.f;
	ret.mMat[1][2] = 0.f;
	ret.mMat[1][3] = 0.f;

	ret.mMat[2][0] = 0.f;
	ret.mMat[2][1] = 0.f;
	ret.mMat[2][2] = 1.f;
	ret.mMat[2][3] = 0.f;

	ret.mMat[3][0] = 0.f;
	ret.mMat[3][1] = 0.f;
	ret.mMat[3][2] = 0.f;
	ret.mMat[3][3] = 1.f;

	return ret;
}

Matrix Translate(float x, float y, float z)
{
	Matrix ret = IdentityMatrix();

	ret.mMat[0][3] = x;
	ret.mMat[1][3] = y;
	ret.mMat[2][3] = z;

	return ret;
}

Matrix Scale(float x, float y, float z)
{
	Matrix ret = IdentityMatrix();

	ret.mMat[0][0] = x;
	ret.mMat[1][1] = y;
	ret.mMat[2][2] = z;

	return ret;
}

Matrix RotateX(float angle)
{
	Matrix ret = IdentityMatrix();

	float cosine = cos(angle);
	float sine = sin(angle);

	ret.mMat[1][1] = cosine;
	ret.mMat[1][2] = -sine;
	ret.mMat[2][1] = sine;
	ret.mMat[2][2] = cosine;

	return ret;
}

Matrix RotateY(float angle)
{
	Matrix ret = IdentityMatrix();

	float cosine = cos(angle);
	float sine = sin(angle);

	ret.mMat[0][0] = cosine;
	ret.mMat[0][2] = sine;
	ret.mMat[2][0] = -sine;
	ret.mMat[2][2] = cosine;

	return ret;
}

Matrix RotateZ(float angle)
{
	Matrix ret = IdentityMatrix();

	float cosine = cos(angle);
	float sine = sin(angle);

	ret.mMat[0][0] = cosine;
	ret.mMat[0][1] = -sine;
	ret.mMat[1][0] = sine;
	ret.mMat[1][1] = cosine;

	return ret;
}

Matrix Rotate(const Vector3 &axis, float angle)
{
	Vector3 unitAxis = UnitVector(axis);
	Matrix ret;

	float x = unitAxis.x;
	float y = unitAxis.y;
	float z = unitAxis.z;
	float cosine = cos(angle);
	float sine = sin(angle);
	float t = 1 - cosine;

	ret.mMat[0][0] = t*x*x + cosine;
	ret.mMat[0][1] = t*x*y - sine*y;
	ret.mMat[0][2] = t*x*z + sine*y;
	ret.mMat[0][3] = 0.f;

	ret.mMat[1][0] = t*x*y + sine*z;
	ret.mMat[1][1] = t*y*y + cosine;
	ret.mMat[1][2] = t*y*z - sine*x;
	ret.mMat[1][3] = 0.f;

	ret.mMat[2][0] = t*x*z - sine*y;
	ret.mMat[2][1] = t*y*z + sine*x;
	ret.mMat[2][2] = t*z*z + cosine;
	ret.mMat[2][3] = 0.f;

	ret.mMat[3][0] = 0.f;
	ret.mMat[3][1] = 0.f;
	ret.mMat[3][2] = 0.f;
	ret.mMat[3][3] = 1.f;

	return ret;
}

Matrix ViewMatrix(const Vector3 &eye, const Vector3 &gaze, const Vector3 &up)
{
	Matrix ret = IdentityMatrix();

	Vector3 w = -(UnitVector(gaze));
	Vector3 u = UnitVector(Cross(up, w));
	Vector3 v = Cross(w, u);

	ret.mMat[0][0] = u.x;
	ret.mMat[0][1] = u.y;
	ret.mMat[0][2] = u.z;
	ret.mMat[1][0] = v.x;
	ret.mMat[1][1] = v.y;
	ret.mMat[1][2] = v.z;
	ret.mMat[2][0] = w.x;
	ret.mMat[2][1] = w.y;
	ret.mMat[2][2] = w.z;

	Matrix move = IdentityMatrix();
	move.mMat[0][3] = -(eye.x);
	move.mMat[1][3] = -(eye.y);
	move.mMat[2][3] = -(eye.z);

	ret *= move;

	return ret;
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs)
{
	Matrix ret;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ret.mMat[i][j] = lhs.mMat[i][j] - rhs.mMat[i][j];

	return ret;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{
	Matrix ret;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ret.mMat[i][j] = lhs.mMat[i][j] + rhs.mMat[i][j];

	return ret;
}

Matrix operator*(const Matrix &lhs, float rhs)
{
	Matrix ret;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ret.mMat[i][j] = lhs.mMat[i][j] * rhs;

	return ret;
}

Matrix operator*(float lhs, const Matrix &rhs)
{
	Matrix ret;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			ret.mMat[i][j] = rhs.mMat[i][j] * lhs;

	return ret;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{
	Matrix ret;
	for(int i = 0; i<4; i++)
		for (int j = 0; j < 4; j++)
		{
			float subt = 0.f;
			for (int k = 0; k < 4; k++)
				subt += lhs.mMat[i][k] * rhs.mMat[k][j];
			ret.mMat[i][j] = subt;
		}

	return ret;
}

Vector3 operator*(const Matrix &lhs, const Vector3 &rhs)
{
	Vector3 ret;
	float temp;

	ret[0] = rhs[0] * lhs.mMat[0][0] + rhs[1] * lhs.mMat[0][1] + rhs[2] * lhs.mMat[0][2] + lhs.mMat[0][3];
	ret[1] = rhs[0] * lhs.mMat[1][0] + rhs[1] * lhs.mMat[1][1] + rhs[2] * lhs.mMat[1][2] + lhs.mMat[1][3];
	ret[2] = rhs[0] * lhs.mMat[2][0] + rhs[1] * lhs.mMat[2][1] + rhs[2] * lhs.mMat[2][2] + lhs.mMat[2][3];
	temp = rhs[0] * lhs.mMat[3][0] + rhs[1] * lhs.mMat[3][1] + rhs[2] * lhs.mMat[3][2] + lhs.mMat[3][3];

	ret /= temp;
	return ret;
}

std::ostream& operator<<(std::ostream &out, const Matrix &rhs)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			out << std::setprecision(3) << std::setw(10) << rhs.mMat[i][j];
		out << std::endl;
	}
	return out;
}

float Matrix::Determinant()
{
	float det;
	det = mMat[0][0] * Det3(
		mMat[1][1], mMat[1][2], mMat[1][3],
		mMat[2][1], mMat[2][2], mMat[2][3],
		mMat[3][1], mMat[3][2], mMat[3][3]);

	det -= mMat[0][1] * Det3(
		mMat[1][0], mMat[1][2], mMat[1][3],
		mMat[2][0], mMat[2][2], mMat[2][3],
		mMat[3][0], mMat[3][2], mMat[3][3]);

	det += mMat[0][2] * Det3(
		mMat[1][0], mMat[1][1], mMat[1][3],
		mMat[2][0], mMat[2][1], mMat[2][3],
		mMat[3][0], mMat[3][1], mMat[3][3]);

	det -= mMat[0][3] * Det3(
		mMat[1][0], mMat[1][1], mMat[1][2],
		mMat[2][0], mMat[2][1], mMat[2][2],
		mMat[3][0], mMat[3][1], mMat[3][2]);

	return det;
}

