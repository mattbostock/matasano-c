#include <stdio.h>

int convert_hex_to_decimal(char *hex);

int main(void) {

  // 97 bytes, including trailing null byte
  char hex[98] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  char ascii[49];

  // To represent ASCII, we'll need pairs of hex values
  // Hexadecimal has a radix of 16
  // 16 * 16 = 256 ASCII characters
  //
  // FIXME Handle bad input, i.e. odd-length strings
  int i, j = 0;
  for (i=0; i < sizeof(hex); i = i+2) {
    int a = convert_hex_to_decimal(&hex[i]);
    int b = convert_hex_to_decimal(&hex[i+1]);

    // Most significant byte
    a *= 16;

    ascii[j] = a + b;
    j++;
  }

  printf("%s", ascii);
}

int convert_hex_to_decimal (char *hex) {
  if ('0' <= *hex && *hex <= '9') {
    return *hex - '0';
  }

  if ('a' <= *hex && *hex <= 'z') {
    return *hex - 'a' + 10;
  }

  // FIXME: Handle error
  return 0;
}
