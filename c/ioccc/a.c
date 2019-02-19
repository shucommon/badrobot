#include <stdio.h>

#define unix 1

int main() {printf(&unix["\021%six\012\0"], (unix)["have"] + "fun" - 0x60); return 0;}
