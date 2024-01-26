#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
// #include "hittable.h"

class hit_record;

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(
            const ray& r_in,
            const hit_record& rec,
            color& attenuation,
            ray& scattered
        ) const = 0;
};

class lambertian : public material {
    // assuming lambertian diffusion on surface
    public:
        lambertian(const color& a) : albedo(a) {}

        bool scatter(const ray& r_in, const hit_record& rec, 
                    color& attenuation, ray& scattered) const override {
            auto scatter_direction = rec.normal + random_unit_vector();

            if (scatter_direction.near_zero()) { // avoid NaNs etc
                scatter_direction = rec.normal;
            }

            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true; // for now, always scatter with attenuation
        }
    
    private:
        color albedo;
};

class metal : public material {
    // assuming surface is metal, so it reflects light
    public:
        metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

        bool scatter(const ray& r_in, const hit_record& rec, 
                    color& attenuation, ray& scattered) const override {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz * random_unit_vector());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0); // for now, always scatter with attenuation
        }


    private:
        color albedo;
        double fuzz;
};

#endif