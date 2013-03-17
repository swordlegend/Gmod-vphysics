#ifndef MATH_H
#define MATH_H

#define SAFE_DIVIDE(a, b) ((b) != 0 ? (a)/(b) : 0)

void BtMatrix_vimult(const btMatrix3x3 &matrix, const btVector3 &in, btVector3 &out);
float AngDragIntegral(float invInertia, float l, float w, float h);

#endif