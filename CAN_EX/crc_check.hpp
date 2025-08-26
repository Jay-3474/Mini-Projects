#ifndef crc_check_H_
#define crc_check_H_

#include <stdio.h>
#include <math.h>
#include <string.h>
#define ull unsigned lli
#define lli long long int

int Decimal_to_Binary(int decimal);
lli Binary_to_Decimal(char binary[]);
void CRC(char data[], char gen_poly[]);

#endif  // crc_check_H_
