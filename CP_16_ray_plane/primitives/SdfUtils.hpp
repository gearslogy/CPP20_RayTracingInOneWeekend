//
// Created by liuyangping on 2022/2/21.
//

#ifndef ONE_WEEKEND_SDFUTILS_H
#define ONE_WEEKEND_SDFUTILS_H

#include "Core/Kernel.hpp"


constexpr int MAX_MARCHING_STEPS = 1000;
constexpr float EPSILON = 0.00001;

//https://www.shadertoy.com/view/llt3R4

template<typename FUNC>
inline Vec3 estimateNormal(Vec3 p, FUNC && sdfSceneFunc ) {
    return normalize(Vec3(
            sdfSceneFunc(Vec3(p.x() + EPSILON, p.y(), p.z())) - sdfSceneFunc(Vec3(p.x() - EPSILON, p.y(), p.z())),
            sdfSceneFunc(Vec3(p.x(), p.y() + EPSILON, p.z())) - sdfSceneFunc(Vec3(p.x(), p.y() - EPSILON, p.z())) ,
            sdfSceneFunc(Vec3(p.x(), p.y(), p.z()  + EPSILON)) - sdfSceneFunc(Vec3(p.x(), p.y(), p.z() - EPSILON))
    ));
}
template<typename FUNC>
void rayMarching(Vec3 rayO, Vec3 rayDir, float start, float end, bool & hit,
                 float &rayDist,
                 Vec3 &rayHitP,
                 Vec3 &rayNormal,
                 FUNC && sdfSceneFunc) {



    float t = 0.0;
    for (int i = 0; i < MAX_MARCHING_STEPS && (t < end) ; i++) {
        auto pos = rayO + t * normalize(rayDir);
        float sd =  sdfSceneFunc( pos );

        if (sd < EPSILON )
        {
            hit = true;
            rayDist = t;
            rayHitP = pos;
            rayNormal = normalize(estimateNormal(pos, sdfSceneFunc));
            break;
        }
        t += sd;
    }


}



#endif //ONE_WEEKEND_SDFUTILS_H
