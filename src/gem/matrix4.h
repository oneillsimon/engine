//
// Created by simon on 09/05/2020.
//

#ifndef UNTITLED_MATRIX4_H
#define UNTITLED_MATRIX4_H

#include "angle.h"
#include "matrix.h"
#include "vector3.h"
#include "vector4.h"

namespace gem {
template <typename T>
class matrix4 : public matrix<T, 4, 4> {
public:
    using matrix<T, 4, 4>::matrix;

    static matrix4<T> translate(const T& x, const T& y, const T& z) {
        return matrix4<T> { { 1, 0, 0, x }, { 0, 1, 0, y }, { 0, 0, 1, z }, { 0, 0, 0, 1 } };
    }

    static matrix4<T> translate(const vector3<T>& v) {
        return matrix4<T>::translate(v.x, v.y, v.z);
    }

    static matrix4<T> rotate(const angle& angle, const T& x, const T& y, const T& z) {
        const T x2 = x * x;
        const T y2 = y * y;
        const T z2 = z * z;

        const auto radians = angle.radians();
        const auto cosine = std::cos(radians);
        const auto sine = std::sin(radians);

        return matrix4<T> {
                 { x2 * (1 - cosine) + cosine, x * y * (1 - cosine) - z * sine, x * z * (1 - cosine) + y * sine, 0 },
                 { y * x * (1 - cosine) + z * sine, y2 * (1 - cosine) + cosine, y * z * (1 - cosine) - x * sine, 0 },
                 { x * z * (1 - cosine) - y * sine, y * z * (1 - cosine) + x * sine, z2 * (1 - cosine) + cosine, 0 },
                 { 0, 0, 0, 1 }
        };
    }

    static matrix4<T> rotate(const angle& angle, const vector3<T>& axis) {
        return matrix4<T>::rotate(angle, axis.x, axis.y, axis.z);
    }

    static matrix4<T> scale(const T& x, const T& y, const T& z) {
        return matrix4<T> { { x, 0, 0, 0 }, { 0, y, 0, 0 }, { 0, 0, z, 0 }, { 0, 0, 0, 1 } };
    }

    static matrix4<T> scale(const T& scalar) {
        return matrix4<T>::scale(scalar, scalar, scalar);
    }

    static matrix4<T> scale(const vector3<T>& v) {
        return matrix4<T>::scale(v.x, v.y, v.z);
    }

    static matrix4<T> look_at(const vector3<T>& eye, const vector3<T>& position, const vector3<T>& up) {
        auto forward = (position - eye).normalise();
        auto side = forward.cross(up);
        auto ortho_up = side.cross(forward);
        return { { side.x, ortho_up.x, forward.x, -eye.x }, { side.y, ortho_up.y, forward.y, -eye.y },
                 { side.z, ortho_up.z, forward.z, -eye.z }, { 0, 0, 0, 1 } };
    }

    static matrix4<T> frustum(
            const float& left, const float& right, const float& top, const float& bottom, const float& near,
            const float& far
    ) {
        if (left == right || top == bottom || near == far || near < 0.0f || far < 0.0f) {
            return matrix4<T>::identity();
        }

        return { { (2 * near) / (right - left), 0, (right + left) / (right - left), 0 },
                 { 0, (2 * near) / (top - bottom), (top + bottom) / (top - bottom), 0 },
                 { 0, 0, (near + far) / (near - far), (2 * near * far) / (near - far) }, { 0, 0, -1, 0 } };
    }

    static matrix4<T> perspective(
            const angle& fov, const float& aspect_ratio, const float& z_near, const float& z_far
    ) {
        auto y_scale = static_cast<float>(1.0 / tan(fov.radians() / 2));
        auto x_scale = y_scale / aspect_ratio;
        auto z_range = z_near - z_far;

        return { { x_scale, 0, 0, 0 }, { 0, y_scale, 0, 0 }, { 0, 0, (z_far + z_near) / z_range, -1 },
                 { 0, 0, (2 * z_far * z_near) / z_range, 0 } };
    }

    static matrix4<T> orthographic(
            const float& left, const float& right, const float& top, const float& bottom, const float& near,
            const float& far
    ) {
        return { { 2 / (right - left), 0, 0, (left + right) / (left - right) },
                 { 0, 2 / (top - bottom), 0, (bottom + top) / (bottom - top) },
                 { 0, 0, 2 / (near - far), (near + far) / (far - near) }, { 0, 0, 0, 1 } };
    }
};
}

#endif //UNTITLED_MATRIX4_H
