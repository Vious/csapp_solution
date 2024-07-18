#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

// q2.68
int lower_one_mask(int n) {
    // a bit brute-force solution
    // int mask = 1;
    // mask = (mask << (n - 1));
    // mask |= (mask >> 16);
    // mask |= (mask >> 8);
    // mask |= (mask >> 4);
    // mask |= (mask >> 2);
    // mask |= (mask >> 1);
    // return mask;

    //here's another one
    int w = sizeof(int) << 3;
    return (unsigned) (-1) >> (w - n);

}

// q2.69
unsigned rotate_left(unsigned x, int n) {
    int w = sizeof(int) << 3;
    unsigned mask = (unsigned)(-1) >> n;
    // cout << hex << mask << endl; // check mask value
    x = ((x & mask) << n) | ((x & ~mask) >> (w - n));
    return x; 
}

// q2.70
int fits_bits(int x, int n) {
    int w = sizeof(int) << 3;
    int move = w - n;
    return (x << move >> move) == x;
}

// q2.71
typedef unsigned packet_t;
int xbyte(packet_t word, int bytenum) {
    int res = (int) word << ((3 - bytenum) << 3) >> 24;
    return res;
}

//q2.72
void copy_int(int val, void *buf, int maxbytes) {
    // buggy because sizeof returns unsigned, maxbytes - an unsigned, simply yields positive overflow
    // if (maxbytes - sizeof(val) >= 0) {
    //     memcpy(buf, (void *) &val, sizeof(val));
    // }
    if (maxbytes >= (int) sizeof(val)) {
        memcpy(buf, (void *) &val, sizeof(val));
    }

}

int main()
{
    //test for q2.68
    cout << "Test for q2.68:" << endl;
    cout << hex << lower_one_mask(1) << endl;
    cout << hex << lower_one_mask(6) << endl;
    cout << hex << lower_one_mask(17) << endl;
    cout << hex << lower_one_mask(32) << endl;

    // q2.69
    cout << "Test for q2.69:" << endl;
    cout << hex << rotate_left(0x12345678, 0) << endl;
    cout << hex << rotate_left(0x12345678, 4) << endl;
    cout << hex << rotate_left(0x12345678, 20) << endl;
    cout << hex << rotate_left(0x12345678, 32) << endl;

    // q2.70
    cout << "Test for q2.70:" << endl;
    cout << hex << "0xFF, 8: " << fits_bits(0xFF, 8) << endl;
    cout << hex << "~0xFF, 8: " << fits_bits(~0xFF, 8) << endl;

    cout << hex << "0b0010, 3: " << fits_bits(0b0010, 3) << endl;
    cout << hex << "0b1010, 3: " << fits_bits(0b1010, 3) << endl;

    // q2.71
    cout << "Test for q2.71:" << endl;
    cout << hex << "0x00112233, 0: " << xbyte(0x00112233, 0) << endl;
    cout << hex << "0x00112233, 1: " << xbyte(0x00112233, 1) << endl;
    cout << hex << "0x00112233, 2: " << xbyte(0x00112233, 2) << endl;
    cout << hex << "0x00112233, 3: " << xbyte(0x00112233, 3) << endl;

    cout << hex << "0xAABBCCDD, 0: " << xbyte(0xAABBCCDD, 0) << endl;
    cout << hex << "0xAABBCCDD, 1: " << xbyte(0xAABBCCDD, 1) << endl;
    cout << hex << "0xAABBCCDD, 2: " << xbyte(0xAABBCCDD, 2) << endl;
    cout << hex << "0xAABBCCDD, 3: " << xbyte(0xAABBCCDD, 3) << endl;

    //q2.72
    cout << "Test for q2.72:" << endl;
    int maxbytes = sizeof(int);
    void *buf = malloc(maxbytes);
    int val;

    val = 0x12345678;
    copy_int(val, buf, maxbytes);
    cout << "In buf: " << *(int *)buf << endl;

    val = 0xABCDABCD;
    copy_int(val, buf, maxbytes - 1);
    cout << "In buf: " << *(int *)buf << endl;
    copy_int(val, buf, maxbytes);
    cout << "In buf: " << *(int *)buf << endl;

    free(buf);
    return 0;
}