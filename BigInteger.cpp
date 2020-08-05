#include "BigInteger.h"

#include <iostream>
#include <cstdlib>
#include <sstream>
// #include <stdexcept>

BigInt::BigInt(){
    digits = "0";
    sign = false;
};

BigInt::BigInt(std::string n){
    if (isdigit(n[0])){
        digits = n;
        sign = false;
    }
    else{
        digits = n.substr(1);
        sign = (n[0] == '-');
    }
};

BigInt::BigInt(std::string n, bool param_sign){
    digits = n;
    sign = param_sign;
};

BigInt::BigInt(int n){
    std::stringstream ss;
    ss << n;
    ss >> digits;
    if(isdigit(digits[0])){
        sign = false;
    }
    else{
        sign = (digits[0] == '-');
        digits = digits.substr(1);
    }
}