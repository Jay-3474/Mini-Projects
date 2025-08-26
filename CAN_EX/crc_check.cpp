#include "crc_check.hpp"

int Decimal_to_Binary(int decimal)
{
  // binary value
  ull binary = 0;
  // counter
  int count = 0;
  // remainder variable
  int rem = 0;
  while (decimal != 0)
  {
    // perform modulo operation
    rem = decimal % 2;
    // compute power of 10
    ull tmp = pow(10, count);
    // add result to compute the binary number
    binary += rem * tmp;
    // divide the decimal by 2
    decimal /= 2;
    // increment count
    count++;
  }
  return binary;
}

lli Binary_to_Decimal(char binary[])
{
  lli decimal = 0;
  // Use bit shifting with 1 to compute the number
  // sum the numbers to get the decimal equivalent
  for (int i = 0; i < strlen(binary); i++)
  {
    if (binary[i] == '1')
      decimal += 1 << (strlen(binary) - i - 1);
  }
  return decimal;
}

// function to compute CRC and codeword
void CRC(char data[], char gen_poly[])
{
  // length of the generator polynomial
  int length_gen = strlen(gen_poly);
  // convert generator polynomial from binary to decimal
  lli generator_dec = Binary_to_Decimal(gen_poly);
  // Convert data from binary to decimal
  lli data_dec = Binary_to_Decimal(data);
  // Shift n-1 bits to the left in data to append zeros
  lli dividend = data_dec << (length_gen - 1);
  // find the number of bits to shift for further computation.
  int shift_bits = (int)ceill(log2l(dividend + 1)) - length_gen;
  // initialize variable for CRC or check value
  lli check_value;
  // loop to find the check_value or CRC
  while ((dividend >= generator_dec) || (shift_bits >= 0))
  {
    // take the first four bits of the data
    // perform XOR with the generator polynomial
    check_value = (dividend >> shift_bits) ^ generator_dec;
    // find the remainder of the operation
    dividend = (dividend & ((1 << shift_bits) - 1)) | (check_value << shift_bits);
    // compute the number of bits to shift again
    shift_bits = (int)ceill(log2l(dividend + 1)) - length_gen;
  }
  // append the check value with the data
  lli final_data = (data_dec << (length_gen - 1)) | dividend;
  // convert the decimal value to binary
  printf("Check value or CRC: %d\n", Decimal_to_Binary(dividend));
  // print the data to be transmitted
  printf("Data to be sent:  %d", Decimal_to_Binary(final_data));
}
