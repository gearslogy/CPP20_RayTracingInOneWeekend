//
// Created by liuyangping on 2022/2/21.
//

#ifndef ONE_WEEKEND_PRIMMANDELBULB_H
#define ONE_WEEKEND_PRIMMANDELBULB_H


#include "Core/Kernel.hpp"
#include "Core/Hittable.hpp"
#include "Core/Material.hpp"
#include "SdfUtils.hpp"

inline float SphereSDF(Vec3 p, Vec3 cen, double radius){
    return length(p - cen) - radius;
}

class SdfSphere : public Hittable {
public:
    explicit SdfSphere(Vec3 center, double radius):cen{center}, rad{radius}{
    }
    inline void setMaterial(const MaterialPtr &ptr){ matPtr = ptr; }
    [[nodiscard]] inline auto getMaterial() const{return matPtr;}

    bool hit(  const Ray& r, double t_min, double t_max, HitRecord& rec) const override{

        bool hit = false;
        Vec3 rayP {0,0,0};
        Vec3 rayN {0,0,0};
        float rayDist{0.0};
        auto rayDir = normalize(r.d);

        rayMarching(r.o, rayDir, 0, t_max, hit, rayDist, rayP, rayN, [this](Vec3 p) {
            return SphereSDF(p, this->cen, this->rad);
        });


        if(!hit) return false;

        rec.t = rayDist;
        rec.normal = rayN;
        rec.p = rayP + rec.normal * 0.0001;
        rec.matPtr = matPtr;
        return hit;
    }

public:
    Vec3 cen;
    double rad{1};
    MaterialPtr matPtr;
};




#endif //ONE_WEEKEND_PRIMMANDELBULB_H

