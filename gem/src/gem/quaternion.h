//
// Created by simon on 12/04/2020.
//

#ifndef UNTITLED_QUATERNION_H
#define UNTITLED_QUATERNION_H

#include "vector4.h"

namespace gem {
class quaternion : public vector4<float> {
public:
    quaternion(): vector4<float>() {}

    quaternion(const float& x, const float& y, const float& z, const float& w): vector4(x, y, z, w) {}

    friend std::ostream& operator <<(std::ostream& os, const quaternion& q) {
        os << "{ x: " << q.x << "f, y: " << q.y << "f, z: " << q.z << "f, w: " << q.w << "f }";
        return os;
    }

    quaternion operator *(const quaternion& q) const {
        auto x_ = (x * q.w) + (w * q.x) + (y * q.z) - (z * q.y);
        auto y_ = (y * q.w) + (w * q.y) + (z * q.x) - (x * q.z);
        auto z_ = (z * q.w) + (w * q.z) + (x * q.y) - (y * q.x);
        auto w_ = (w * q.w) - (x * q.x) - (y * q.y) - (z * q.z);
        return quaternion(x_, y_, z_, w_);
    }

    void operator *=(const quaternion& q) {
        *this = *this * q;
    }
};
}

#endif //UNTITLED_QUATERNION_H
