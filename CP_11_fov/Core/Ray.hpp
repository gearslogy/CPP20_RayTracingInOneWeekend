//
// Created by star on 2/13/2022.
//

#ifndef ONE_WEEKEND_RAY_HPP
#define ONE_WEEKEND_RAY_HPP
#include <iostream>
template<typename Vec_t >
struct Ray_t{
    auto at(double t) const {
        return o+ t * d;
    }
    auto direction()const{return d;}
    auto origin() const{return o;}

    Vec_t o; // xyz o
    Vec_t d; // xyz dir
};

template< typename Vec_t>
inline std::ostream  & operator <<(std::ostream & os , const Ray_t<Vec_t> & ray){
    os << "ray origin:" << ray.o <<" direction:" << ray.d;
    return os;
}

#endif //ONE_WEEKEND_RAY_HPP
