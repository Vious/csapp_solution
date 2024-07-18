#include <iostream>
#include <cstring>
#include <climits>
#include <cassert>

using namespace std;

//Q2.73
int saturating_add(int x, int y) {
    int sum = x + y;

    int negOver = (x & INT_MIN) && (y & INT_MIN) && !(sum & INT_MIN);
    int posOver = !(x & INT_MIN) && !(y & INT_MIN) && (sum & INT_MIN);

    (posOver && (sum = INT_MAX)) || (negOver && (sum = INT_MIN));

    return sum;
}

//q2.74
int tsub_ok(int x, int y) {
    int differ = x - y;
    
    int negOver = (x & INT_MIN) && !(y & INT_MIN) && !(differ & INT_MIN);
    int posOver = !(x & INT_MIN) && (y & INT_MIN) && (differ & INT_MIN);

    return (negOver | posOver) ? 0 : 1;
}

//Q2.75
// write the 64 bits multiplication
int signed_high_prod(int x, int y) {
    int64_t mulRes = (int64_t) x * y;
    return mulRes >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int signX = (x >> 31) & (0x1);
    int signY = (y >> 31) & (0x1);

    int highProd = signed_high_prod(x, y);
    // (x_w-1 * y + y_w-1 * x) * (2 ^ w)
    return highProd + x * signY + y * signX;
}

unsigned check_unsigned_high_prod(unsigned x, unsigned y) {
    uint64_t mulRes = (uint64_t) x * y;
    return mulRes >> 32;
}

// Q2.76
void* myCalloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0) {
        return NULL;
    }
    size_t bufSize = nmemb * size;
    if (nmemb == bufSize / size) {
        void *ptr = malloc(bufSize);
        if (ptr != NULL) {
            memset(ptr, 0, bufSize);
        }
        return ptr;
    }
    return NULL;
}

//Q2.77
void caseMulti(int x) {
    // K = 17
    int res = (x << 4) + x;
    cout << "K = 17 : " << x * 17 << " by bit operation : " << res << endl;

    res = x - (x << 3);
    cout << "K = -7 : " << x * -7 << " by bit operation : " << res << endl;

    res = (x << 6) - (x << 2);
    cout << "K = 60 : " << x * 60 << " by bit operation : " << res << endl;

    res = - ( (x << 7) - (x << 4) ) ;
    cout << "K = -112 : " << x * -112 << " by bit operation : " << res << endl;

}

int main()
{
    //test for q2.73
    cout << "Test for q2.73:" << endl;
    // cout << (int) 0x80000000 << endl;
    cout << "-1000 + 100: " << saturating_add(-1000, 100) << endl;
    cout << "INT_MIN + 10000: " << saturating_add(INT_MIN, 10000) << endl;
    cout << "INT_MAX - 10, INT_MAX - 100000: " << saturating_add(INT_MAX - 10, INT_MAX - 100000) << endl;
    cout << "INT_MIN + 10, INT_MIN + 100000: " << saturating_add(INT_MIN + 10, INT_MIN + 100000) << endl;

    //test for q2.74
    cout << "Test for q2.74:" << endl;
    cout << "INT_MIN, 1000 OK ?: " << tsub_ok(INT_MIN, 1000) << endl;
    cout << "500, 1000 OK ?: " << tsub_ok(500, 1000) << endl;
    cout << "500, INT_MIN OK ?: " << tsub_ok(500, INT_MIN) << endl;
    cout << "0, INT_MIN OK ?: " << tsub_ok(0, INT_MIN) << endl;


    //test for Q2.75
    cout << "Test for Q2.75:" << endl;
    cout << "For 0x12345678 X 0xABCDABCD: " << unsigned_high_prod(0x12345678, 0xABCDABCD);
    cout << " Correct answer: " << check_unsigned_high_prod(0x12345678, 0xABCDABCD) << endl;

    cout << "For 0x00358977, 0xFFFFFFFF: " << unsigned_high_prod(0x00358977, 0xFFFFFFFF);
    cout << " Correct answer: " << check_unsigned_high_prod(0x00358977, 0xFFFFFFFF) << endl;

    //test for Q2.76
    cout << "Test for Q2.76:" << endl;
    void *ptr = myCalloc(10000, 4);
    assert(ptr != NULL);
    free(ptr);

    ptr = myCalloc(SIZE_MAX, 2);
    assert(ptr == NULL);
    free(ptr);

    //test for Q2.77
    cout << "Test for Q2.77:" << endl;
    cout << "For x = 50: " << endl;
    caseMulti(50);
    cout << "For x = 128: " << endl;
    caseMulti(128);
    cout << "For x = -15: " << endl;
    caseMulti(-15);
    cout << "For x = -187: " << endl;
    caseMulti(-187);

    return 0;
}