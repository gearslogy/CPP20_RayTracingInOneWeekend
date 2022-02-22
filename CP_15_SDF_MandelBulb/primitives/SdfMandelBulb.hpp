//
// Created by liuyangping on 2022/2/21.
//

#ifndef ONE_WEEKEND_SDFMANDELBULB_H
#define ONE_WEEKEND_SDFMANDELBULB_H



#include "Core/Kernel.hpp"
#include "Core/Hittable.hpp"
#include "Core/Material.hpp"
#include "SdfUtils.hpp"

// Filmic mandelbulb animation  https://www.shadertoy.com/view/wl2SDt
float distanceEstimation(Vec3 p) {
    const float Power = 8;
    auto pos = p + Vec3{0,-0.5,0};
    if(length(pos) > 1.5) return length(pos) - 1.2;
    Vec3 z = pos;
    float dr = 1.0, r = 0.0, theta, phi;
    for (int i = 0; i < 15; i++) {
        r = length(z);
        if (r>1.5) break;
        dr =  pow( r, Power-1.0)*Power*dr + 1.0;
        theta = acos(z.z()/r) * Power ;
        phi = atan2(z.y(),z.x()) * Power ;
        float sinTheta = sin(theta);
        z = pow(r,Power) * Vec3(sinTheta*cos(phi), sinTheta*sin(phi), cos(theta)) + pos;
    }
    return 0.5*log(r)*r/dr;
}

class SdfMandleBulb : public Hittable {
public:

    inline void setMaterial(const MaterialPtr &ptr){ matPtr = ptr; }
    [[nodiscard]] inline auto getMaterial() const{return matPtr;}

    bool hit( const Ray& r, double t_min, double t_max, HitRecord& rec) const override{
        bool hit = false;
        auto rayDir = normalize(r.d);
        Vec3 rayP {0,0,0};
        Vec3 rayN {0,0,0};
        float rayDist{0};

        // raymarching
        rayMarching(r.o, normalize(r.d), 0, t_max, hit, rayDist, rayP, rayN, [this](Vec3 p) {
            return distanceEstimation(p);
        });

        if(!hit) return false;

        rec.t = rayDist;
        rec.normal = rayN;
        rec.p = rayP + rec.normal * 0.0001;
        rec.matPtr = matPtr;
        return true;
    }

public:
    Vec3 cen{0,0,0};
    double rad{1};
    MaterialPtr matPtr;
};



#endif //ONE_WEEKEND_SDFMANDELBULB_H
