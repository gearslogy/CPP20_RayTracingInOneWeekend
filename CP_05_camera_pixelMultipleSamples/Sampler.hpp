//
// Created by star on 2/15/2022.
//

#ifndef ONE_WEEKEND_SAMPLER_HPP
#define ONE_WEEKEND_SAMPLER_HPP

#include "Kernel.hpp"
#include "Utils.hpp"

Vec3 random_in_unit_disk() {
    while (true) {
        auto p = Vec3(random_double(-1,1), random_double(-1,1), 0);
        if (length_squared(p) >= 1) continue;
        return p;
    }
}





#endif //ONE_WEEKEND_SAMPLER_HPP
