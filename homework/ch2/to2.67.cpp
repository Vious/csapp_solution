/*
 * show-bytes.c
 is_liitle_endian
 */

#include <stdio.h>
#include <assert.h>
#include <iostream>

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
  size_t i;
  for (i = 0; i < len; i++) {
    printf(" %.2x", start[i]);
  }
  printf("\n");
}

void show_int(int x) {
  show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
  show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void* x) {
  show_bytes((byte_pointer) &x, sizeof(void*));
}


// show bites for short, long and double
void show_short(short x) {
  show_bytes((byte_pointer) &x, sizeof(short));   
}

void show_long(long x) {
  show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x) {
  show_bytes((byte_pointer) &x, sizeof(double));
}


void test_show_bytes(int val) {
  int ival = val;
  float fval = (float) ival;
  int* pval = &ival;

  show_int(ival);
  show_float(fval);
  show_pointer(pval);

  // for short, long and double
  int sval = (short) val;
  show_short(sval);

  long lval = (long) val;
  show_long(lval);

  double dval = (double) val;
  show_double(dval);

}


// q2.58
int is_liitle_endian() {
  int test_num = 0xFF;
  byte_pointer byte_start = (byte_pointer) &test_num;

  if (byte_start[0] == 0xFF) {
    return 1;
  }
  return 0;
}

// q2.59
// int main(int argc, char* argv[]) {
//   size_t mask = 0xFF;
//   size_t x = 0x89ABCDEF;
//   size_t y = 0x76543210;

//   size_t res = (x & mask) | (y & ~mask);

//   std::cout << std::hex << res << std::endl;

//   return 0;
// }

//q2.60
unsigned replace_byte(unsigned x, int i, unsigned char b) {
  unsigned ret;
  if (i < 0 || i > sizeof(unsigned) - 1) {
    return x;
  }
  unsigned mask = 0xFF;
  mask = mask << (i * 8);
  ret = (x & ~mask) | (b << (i*8));

  return ret;
}

//q2.63 shifts
unsigned srl(unsigned x, int k) {
  unsigned xsra = (int) x >> k;
 
  int w = 8 * sizeof(int);
  int move = -1;
  move = (move) << (w - k);
  xsra = (xsra) & (~move);
  
  return xsra;
}

int sra(int x, int k) {
  int xsrl = (unsigned) x >> k;

  int w = 8 * sizeof(int);
  int move = -1;
  move = (move) << (w - k);

  int mask = 1 << (w - 1);
  move &= !(x & mask) - 1;

  xsrl = xsrl | move;
  return xsrl;
}


//q2.64
int any_odd_one(unsigned x) {
  // 1010 = A!!!! important
  int mask = 0xAAAAAAAA;
  return !!(x & mask);
}

//q2.65
int odd_ones(unsigned x) {
  x ^= (x >> 16);
  x ^= (x >> 8);
  x ^= (x >> 4);
  x ^= (x >> 2);
  x ^= (x >> 1);
  x &= 0x1;

  return x;
}

//q2.66
int leftmost_one(unsigned x) {
  if (x == 0) {return 0;}
  // very clever answer from solution code
  /*
  * first, generate a mask that all bits after leftmost one are one
  * e.g. 0xFF00 -> 0xFFFF, and 0x6000 -> 0x7FFF
  * If x = 0, get 0
  */
  x |= (x >> 1);
  x |= (x >> 2);
  x |= (x >> 4);
  x |= (x >> 8);
  x |= (x >> 16);
  /*
   * then, do (mask >> 1) + (mask && 1), in which mask && 1 deals with case x = 0, reserve leftmost bit one
   * that's we want
   */
  return (x ^ (x >> 1));

}

int int_size_is_32() {
  int sub_msb = 1 << 31;
  int beyond_msb = sub_msb << 1;

  return sub_msb && !beyond_msb;
}

int int_size_is_32_for_16bit() {
  int sub_msb = ((1 << 15) << 15) << 1;
  int beyond_msb = sub_msb << 1;
  return sub_msb && !beyond_msb;

}

int main(int argc, char* argv[]) {
  int test_num = 328;
  int test2 = 1024;
  test_show_bytes(test_num);
  // test_show_bytes(test2);
  int ret = is_liitle_endian();
  std::cout << "Is little endian: " << ret << std::endl;

  unsigned res1 = replace_byte(0x12345678, 2, 0xAB);
  unsigned res2 = replace_byte(0x12345678, 0, 0xAB);
  std::cout << std::hex << res1 << std::endl;
  std::cout << std::hex << res2 << std::endl;

  unsigned test_unsigned = 0x12345678;
  int test_int = 0x12345678;

  assert(srl(test_unsigned, 4) == test_unsigned >> 4);
  assert(sra(test_int, 4) == test_int >> 4);
  
  assert(srl(test_unsigned, 8) == test_unsigned >> 8);
  assert(sra(test_int, 8) == test_int >> 8);

  test_unsigned = 0x87654321;
  test_int = 0x87654321;

  assert(srl(test_unsigned, 4) == test_unsigned >> 4);
  assert(sra(test_int, 4) == test_int >> 4);
  
  assert(srl(test_unsigned, 8) == test_unsigned >> 8);
  assert(sra(test_int, 8) == test_int >> 8);

  unsigned odd1 = 0x2;
  unsigned odd2 = 0x4;
  unsigned odd3 = 0xF;
  unsigned odd4 = 0x1;

  std::cout << "Is odd: " << any_odd_one(odd1) << std::endl;
  std::cout << "Is odd: " << any_odd_one(odd2) << std::endl;
  std::cout << "Is odd: " << any_odd_one(odd3) << std::endl;
  std::cout << "Is odd: " << any_odd_one(odd4) << std::endl;

  std::cout << "Is odd num: " << odd_ones(0x10101011) << std::endl;
  std::cout << "Is odd num: " << odd_ones(0x11110101) << std::endl;

  // q2.66
  std::cout <<std::hex << leftmost_one(0x11110101) << std::endl;
  std::cout <<std::hex << leftmost_one(0xFFFFFFFF) << std::endl;
  std::cout <<std::hex << leftmost_one(0xFF00) << std::endl;
  std::cout <<std::hex << leftmost_one(0x6600) << std::endl;
  std::cout <<std::hex << leftmost_one(0x80000000) << std::endl;
  std::cout <<std::hex << leftmost_one(0x0) << std::endl;

  std::cout << "Is 32 bits int? : " << int_size_is_32() << " " << int_size_is_32_for_16bit() << std::endl;

  return 0;
}

