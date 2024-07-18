// #include <iostream>
#include <stdio.h>
#include <assert.h>
// just for the simpler use of std::cout
// using namespace std;

//Q3.58
long decode2(long x, long y, long z) {
    y -= z;
    x *= y;
    return x ^ (y << 63 >> 63);
}

//Q3.59
/* cqto: 
• convert quad word to octal word
• no operands
• takes the sign bit from %rax and replicates it in all bits of %rdx
• effect: sign extend 64-bit signed %rax to 128-bit signed %rdx:%rax.

mulq %rsi:
• one operand is %rax
• The other operand given in the instruction
• product is stored in %rdx (high-order part) and %rax (low order part) -> full 128-bit result
 
 */

//Q3.60
long loop(long x, int n) {
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask <<= n) {
        result |= (x & mask);
    }
    return result;
}

//Q3.61
// /* 
long cread(long *xp) {
    return (xp ? *xp : 0);
}
//  */
long cread_alt(long *xp) {
    return (!xp ? 0 : *xp);
}

//Q3.62
typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

long switch3(long *p1, long *p2, mode_t action) {
    long result = 0;
    switch (action) {
        case MODE_A:
            result = *p2;
            // action = *p1;
            // *p2 = action;
            *p2 = *p1;
            break;
        case MODE_B:
            result = *p1 + *p2;
            *p1 = result;
            break;
        case MODE_C:
            *p1 = 59;
            result = *p2;
            break;
        case MODE_D:
            result = *p2;
            *p1 = result;
        case MODE_E:
            result = 27;
            break;
        
        default:
            result = 12;
            break;
    }
    return result;

}

//Q3.63
long switch_prob(long x, long n) {
    long result = x;
    switch(n) {

    }
    return result;
}

int main()
{
    // test for Q3.61
    long lnm = 0;
    assert(cread(&lnm) == cread_alt(&lnm)); 
    // assert(cread(NULL) == cread_alt(NULL));
    
    

    return 0;
}