#include <iostream>
#include <cstring>
#include <climits>
#include <cassert>
#include <bitset>

using namespace std;

//Q2.78
int divide_power2(int x, int k) {
    int negSign = x & INT_MIN;
    (negSign && (x = x + (1 << k) - 1));
    return x >> k;
}

//Q2.79
int mul3div4(int x) {
    int res = (x << 1) + x;
    res = divide_power2(res, 2);
    return res;
}

//Q2.80
int threefourths(int x) {
    int negSign = x & INT_MIN;
    int left = x & (~0x3);
    int remain = x & 0x3;
    left = (left >> 2);
    left = (left << 1) + left;

    remain = (remain << 1) + remain;
    int bias = (1 << 2) - 1;
    (negSign && (remain = remain + bias));
    remain = remain >> 2;

    return left + remain;
}

//Q2.81
int ProbA(int k) {
    return -1 << k;
}

int ProbB(int j, int k) {
    return ~ProbA(k) << j;
}

//Q2.82
/* answers:
A. false, when x = INT_MIN, -x also equals to INT_MIN
B. true
C. true, note that ~x + x + 1 = 0
D. true, bit level representation is the same, then unsigned
E. true
 */
int main()
{
    //q2.78
    cout << "Test for q2.78:" << endl;
    cout << "-1 / 2 : " << divide_power2(-1, 1) << " answer: " << -1 / 2 << endl;
    cout << "0x800FFFFF / 2^4 : " << divide_power2(0x800FFFFF, 4) << " answer: " << (int)0x800FFFFF / 16 << endl;
    cout << "123456 / 16 : " << divide_power2(123456, 4) << " answer: " << 123456 / 16 << endl;


    cout << "Test for q2.79:" << endl;
    cout << "x = 1028 : " << mul3div4(1028) << " answer: " << 1028 * 3 / 4 << endl;
    // cout << "x = 0x800FFFFF : " << mul3div4(0x800FFFFF) << " answer: " << (int)0x800FFFFF * 3 / 4 << endl;

    cout << "Test for q2.80:" << endl;
    cout << "3/4 of 8: " << threefourths(8) << endl;
    cout << "3/4 of -8: " << threefourths(-8) << endl;

    cout << "3/4 of 16: " << threefourths(16) << endl;
    cout << "3/4 of -16: " << threefourths(-16) << endl;

    cout << "3/4 of 11: " << threefourths(11) << endl;
    cout << "3/4 of -11: " << threefourths(-11) << endl;


    cout << "Test for q2.81:" << endl;
    cout << bitset<sizeof(int) << 3>(ProbA(10)) << endl;
    cout << bitset<sizeof(int) << 3>(ProbB(8,1)) << endl;
    cout << bitset<sizeof(int) << 3>(ProbB(12, 8)) << endl;

    // cout << "Test for q2.82:" << endl;
    // cout << bitset<sizeof(unsigned) << 3> ((unsigned) 0x1 - 0x3) << endl;

    return 0;
}