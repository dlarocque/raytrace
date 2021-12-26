#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"
#include "float.h"
#include "camera.h"

#include <memory>


vec3 ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0.0, MAXFLOAT, rec)) {
        return 0.5 * vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

hittable_list random_scene() {
    hittable_list world;

    world.add(std::make_shared<sphere>(point(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point(0, -100.5, 0), 100));

    return world;
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 50;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    auto world = random_scene();
    camera cam;

    for(int j = ny-1; j >= 0; j--) {
        for(int i = 0; i < nx; i++) {
            vec3 col(0,0,0);
            
            // antialiasing
            for(int s = 0; s < ns; s++) {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float (ny);
                ray r = cam.get_ray(u, v);
                vec3 p = r.at(2.0);
                col += ray_color(r, world);
            }
            col /= float(ns);

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
