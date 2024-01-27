#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 100;
    int max_depth = 50;
    int vfov = 20;
    point3 lookfrom = point3(-2, 2, 1);
    point3 lookat = point3(0,0,-1);
    vec3 vup = vec3(0,1,0);

    // World
    hittable_list world;

    // auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    // // auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    // // auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    // auto material_center = make_shared<dielectric>(1.5);
    // auto material_left = make_shared<dielectric>(1.5);
    // auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100, material_ground));
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1,0,-1), 0.5, material_left));    
    // for the below sphere with negative radius --> surface normal points inward
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0),-0.4, material_left));
    world.add(make_shared<sphere>(point3(1,0,-1), 0.5, material_right));    

    // auto R = cos(pi/4);

    // auto material_left  = make_shared<lambertian>(color(0,0,1));
    // auto material_right = make_shared<lambertian>(color(1,0,0));

    // world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
    // world.add(make_shared<sphere>(point3( R, 0, -1), R, material_right));

    camera cam(
        aspect_ratio, image_width, samples_per_pixel, max_depth,
        vfov, lookfrom, lookat, vup
    );

    cam.render(world);
}
