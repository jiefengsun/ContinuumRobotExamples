#ifndef COMMONMATH_H
#define COMMONMATH_H

#include "eigenmatrixtypes.h"

namespace ContinuumRobotLibrary{

const double pi = 3.1415926535897932384626433832795028841971L;

/*! Maps a vector in R3 to a 3x3 skew-symettric matrix in se3. */
inline Matrix3d hat(Vector3d y){
    Matrix3d y_hat;
    y_hat <<    0, -y(2),  y(1),
             y(2),     0, -y(0),
            -y(1),  y(0),     0;

    return y_hat;
}

/*! Maps a matrix in se3 to a vector in R3. The input should be skew-symmetric but is not validated. */
inline Vector3d inv_hat(Matrix3d y_hat){
    Vector3d y;
    y << y_hat(2,1), y_hat(0,2), y_hat(1,0);

    return y;
}

/*! Calculates the logarithm of a 3x3 matrix */
inline Matrix3d log(Matrix3d R){
    double theta = acos((R.trace() - 1)/2);

    if(theta==0) return Matrix3d::Identity();
    else return (theta/(2*sin(theta)))*(R.transpose() - R);
}

/*! Quantify the difference between two rotation matrices as a 3x1 vector. */
inline Vector3d rotation_error(Matrix3d R1, Matrix3d R2){
    return inv_hat( log( R1.transpose()*R2 ) );
}

/*! A linearized metric for distance between two rotation matrices.
 *  Warning: there can be zeroes corresponding to 180 degree rotations. */
inline Vector3d linear_rotation_error(Matrix3d R1, Matrix3d R2){
    return inv_hat(R1.transpose()*R2 - R1*R2.transpose());
}

}

#endif // COMMONMATH_H