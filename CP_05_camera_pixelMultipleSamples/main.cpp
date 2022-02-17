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

    Camera cam;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / cam.aspect_ratio);


    HittableList world;
    world.add(std::make_shared<Sphere>(Vec3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0.0f,-100.5f,-1.0f), 100.0));


    std::vector<char> imageData; // R/G/B array
    imageData.resize(image_width * image_height * 3);
    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {

            Vec3 pixel_color{0,0,0};
            for(int s = 0; s< 20; s++){
                auto u =     (double(i) + random_double() ) / (image_width-1);
                auto v = 1-  ( double(j) + random_double()) / (image_height-1);    // left cornel is 0,0

                auto ray = cam.getRay(u,v);
                pixel_color = pixel_color + ray_color(ray, world);
            }
            pixel_color/= 20;


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
