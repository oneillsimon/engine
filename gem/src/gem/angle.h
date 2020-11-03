//
// Created by simon on 10/04/2020.
//

#include "constants.h"

#ifndef UNTITLED_ANGLE_H
#define UNTITLED_ANGLE_H

namespace gem {
class angle {
public:
    double radians;
    double degrees;

    explicit angle(double radians) : radians(radians), degrees(radians * (180 / static_cast<double>(PI))) { }

    static angle from_radians(double radians) {
        return angle(radians);
    }

    static angle from_degrees(double degrees) {
        return angle(degrees * (static_cast<double>(gem::PI) / 180.0));
    }
};
}

#endif //UNTITLED_ANGLE_H
