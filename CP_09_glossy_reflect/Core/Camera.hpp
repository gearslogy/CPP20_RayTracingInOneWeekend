//
// Created by star on 2/14/2022.
//

#ifndef ONE_WEEKEND_CAMERA_HPP
#define ONE_WEEKEND_CAMERA_HPP

template<typename vec_t, typename ray_t>
struct Camera_T{
    Camera_T(){
        // Camera
        auto viewport_height = 2.0;
        auto viewport_width = aspect_ratio * viewport_height;
        auto focal_length = 1.0;

        origin = vec_t{0, 0, 0};
        horizontal = vec_t{viewport_width, 0, 0};
        vertical = vec_t{0, viewport_height, 0};
        lower_left_corner = origin - horizontal/2 - vertical/2 - vec_t{0, 0, focal_length};
    }

    ray_t getRay(double u, double v) const {
        return ray_t{origin, lower_left_corner + u*horizontal + v*vertical - origin};
    }

    vec_t origin{0,0,0};
    vec_t lower_left_corner;
    vec_t horizontal;
    vec_t vertical;
    double aspect_ratio{16.0/9.0};
};



#endif //ONE_WEEKEND_CAMERA_HPP
