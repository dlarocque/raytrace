#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {}
        ray(const point& origin, const vec3& direction)
            : orig(origin), dir(direction), tm(0) {}

        ray(const point& origin, const vec3& direction, double time)
            : orig(origin), dir(direction), tm(time) {}

        point origin() const { return orig; }
        vec3 direction() const { return dir; }
        double time() const { return tm; }

        point at(double t) {
            return orig + dir*t;
        }

    public:
        point orig;
        vec3 dir;
        double tm;
};

#endif
