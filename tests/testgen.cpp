#include <iostream>
#include <fstream>
#include <random>
#include "Vector.h"

#ifdef EED_USE_DOUBLE
typedef double real;
#else
typedef float real;
#endif
typedef EED::Vector3<real> Vec3;

Vec3 random_vec3(std::mt19937 &gen, real radius = 1.0)
{
    std::uniform_real_distribution<real> dis(-radius, radius);

    return Vec3(dis(gen), dis(gen), dis(gen));
}

int main()
{
    int n_samples = 100000;
    int seed = 42;
    real radius = 1.0;

    std::mt19937 gen(seed);

    std::ofstream file("testdata_random.txt");
    if (file.is_open())
    {
        for(int i = 0; i < n_samples; i++)
        {
            Vec3 x0 = random_vec3(gen, radius);
            Vec3 x1 = random_vec3(gen, radius);
            Vec3 x2 = random_vec3(gen, radius);
            Vec3 x3 = random_vec3(gen, radius);
            
            file << x0 << " " << x1 << " " << x2 << " " << x3 << std::endl;
        }
        file.close();
        std::cout << "File written successfully: testdata_random.txt" << std::endl;
    }
    else
    {
        std::cout << "Failed to open file testdata_random.txt" << std::endl;
    }

    std::ofstream file2("testdata_parallel.txt");
    if (file2.is_open())
    {
        for(int i = 0; i < n_samples; i++)
        {
            Vec3 n = random_vec3(gen, radius).normalize();
            std::uniform_real_distribution<real> dis(0, radius);
            real l0 = dis(gen);
            real l1 = dis(gen);
            
            int flip = std::uniform_int_distribution<int>(0, 1)(gen);

            Vec3 x0 = random_vec3(gen, radius);
            Vec3 x1 = x0 + n * l0;
            Vec3 x2 = random_vec3(gen, radius);
            Vec3 x3 = x2 + n * l1;
            if (flip)
            {
                std::swap(x2, x3);
            }
            
            file2 << x0 << " " << x1 << " " << x2 << " " << x3 << std::endl;
        }
        file2.close();
        std::cout << "File written successfully: testdata_parallel.txt" << std::endl;
    }
    else
    {
        std::cout << "Failed to open file testdata_parallel.txt" << std::endl;
    }

    std::ofstream file3("testdata_coplanar.txt");
    if (file3.is_open())
    {
        for(int i = 0; i < n_samples; i++)
        {
            Vec3 e0 = random_vec3(gen, radius).normalize();
            
            Vec3 x0 = random_vec3(gen, radius);
            Vec3 x1 = random_vec3(gen, radius);
            Vec3 x2 = random_vec3(gen, radius);
            Vec3 x3 = random_vec3(gen, radius);

            x0 = x0 - e0 * e0.dot(x0);
            x1 = x1 - e0 * e0.dot(x1);
            x2 = x2 - e0 * e0.dot(x2);
            x3 = x3 - e0 * e0.dot(x3);
            
            file3 << x0 << " " << x1 << " " << x2 << " " << x3 << std::endl;
        }
        file3.close();
        std::cout << "File written successfully: testdata_coplanar.txt" << std::endl;
    }
    else
    {
        std::cout << "Failed to open file testdata_coplanar.txt" << std::endl;
    }

    return 0;
}