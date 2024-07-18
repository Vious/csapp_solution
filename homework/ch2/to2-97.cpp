#include <iostream>
#include <cstring>
#include <climits>
#include <cassert>
#include <bitset>
#include <cmath>

using namespace std;

// Q2.84
union F2uUnion {
    float f;
    unsigned u;
};

unsigned f2u(float x) {
    return *reinterpret_cast<unsigned*>(&x);
}

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return ((ux <= uy) && !(sx & 0x1) && !(sy & 0x1)) || ((ux >= uy) && (sx & 0x1)) 
        || ((ux << 1 == 0) && ((uy << 1 == 0)));
}

//Q2.89
/* 
A. true
B. false, y = INT_MIN
C. true
D. false, may cause overflow
E. false, when dz = 0
 */

//Q2.90
float u2f(unsigned x) {
    return *reinterpret_cast<float*> (&x);
}

float fpwr2(int x) {
    unsigned exp, frac;
    unsigned u;

    if (x < 2 - 128 - 23) {
        exp = 0;
        frac = 0;
    } else if (x < -126) {
        exp = 0;
        frac = 1 << (149 + x);
    } else if (x < 128) {
        exp = x + 126 + 1;
        frac = 0;
    } else {
        exp = 255;
        frac = 0;
    }

    u = exp << 23 | frac;
    return u2f(u);

}
// Q2.92
typedef unsigned float_bits;

float_bits float_negate(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned u;
    if (exp == 0xFF && frac != 0) {
        return f;
    }
    // (!sign && (sign = 1)) || (sign && (sign = 0));
    // u = sign << 31 | exp << 23 | frac;

    u = ~sign << 31 | exp << 23 | frac;
    return u;
}

//Q2.93
float_bits float_absval(float_bits f){
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0xFF && frac != 0) {
        return f;
    }
    (!!sign && (sign = 0));
    /* more directly, 0 << 31 | exp << 23 | frac; */
    return sign << 31 | exp << 23 | frac;
}

//Q2.94
float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0xFF && frac != 0) {
        return f;
    }
    if (exp == 0) {
        frac << 1;
    } else if (exp == 0xFE) {
        exp = 0xFF;
        frac = 0;
    } else {
        exp += 1;
    }

    return sign << 31 | exp << 23 | frac;

}

//Q2.95
float_bits float_half(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    unsigned noSignPart = f & 0x7FFFFFFF;

    if (exp == 0xFF) {
        return f;
    }
    int roundAdd = (frac & 0x3) == 0x3;
    if (exp == 0) {
        frac = frac >> 1;
        frac = frac + roundAdd;
    } else if (exp == 1) {
        noSignPart = noSignPart >> 1;
        noSignPart += roundAdd;
        exp = noSignPart >> 23 & 0xFF;
        frac = noSignPart & 0x7FFFFF;
    } else {
        exp -= 1;
    }
    return sign << 31 | exp << 23 | frac;
}

//Q2.96
int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF) {
        return 0x80000000;
    }
    unsigned bias = 0x7F;
    unsigned E;
    unsigned M;
    int ret;
    if (exp < bias) {
        return 0;
    } else if (exp >= 31 + bias) {
        return 0x80000000;
    } else {
        M = frac | 0x800000;
        E = exp - bias;
        if (E > 23) {
            ret = M << (E - 23);
        } else {
            ret = M >> (23 - E);
        }
    }


    return sign ? -ret : ret;
}

//Q2.97
float_bits float_i2f(int i) {
    unsigned sign, exp, frac;
    unsigned bias = 0x7F;
    if (i == 0) {
        return 0x0;
    } 
    if (i == INT_MIN) {
        exp = bias + 31;
        return 1 << 31 | exp << 23 | 0;
    }
    if (i < 0) {
        sign = 1;
        i = -i;
    }

    unsigned E = 0, bits = i;
    while(bits) {
        bits >>= 1;
        E += 1;
    }
    // unsigned tmpFracBits;
    unsigned M = i;
    if ( E <= 23) {
        M <<= (23 - E);
    } else {
        unsigned truncMask = (unsigned) -1 >> (32 - (E - 23));
        unsigned truncVal = truncMask & M;
        unsigned haveLsb = (M >> (E - 23)) & 0x1;
        unsigned halfTrunc = 1 << (E - 23 - 1);
        unsigned rounded = (haveLsb && truncVal >= halfTrunc) || (!haveLsb && truncVal > halfTrunc);
        M >>= (E - 23);
        M += rounded;
        if ((1 << 24) == M) {
            M >>= 1;
            E += 1;
        }
    }

    exp = E + bias;
    frac = M - ( 1 << 23);

    return sign << 31 | exp << 23 | frac;
}

int main()
{
    cout << "Test for q2.84:" << endl;
    cout << "<= compare: 1.237777, 1.237778: " << float_le(1.237777, 1.237778) << endl;
    cout << "<= compare: 1.237777, -1.237778: " << float_le(1.237777, -3.4423832) << endl;
    cout << "<= compare: -1.237777, -1.237778: " << float_le(-1.237777, -3.4423832) << endl;
    cout << "<= compare: -10.237777, -1.237778: " << float_le(-10.237777, -3.4423832) << endl;
    cout << "<= compare: 0, -0.0: " << float_le(+0.0, -0.0) << endl;
    cout << "<= compare: -0, +0.0: " << float_le(-0.0, +0.0) << endl;
    cout << "<= compare: 0.0, 0.0: " << float_le(0.0, 0.0) << endl;

    cout << "Test for q2.90:" << endl;
    assert(fpwr2(0) == powf(2,0));
    assert(fpwr2(100) == powf(2,100));
    assert(fpwr2(-100) == powf(2,-100));
    assert(fpwr2(10000) == powf(2,10000));
    assert(fpwr2(-10000) == powf(2,-10000));

    cout << "Test for q2.92:" << endl;
    cout << "Test for 0x0F401258: " << hex << float_negate(0x0F401258) << endl;
    cout << "Test for 0x8F401258: " << hex << float_negate(0x8F401258) << endl;
    cout << "Test for 0xFFFFF001: " << hex << float_negate(0xFFFFF001) << endl;
    cout << "Test for 0x7FFFF001: " << hex << float_negate(0x7FFFF001) << endl;

    cout << "Test for q2.93:" << endl;
    cout << "Test for 0x0F401258: " << hex << float_absval(0x0F401258) << endl;
    cout << "Test for 0x8F401258: " << hex << float_absval(0x8F401258) << endl;
    cout << "Test for 0xAF401258: " << hex << float_absval(0xAF401258) << endl;
    cout << "Test for 0xFFFFF001: " << hex << float_absval(0xFFFFF001) << endl;
    cout << "Test for 0x7FFFF001: " << hex << float_absval(0x7FFFF001) << endl;

    cout << "Test for q2.94:" << endl;
    cout << "Test for 0xFFFFF001: " << hex << float_twice(0xFFFFF001) << endl;
    cout << "Test for 0x0F401258: " << hex << float_twice(0x0F401258) << endl;
    cout << "Test for 0x7F123456: " << hex << float_twice(0x7F123456) << endl;

    cout << "Test for q2.95:" << endl;
    cout << "Test for 0xFFFFF001: " << hex << float_half(0xFFFFF001) << endl;
    cout << "Test for 0x0F401258: " << hex << float_half(0x0F401258) << endl;
    cout << "Test for 0x7F123456: " << hex << float_half(0x7F123456) << endl;
    cout << "Test for 0x00000123: " << hex << float_half(0x00000123) << endl;

    cout << "Test for q2.96:" << endl;
    cout << "Test for 0xFFFFF001: " << hex << float_f2i(0xFFFFF001) << endl;
    cout << "Test for 0x0F401258: " << hex << float_f2i(0x0F401258) << endl;
    cout << "Test for 0x43401258: " << hex << float_f2i(0x43401258) << endl;
    cout << "Test for 0x7F123456: " << hex << float_f2i(0x7F123456) << endl;
    cout << "Test for 0x00000123: " << hex << float_f2i(0x00000123) << endl;

    // cout << "Test for q2.97:" << endl;


    return 0;
}