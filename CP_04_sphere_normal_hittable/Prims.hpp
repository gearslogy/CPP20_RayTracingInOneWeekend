//
// Created by star on 2/14/2022.
//

#ifndef ONE_WEEKEND_PRIMS_HPP
#define ONE_WEEKEND_PRIMS_HPP



#include "Kernel.hpp"
#include "Hittable.hpp"


class Sphere : public Hittable {
public:
    Sphere() =default;
    Sphere(Vec3 cen, double r) : center(cen), radius(r) {};

    bool hit( const Ray& r, double t_min, double t_max, HitRecord& rec) const override{
        Vec3 oc = r.origin() - center;
        auto a = r.d.x() * r.d.x() + r.d.y() * r.d.y()+ r.d.z() * r.d.z();
        auto half_b = dot(oc, r.direction());
        auto c = length_squared(oc) - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        Vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        return true;
    }

public:
    Vec3 center;
    double radius{};
};


#endif //ONE_WEEKEND_PRIMS_HPP
