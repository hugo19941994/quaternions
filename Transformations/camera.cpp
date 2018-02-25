#include "camera.h"
#include <math.h>
#include <iostream>

// TODO
// devuelve los valores de distancia de los planos a partir del fov horizontal
FRUSTUM makeFrustum(double fovX, double aspectRatio, double nearValue, double farValue)
{
	const double DEG2RAD = 3.14159265 / 180;

	double tangent = tan(fovX / 2 * DEG2RAD);   // tangent of half fovY
	double height = nearValue * tangent;          // half height of near plane
	double width = height * aspectRatio;      // half width of near plane

	FRUSTUM ret;
	ret.farValue = farValue;
	ret.nearValue = nearValue;
	ret.left = -width;
	ret.right = width;
	ret.bottom = -height;
	ret.top = height;
	// TODO : rellenar valores de ret
	return ret;
}

MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector) {
	// Inverse z (normally target - eyePosition)
	VECTOR3D forward = Normalize(Substract(eyePosition, target));
	VECTOR3D side = Normalize(CrossProduct(upVector, forward));
	VECTOR3D up = Normalize(CrossProduct(forward, side));

	MATRIX3 r{ side, up, forward };

	return InverseOrthogonalMatrix(r, eyePosition);
}

void updateEulerOrientation(EULER& euler) {
	QUATERNION y = QuaternionFromAngleAxis(euler.yaw, VECTOR3D{ 1, 0, 0 });
	QUATERNION p = QuaternionFromAngleAxis(euler.pitch, VECTOR3D{ 0, 1, 0 });
	QUATERNION r = QuaternionFromAngleAxis(euler.roll, VECTOR3D{ 0, 0, 1 });

	euler.orientation = Multiply(Multiply(y, p), r);
}

VECTOR3D getForward(EULER euler) {
	return RotateWithQuaternion({ 0, 0, -1 }, euler.orientation);
}


