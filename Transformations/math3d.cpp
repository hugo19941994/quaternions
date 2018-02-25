#include <math.h>
#include "math3d.h"

VECTOR3D Add(VECTOR3D a, VECTOR3D b) //Ya implementado como ejemplo.
{
	VECTOR3D ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}

VECTOR3D Substract(VECTOR3D a, VECTOR3D b) {
	VECTOR3D ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}

VECTOR3D Multiply(VECTOR3D a, VECTOR3D b) {
	VECTOR3D ret;
	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return ret;
}

VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a) {
	VECTOR3D ret;
	ret.x = a.x * scalar;
	ret.y = a.y * scalar;
	ret.z = a.z * scalar;
	return ret;
}

double Magnitude(VECTOR3D a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

VECTOR3D Normalize(VECTOR3D a) {
	double length = Magnitude(a);
	VECTOR3D ret;
	ret.x = a.x / length;
	ret.y = a.y / length;
	ret.z = a.z / length;
	return ret;
}

VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b) {
	double uvi = a.y * b.z - b.y * a.z;
	double uvj = b.x * a.z - a.x * b.z;
	double uvk = a.x * b.y - b.x * a.y;
	VECTOR3D ret;
	ret.x = uvi;
	ret.y = uvj;
	ret.z = uvk;
	return ret;
}

double DotProduct(VECTOR3D a, VECTOR3D b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

MATRIX3 Transpose(MATRIX3 m) {
	MATRIX3 ret;
	ret.column0.x = m.column0.x;
	ret.column0.y = m.column1.x;
	ret.column0.z = m.column2.x;

	ret.column1.x = m.column0.y;
	ret.column1.y = m.column1.y;
	ret.column1.z = m.column2.y;

	ret.column2.x = m.column0.z;
	ret.column2.y = m.column1.z;
	ret.column2.z = m.column2.z;

	return ret;
}

VECTOR3D Transform(MATRIX3 m, VECTOR3D a) {
	MATRIX3 mt = Transpose(m);
	VECTOR3D ret;
	ret.x = DotProduct(mt.column0, a);
	ret.y = DotProduct(mt.column1, a);
	ret.z = DotProduct(mt.column2, a);
	return ret;
}

MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t) {
	MATRIX3 At = Transpose(A);
	MATRIX4 ret;
	ret.m[0] = At.column0.x;
	ret.m[1] = At.column0.y;
	ret.m[2] = At.column0.z;
	ret.m[3] = 0;

	ret.m[4] = At.column1.x;
	ret.m[5] = At.column1.y;
	ret.m[6] = At.column1.z;
	ret.m[7] = 0;

	ret.m[8] = At.column2.x;
	ret.m[9] = At.column2.y;
	ret.m[10] = At.column2.z;
	ret.m[11] = 0;

	ret.m[12] = -DotProduct(t, A.column0);
	ret.m[13] = -DotProduct(t, A.column1);
	ret.m[14] = -DotProduct(t, A.column2);
	ret.m[15] = 1;
	return ret;
}

QUATERNION QuaternionFromAngleAxis(float angle, VECTOR3D axis) {
	double s = sin((angle * DTOR) / 2);
	QUATERNION toRet;

	toRet.v.x = axis.x * s;
	toRet.v.y = axis.y * s;
	toRet.v.z = axis.z * s;

	double w = cos((angle * DTOR) / 2);
	toRet.s = w;

	return toRet;
}

QUATERNION QuaternionFromToVectors(VECTOR3D from, VECTOR3D to) {

	double cos = DotProduct(Normalize(from), Normalize(to));
	double angle = acos(cos);
	VECTOR3D axis = CrossProduct(Normalize(from), Normalize(to));
	return QuaternionFromAngleAxis(angle, axis);
}

QUATERNION Multiply(QUATERNION a, QUATERNION b) {
	QUATERNION q;
    q.v.x = a.v.x * b.s + a.v.y * b.v.z - a.v.z * b.v.y + a.s * b.v.x;
	q.v.y = -a.v.x * b.v.z + a.v.y * b.s + a.v.z * b.v.x + a.s * b.v.y;
	q.v.z = a.v.x * b.v.y - a.v.y * b.v.x + a.v.z * b.s + a.s * b.v.z;
	q.s = -a.v.x * b.v.x - a.v.y * b.v.y - a.v.z * b.v.z + a.s * b.s;
	return q;
}

QUATERNION Conjugate(QUATERNION a) {
	QUATERNION q;
	q.v.x = -a.v.x;
	q.v.y = -a.v.y;
	q.v.z = -a.v.z;
	q.s = a.s;
	return q;
}

VECTOR3D RotateWithQuaternion(VECTOR3D a, QUATERNION q) {
	VECTOR3D vector;
	float num12 = q.v.x + q.v.x;
	float num2 = q.v.y + q.v.y;
	float num = q.v.z + q.v.z;
	float num11 = q.s * num12;
	float num10 = q.s * num2;
	float num9 = q.s * num;
	float num8 = q.v.x * num12;
	float num7 = q.v.x * num2;
	float num6 = q.v.x * num;
	float num5 = q.v.y * num2;
	float num4 = q.v.y * num;
	float num3 = q.v.z * num;
	float num15 = ((a.x * ((1.0f - num5) - num3)) + (a.y * (num7 - num9))) + (a.z * (num6 + num10));
	float num14 = ((a.x * (num7 + num9)) + (a.y * ((1.0f - num8) - num3))) + (a.z * (num4 - num11));
	float num13 = ((a.x * (num6 - num10)) + (a.y * (num4 + num11))) + (a.z * ((1.0f - num8) - num5));
	vector.x = num15;
	vector.y = num14;
	vector.z = num13;
	return vector;
}
