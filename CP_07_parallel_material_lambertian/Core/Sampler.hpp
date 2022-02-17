//
// Created by star on 2/15/2022.
//

#ifndef ONE_WEEKEND_SAMPLER_HPP
#define ONE_WEEKEND_SAMPLER_HPP

#include "Kernel.hpp"
#include "Utils.hpp"


class QubeScatter{
public:
    // random points in [-1 , 1] qube
    static inline auto interior(){
        Vec3 ret{random_double(-1,1), random_double(-1,1), random_double(-1,1)};
        return ret;
    };
};

class DiskScatter{
public:
    // reject method. get sample point on disk
    static inline auto surface() {
        while (true) {
            auto p = Vec3(random_double(-1,1), random_double(-1,1), 0);
            if (length_squared(p) >= 1) continue;
            return p;
        }
    }
};

class SphereScatter{
public:
    // sample point inside sphere, use reject method
    static inline auto interior(){
        while (true) {
            auto p = QubeScatter::interior();
            if (length_squared(p)>= 1) continue;
            return p;
        }
    }
    // sample point on unit sphere surface
    static inline Vec3 surface() {
        return normalize(interior());  // 只要把原来的球内改成normalize就可以了
    }
};

class HemisphereScatter{
public:
    // sample point in unit hemisphere
    static inline auto interior(const Vec3& normal) {
        Vec3 in_unit_sphere = SphereScatter::interior();
        if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
            return in_unit_sphere;
        else
            return -in_unit_sphere;
    }
    // sample point on unit hemisphere surface
    static inline auto surface(const Vec3& normal){
        return normalize(interior(normal));
    }

};

inline auto random_in_unit_sphere() {
    while (true) {
        auto p = Vec3(random_double(-1,1), random_double(-1,1), random_double(-1,1));
        if (length_squared(p)>= 1) continue;
        return p;
    }
}

#endif //ONE_WEEKEND_SAMPLER_HPP
