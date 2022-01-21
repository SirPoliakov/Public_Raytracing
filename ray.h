#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray 
{
    public:
        ray() {}
        ray(const Vec3& origin, const Vec3& direction) // alias ? 
            : orig(origin), dir(direction)
        {}

        Vec3 origin() const  { return orig; }
        Vec3 direction() const { return dir; }

        Vec3 at(double t) const {
            return orig + t*dir;
        }

    public:
        Vec3 orig;
        Vec3 dir;
};

#endif
