#include <iostream>
#include "Core/Vec.hpp"
#include "Core/Ray.hpp"
#include "Core/Utils.hpp"
#include <vector>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "Core/Kernel.hpp"
#include "Core/Hittable.hpp"
#include "Core/Prims.hpp"
#include "Materials/Lambertian.hpp"
#include <omp.h>
Vec3 ray_color(const Ray& r, const HittableList & hitList, int depth) {
    if(depth < 0) return color_black;
    HitRecord rec{};



    if(hitList.hit(r,0.001, infinity, rec)){
        Ray scattered;
        Color attenuation;
        if (rec.matPtr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, hitList, depth-1);
        return color_black;
    }

    Vec3 unit_direction = normalize(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
}

int main() {


    Camera cam;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / cam.aspect_ratio);
    const auto max_depth = 50;
    const auto max_samples =100;
    auto lambertian_ground = std::make_shared<Lambertian>(Color(0.5,0.5,0.5));
    auto lambertian_sphere = std::make_shared<Lambertian>(Color(1.0,0.0,0.0));
    auto groundObj = std::make_shared<Sphere>(Vec3(0.0f,-100.5f,-1.0f), 100.0);
    auto sphereObj = std::make_shared<Sphere>(Vec3(0,0,-1), 0.5);
    groundObj->setMaterial(lambertian_ground);
    sphereObj->setMaterial(lambertian_sphere);

    HittableList world;
    world.add(groundObj);
    world.add(sphereObj);

    std::vector<char> imageData; // R/G/B array
    imageData.resize(image_width * image_height * 3);

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {

            Vec3 pixel_color{0,0,0};
            for(int s = 0; s< max_samples; s++){
                auto u =     (double(i) + random_double() ) / (image_width-1);
                auto v = 1-  ( double(j) + random_double()) / (image_height-1);    // left cornel is 0,0
                auto ray = cam.getRay(u,v);
                pixel_color = pixel_color + ray_color(ray, world,max_depth);
            }
            pixel_color/= max_samples;

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
