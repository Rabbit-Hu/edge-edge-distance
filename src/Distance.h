#include <cmath>
#include <iostream>
#include <iomanip>
#include "Vector.h"

namespace EED
{
    enum EEType
    {
        PP02 = 0,
        PP03 = 1,
        PP12 = 2,
        PP13 = 3,
        PE023 = 4,
        PE123 = 5,
        PE201 = 6,
        PE301 = 7,
        EE = 8,
    };

    template <typename T>
    int ee_closest_point(
        const Vector3<T> &x0,
        const Vector3<T> &x1,
        const Vector3<T> &x2,
        const Vector3<T> &x3,
        T &t0,
        T &t1,
        T parallel_sin_sq_tol = 1e-10)
    {
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
        auto N0 = (C * D - B * E); // t0 * D, "Nominator 0"
        auto N1 = (A * E - B * D); // t1 * E, "Nominator 1"
        auto D1 = D0;              // Denominator 1

        int type = EEType::EE;

        // std::cout << "e0.cross(e1): " << e0.cross(e1).lengthSq() << std::endl;
        // std::cout << "parallel thres: " << parallel_sin_sq_tol * A * C << std::endl;
        // std::cout << "N0: " << N0 << ", D0: " << D0 << std::endl;
        // std::cout << "N1: " << N1 << ", D1: " << D1 << std::endl;

        bool no_EE = (e0.cross(e1).dot(x02) == 0.0 ||                         // coplanar
                      e0.cross(e1).lengthSq() < parallel_sin_sq_tol * A * C); // parallel

        if (N0 <= 0.0 || (no_EE && N0 < D0 * 0.5)) // the t0=0 edge of the square is visible
        {
            N1 = E;
            D1 = C;
            t0 = 0.0;
            type = EEType::PE023; // if 0<t1<1 then return type = PE023
        }
        else if (N0 >= D0 || (no_EE && N0 >= D0 * 0.5)) // the t0=1 edge of the square is visible
        {
            N1 = E - B;
            D1 = C;
            t0 = 1.0;
            type = EEType::PE123; // if 0<t1<1 then return type = PE123
        }
        else
        {
            // if (N1 > 0.0 && N1 < D1 &&
            //     (e0.cross(e1).dot(x02) == 0.0 ||                         // coplanar
            //      e0.cross(e1).lengthSq() < parallel_sin_sq_tol * A * C)) // parallel
            // {
            //     std::cout << "Parallel or coplanar edges detected" << std::endl;
            //     // Ban EEType::EE, choose from the PP and PE types
            //     if (N0 < D0 * 0.5)
            //     {
            //         N1 = E;
            //         D1 = C;
            //         t0 = 0.0;
            //         type = EEType::PE023; // if 0<t1<1 then return type = PE023
            //     }
            //     else
            //     {
            //         N1 = E - B;
            //         D1 = C;
            //         t0 = 1.0;
            //         type = EEType::PE123; // if 0<t1<1 then return type = PE123
            //     }
            // }
            // else
            // {
            //     t0 = N0 / D0; // type = EEType::EE
            // }
            t0 = N0 / D0; // type = EEType::EE
        }

        if (N1 <= 0.0) // determined t1=0, i.e. vertex 2 active
        {
            t1 = 0.0;
            if (D <= 0.0)
            {
                t0 = 0.0;
                return EEType::PP02;
            }
            else if (D >= A)
            {
                t0 = 1.0;
                return EEType::PP12;
            }
            else
            {
                t0 = D / A;
                return EEType::PE201;
            }
        }
        else if (N1 >= D1) // determined t1=1, i.e. vertex 3 active
        {
            t1 = 1.0;
            if (D - B <= 0.0)
            {
                t0 = 0.0;
                return EEType::PP03;
            }
            else if (D - B >= A)
            {
                t0 = 1.0;
                return EEType::PP13;
            }
            else
            {
                t0 = (D - B) / A;
                return EEType::PE301;
            }
        }

        t1 = N1 / D1;
        return type;
    }

} // namespace EED
