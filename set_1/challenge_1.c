#include <stdio.h>
#include <stdlib.h>

int convert_hex_to_decimal(char *hex);

int main(void) {

  // 97 bytes, including trailing null byte
  char hex[98] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
  char ascii[sizeof(hex) / 2];

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

  printf("%s\n", ascii);

  char base64[65];

  int di, si = 0;
  int n = ((sizeof(ascii) - 1) / 3) * 3;
  char encode_std[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  // Cribbed from: https://golang.org/src/encoding/base64/base64.go?s=2843:2887#L83
  while (si < n) {
    int val = ascii[si + 0] << 16 | ascii[si + 1] << 8 | ascii[si + 2];

    base64[di + 0] = encode_std[val >> 18&0x3F];
    base64[di + 1] = encode_std[val >> 12&0x3F];
    base64[di + 2] = encode_std[val >> 6&0x3F];
    base64[di + 3] = encode_std[val &0x3F];

    si += 3;
    di += 4;
  }

  // FIXME Handle padding

  printf("%s\n", base64);
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
