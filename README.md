# BigIntegerCpp

This project is an exercise in implementing a C++ library. The C++ language supports integers upto 9,223,372,036,854,775,807 using the long long type if the compiler implements it as 8 bytes. This library provides methods to perform mathematical operations upon integers larger than that, limited only by the memory provided by the system. This is also known as __infinite precision arithmetic__ or __arbitrary-precision arithmetic__.

The library stores numbers as a class with the magnitude as a string and the sign as a boolean, and algorithms are implemented to handle common arithmetic operations upon them.