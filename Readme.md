## C++ 20 Generic Method : Raytracing in one week
* C++ 20 
* progress wip
* high performance rendering with threading blocks & std::async
* C++ faster random engine with CRTP + singleton

### CP_04_sphere_normal_hittable


![image](CP_04_sphere_normal_hittable/image.jpg)



### CP_05_camera_pixelMultipleSamples

![image](CP_05_camera_pixelMultipleSamples/image.jpg)


### CP_06_material_lambertian

![image](CP_06_material_lambertian/image.jpg)



### CP_07_parallel_material_lambertian

![image](CP_07_parallel_material_lambertian/parallex.png)

![image](CP_07_parallel_material_lambertian/image.jpg)


### CP_08_material_perfect_reflect_gamma_correct
![image](CP_08_material_perfect_reflect_gamma_correct/image.jpg)



### CP_09_glossy_reflect
![image](CP_09_glossy_reflect/image.jpg)
```
auto material_left   = std::make_shared<PerfectReflection>(Color(0.8, 0.8, 0.8), 0.5);
auto material_right  = std::make_shared<PerfectReflection>(Color(0.8, 0.6, 0.2),1);
```
render dt:100s, 100samplers, width=1280


* cos-weighted hemisphere is another choice, but need check the glossy reflected vector  is not entering the sphere
* (red is reflected vector)

![image](CP_09_glossy_reflect/hemisphere.png)

"raytracing in one weekend" is solves that problem. because it used this method:

![image](CP_09_glossy_reflect/sphere_random_reflection.png)

## CP_10_refract
![image](CP_10_refract/image.jpg)

render time dt: 103s
* 折射向量推导
* 全内折射
* fresnel 多项式逼近

![image](CP_10_refract/refract.png)

![image](CP_10_refract/schlick.png)

![image](CP_10_refract/Total_Internal_Reflection.png)

## CP_11 vertical field-of-view 

vfov:45

![image](CP_11_fov/vfov45.jpg)

vfov:90

![image](CP_11_fov/vfov90.jpg)