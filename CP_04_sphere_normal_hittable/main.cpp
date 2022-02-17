#include <iostream>
#include "Vec.hpp"
#include "Ray.hpp"
#include "Utils.hpp"
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "Kernel.hpp"
#include "Hittable.hpp"
#include "Prims.hpp"

Vec3 ray_color(const Ray& r, const HittableList & hitList) {
    HitRecord rec{};
    if(hitList.hit(r,0, 100, rec)){
        return 0.5 * (rec.normal + Vec3(1,1,1));

    }
    Vec3 unit_direction = normalize(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}

int main() {


    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Vec3(0, 0, 0);
    auto horizontal = Vec3{viewport_width, 0, 0};
    auto vertical = Vec3{0, viewport_height, 0};
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3{0, 0, focal_length};


    HittableList world;
    world.add(std::make_shared<Sphere>(Vec3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0.0f,-100.5f,-1.0f), 100.0));


    std::vector<char> imageData; // R/G/B array
    imageData.resize(image_width * image_height * 3);
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = 1-double(j) / (image_height-1);    // left cornel is 0,0

            Ray r{origin, lower_left_corner + u*horizontal + v*vertical};
            auto pixel_color = ray_color(r, world);


            auto idx = j * image_width + i;
            auto idx_r = idx*3 + 0; // R idx
            auto idx_g = idx*3 + 1; // G idx
            auto idx_b = idx*3 + 2; // B idx
            //std::cout <<"idx:::"<< idx <<"   "<<idx_r << " " << idx_g << " " << idx_b << std::endl;
            imageData[idx_r] = static_cast<char>(255.999 * pixel_color.x());
            imageData[idx_g] = static_cast<char>(255.999 * pixel_color.y());
            imageData[idx_b] = static_cast<char>(255.999 * pixel_color.z());
        }
    }


    stbi_write_jpg("image.jpg",image_width, image_height,3, imageData.data(),100);

    return 0;
}
