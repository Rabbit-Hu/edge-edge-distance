#include <iostream>
#include <fstream>
#include "Vector.h"
#include "Distance.h"

#ifdef EED_USE_DOUBLE
typedef double real;
#else
typedef float real;
#endif
typedef EED::Vector3<real> Vec3;


real pe_distance_gt(Vec3 x0, Vec3 x1, Vec3 x2, real &t)
{
    Vec3 e0 = x1 - x0;
    Vec3 x02 = x2 - x0;
    t = e0.dot(x02) / e0.lengthSq();
    if (t < 0.0)
    {
        t = 0.0;
        return x02.length();
    }
    else if (t > 1.0)
    {
        t = 1.0;
        return (x2 - x1).length();
    }
    else
    {
        return (x02 - e0 * t).length();
    }
}

real distance_gt(Vec3 x0, Vec3 x1, Vec3 x2, Vec3 x3, real &t0, real &t1)
{
    real l = 0.0, r = 1.0;
    real a, b, da, db;
    for (int i = 0; i < 200; i++)
    {
        a = l + (r - l) / 3;
        b = l + (r - l) / 3 * 2;
        da = pe_distance_gt(x0, x1, x2 * (1 - a) + x3 * a, t0);
        db = pe_distance_gt(x0, x1, x2 * (1 - b) + x3 * b, t0);
        if (da < db)
        {
            r = b;
        }
        else
        {
            l = a;
        }
    }
    t1 = (l + r) / 2;
    return pe_distance_gt(x0, x1, x2 * (1 - t1) + x3 * t1, t0);
}

bool type_sanity_check(int type, real t0, real t1){
    if (type == EED::EEType::PP02) 
        return t0 == 0.0 && t1 == 0.0;
    if (type == EED::EEType::PP03)
        return t0 == 0.0 && t1 == 1.0;
    if (type == EED::EEType::PP12)
        return t0 == 1.0 && t1 == 0.0;
    if (type == EED::EEType::PP13)
        return t0 == 1.0 && t1 == 1.0;
    if (type == EED::EEType::PE023)
        return t0 == 0.0 && t1 > 0.0 && t1 < 1.0;
    if (type == EED::EEType::PE123)
        return t0 == 1.0 && t1 > 0.0 && t1 < 1.0;
    if (type == EED::EEType::PE201)
        return t0 > 0.0 && t0 < 1.0 && t1 == 0.0;
    if (type == EED::EEType::PE301)
        return t0 > 0.0 && t0 < 1.0 && t1 == 1.0;
    if (type == EED::EEType::EE)
        return t0 > 0.0 && t0 < 1.0 && t1 > 0.0 && t1 < 1.0;
    return false;
}

int test_file(const char *filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    int type_cnt[9] = {0};
    int error_cnt = 0;
    int total_cnt = 0;
    real max_error = 0.0;

    while (true)
    {
        Vec3 x0, x1, x2, x3;

        file >> x0 >> x1 >> x2 >> x3;

        // std::cout << "x0: " << x0 << std::endl;
        // std::cout << "x1: " << x1 << std::endl;
        // std::cout << "x2: " << x2 << std::endl;
        // std::cout << "x3: " << x3 << std::endl;

        if (!file)
        {
            break;
        }

        real t0, t1;
        int type = EED::ee_closest_point(x0, x1, x2, x3, t0, t1);
        // std::cout << "type: " << type << std::endl;
        // std::cout << "t0: " << t0 << std::endl;
        // std::cout << "t1: " << t1 << std::endl;

        Vec3 h0 = x0 * (1 - t0) + x1 * t0;
        Vec3 h1 = x2 * (1 - t1) + x3 * t1;
        real dist = (h0 - h1).length();
        // std::cout << "h0: " << h0 << std::endl;
        // std::cout << "h1: " << h1 << std::endl;
        // std::cout << "dist: " << dist << std::endl;

        real t0_gt, t1_gt;
        real dist_gt = distance_gt(x0, x1, x2, x3, t0_gt, t1_gt);
        // std::cout << "t0_gt: " << t0_gt << std::endl;
        // std::cout << "t1_gt: " << t1_gt << std::endl;
        // std::cout << "dist: " << dist << ", dist_gt: " << dist_gt << std::endl;

        real diff = std::abs(dist - dist_gt);
        max_error = std::max(max_error, diff);

        if (diff > 1e-6 || !type_sanity_check(type, t0, t1))
        {
            error_cnt++;

            auto e0 = x1 - x0;
            auto e1 = x3 - x2;
            auto x02 = x2 - x0;

            // Find closest point on the two lines:
            //   h0 = x0 + t0 * e0
            //   h1 = x2 + t1 * e1

            auto A = e0.lengthSq();
            auto B = -e0.dot(e1);
            auto C = e1.lengthSq();

            auto D = x02.dot(e0);
            auto E = -x02.dot(e1);

            // [A B; B C] @ [t0; t1] = [D; E]
            auto D0 = A * C - B * B;   // det(A, B; B, C), always >= 0

            std::cout << "x0: " << x0 << std::endl;
            std::cout << "x1: " << x1 << std::endl;
            std::cout << "x2: " << x2 << std::endl;
            std::cout << "x3: " << x3 << std::endl;
            std::cout << "dist: " << dist << ", dist_gt: " << dist_gt << std::endl;
            std::cout << "diff: " << diff << std::endl;
            std::cout << "type: " << type << std::endl;
            std::cout << "t0: " << t0 << std::endl;
            std::cout << "t1: " << t1 << std::endl;
            std::cout << "t0_gt: " << t0_gt << std::endl;
            std::cout << "t1_gt: " << t1_gt << std::endl;
            std::cout << "D0: " << D0 << std::endl;
            std::cout << std::endl;
        }

        type_cnt[type]++;
        total_cnt++;
    }

    file.close();

    std::cout << "type count:" << std::endl;
    for (int i = 0; i < 9; i++)
    {
        std::cout << "type " << i << ": " << type_cnt[i] << std::endl;
    }

    std::cout << "error count: " << error_cnt << "/" << total_cnt << std::endl;
    std::cout << "max error: " << max_error << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    test_file(argv[1]);

    return 0;
}
