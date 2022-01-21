
#include<fstream>
#include "ray.h"
#include "color.h"
#include "vec3.h"

#include<iostream>

using std::cout;
using std::endl;


//Fonctions

double hit_sphere(const point3& center, double radius, const ray& r) 
    {

        Vec3 oc = r.origin() - center;
        auto a = dot(r.direction(), r.direction());
        auto b = 2.0 * dot(oc, r.direction());
        auto c = dot(oc, oc) - radius*radius;
        auto discriminant = b*b - 4*a*c;
        
        if (discriminant < 0){
            return -1.0;
        }else{
            return (-b - sqrt(discriminant)) / (2.0*a) ;
        }

    }

Vec3 ray_color(const ray& r)
{
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if(t>=0.0){
        Vec3 norm = unitVector(r.at(t) - Vec3(0,0,-1));
        return 0.5*color(norm.x()+1, norm.y()+1, norm.z()+1);
    }
    
    Vec3 unit_direction = unitVector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Vec3(1.0, 1.0, 1.0)+ t*Vec3(0.5, 0.7, 1.0);
}




int main()
{
    std::ofstream output;
    output.open("output.ppm");
    
 // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = Vec3(viewport_width, 0, 0);
    auto vertical = Vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);


    // Render

    output << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(output, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";

    output.close();
    return 0;


}

