#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


void final_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; ++a) {
        for (int b = -11; b < 11; ++b) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // lambertian
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center,0.2,sphere_material));                    
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5,1);
                    auto fuzz = random_double(0,0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // dielectric
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));
    
    auto aspect_ratio      = 16.0 / 9.0;
    int image_width       = 1200;
    int samples_per_pixel = 50; // 500;
    int max_depth         = 10; // 50;

    int vfov     = 20;
    point3 lookfrom = point3(13,2,3);
    point3 lookat   = point3(0,0,0);
    vec3 vup      = vec3(0,1,0);

    double defocus_angle = 0.6;
    double focus_dist    = 10.0;

    camera cam(
        aspect_ratio,
        image_width,
        samples_per_pixel,
        max_depth,
        vfov,
        lookfrom,
        lookat,
        vup,
        defocus_angle,
        focus_dist
    );

    cam.render(world);

}

void three_sphere_scene() {
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 100;
    int max_depth = 50;
    int vfov = 20;
    point3 lookfrom = point3(-2, 2, 1);
    point3 lookat = point3(0,0,-1);
    vec3 vup = vec3(0,1,0);
    double defocus_angle = 10.0;
    double focus_dist = 3.4;

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
        vfov, lookfrom, lookat, vup, defocus_angle, focus_dist
    );

    cam.render(world);
}

int main() {
    // three_sphere_scene();
    final_scene();
}
