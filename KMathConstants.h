#pragma once

#include <DirectXMath.h>

//If you want to use Column Major, uncomment this pragma
//#define COLUMN_MAJOR

namespace KEngine
{
    namespace Math
    {
        //Alignment of classes that use __m128 structure
        //(Or XMVECTOR structure)
        constexpr size_t M128Alignment = 16;

        constexpr float Pi = 3.1415926f;
        constexpr float PiDiv2 = Pi * 0.5f;
        constexpr float PiDiv4 = Pi * 0.25f;
        constexpr float PiMul2 = Pi * 2.f;

        constexpr float e = 2.7182818284f;
    }
}