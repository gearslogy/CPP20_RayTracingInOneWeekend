//
// Created by star on 2/14/2022.
//

#ifndef ONE_WEEKEND_CAMERA_HPP
#define ONE_WEEKEND_CAMERA_HPP

template<typename vec_t, typename ray_t>
struct Camera_T{
    constexpr Camera_T(double verticalFieldOfView, double aspectRatio) noexcept: vFov(verticalFieldOfView),aspectWHRatio(aspectRatio) {

        auto theta = degrees_to_radians(vFov);
        auto h = tan(theta/2);
        auto viewPortHeight = 2.0 * h;
        auto viewPortWidth = aspectWHRatio * viewPortHeight;
        origin = vec_t{0, 0, 0};
        horizontal = vec_t{viewPortWidth, 0, 0};
        vertical = vec_t{0, viewPortHeight, 0};
        lower_left_corner = origin - horizontal/2 - vertical/2 - vec_t{0, 0, vFocalLength};

    }


    ray_t getRay(double u, double v) const {
        return ray_t{origin, lower_left_corner + u*horizontal + v*vertical - origin};
    }

    inline auto getAspectRatio(){
        return aspectWHRatio;
    }

    vec_t origin{0,0,0};
    vec_t lower_left_corner;
    vec_t horizontal;
    vec_t vertical;


    double vFov{45};  //vertical field-of-view in degrees
    double aspectWHRatio{16.0/9.0};
    double vFocalLength{1.0};
};



#endif //ONE_WEEKEND_CAMERA_HPP
