#pragma once

#include "Vector3.h"
#include <iostream>
#include <cmath>
#include <iomanip>

class Matrix
{
public:
	Matrix() { }
	Matrix(const Matrix &orig);

	void Invert();
	void Transpose();
	Matrix GetInverse() const;
	Matrix GetTranspose() const;

	Matrix& operator+=(const Matrix& rhs);
	Matrix& operator-=(const Matrix& rhs);
	Matrix& operator*=(const Matrix& rhs);
	Matrix& operator*=(float rhs);

	friend Matrix operator-(const Matrix &lhs, const Matrix &rhs);
	friend Matrix operator+(const Matrix &lhs, const Matrix &rhs);
	friend Matrix operator*(const Matrix &lhs, const Matrix &rhs);
	friend Vector3 operator*(const Matrix &lhs, const Vector3 &rhs);
	friend Matrix operator*(const Matrix &lhs, float rhs);
	friend Matrix operator*(float lhs, const Matrix &rhs);

	friend Vector3 TransformLoc(const Matrix &lhs, const Vector3 &rhs);
	friend Vector3 TransfromVec(const Matrix &lhs, const Vector3 &rhs);
	
	friend Matrix ZeroMatrix();
	friend Matrix IdentityMatrix();
	friend Matrix Translate(float x, float y, float z);
	friend Matrix Scale(float x, float y, float z);
	friend Matrix Rotate(const Vector3 &axis, float angle);
	friend Matrix RotateX(float angle);
	friend Matrix RotateY(float angle);
	friend Matrix RotateZ(float angle);
	friend Matrix ViewMatrix(const Vector3 &eye, const Vector3 &gaze, const Vector3 &up);
	friend std::ostream& operator<<(std::ostream &out, const Matrix &rhs);

	float Determinant();
public:
	float mMat[4][4];
};

inline float Det3(
	float a, float b, float c,
	float d, float e, float f,
	float g, float h, float i)
{
	return a*e*i + d*h*c + g*b*f - g*e*c - d*b*i - a*h*f;
}