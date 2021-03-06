#ifndef HITTABLEH
#define HITTABLEH

#include "ray.h"

class material;


struct hit_record {
    double t;
    vec3 p;
    vec3 normal;
    bool front_face;
    shared_ptr<material> mat_ptr;

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        // if the dot product is negative, the ray direction and the outward_normal
        // face in oppositve directions.  If they face in opposite directions
        // the ray is directed toward the front face of the sphere
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};


class hittable {
     public:
         virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif
