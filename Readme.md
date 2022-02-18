## C++ 20 Generic Method : Raytracing in one week
* C++ 20 
* progress wip
* high performance rendering with threading blocks & std::async


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