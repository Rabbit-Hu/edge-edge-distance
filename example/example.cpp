#include <iostream>
#include "Distance.h"

#ifdef EED_USE_DOUBLE
typedef double real;
#else
typedef float real;
#endif
typedef EED::Vector3<real> Vec3;

int main()
{

    // Vec3 x0(0, 0, 0);
    // Vec3 x1(1, 1, 0);
    // Vec3 x2(1, 1 - 1e-6, 0);
    // Vec3 x3(0, 1e-6, 0);

    // Vec3 x0(-1.0896217473782599, 9.7236145595088601e-007, 0.0);
    // Vec3 x1(0.91220578597858548, -9.4369829432107506e-007, 0.0);
    // Vec3 x2(-0.90010447502136237, 9.0671446351334441e-007, 0.0);
    // Vec3 x3(1.0730877178721130, -9.8185787633992740e-007, 0.0);

    // Vec3 x0(0, 0, 0);
    // Vec3 x1(1, 0, 0);
    // Vec3 x2(0.5, 1, 1e-3);
    // Vec3 x3(1.5, 1, 0);

    Vec3 x0, x1, x2, x3;
    std::cin >> x0 >> x1 >> x2 >> x3;

    real t0, t1;
    int type = EED::ee_closest_point(x0, x1, x2, x3, t0, t1);
    std::cout << "type: " << type << std::endl;
    std::cout << "t0: " << t0 << std::endl;
    std::cout << "t1: " << t1 << std::endl;

    Vec3 h0 = x0 * (1 - t0) + x1 * t0;
    Vec3 h1 = x2 * (1 - t1) + x3 * t1;
    real dist = (h0 - h1).length();
    std::cout << "h0: " << h0 << std::endl;
    std::cout << "h1: " << h1 << std::endl;
    std::cout << "dist: " << dist << std::endl;

    return 0;
}
