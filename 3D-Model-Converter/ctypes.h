#ifndef CTYPES_H
#define CTYPES_H

typedef float Vec2[2];
typedef float Vec3[3];
typedef float Quat[4];
typedef struct {
	float a1, a2, a3, a4;
	float b1, b2, b3, b4;
	float c1, c2, c3, c4;
	float d1, d2, d3, d4;
} Mat4x4;

#endif