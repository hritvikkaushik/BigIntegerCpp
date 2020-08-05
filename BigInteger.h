#include<string>
#include<vector>
// #include<iostream>

class BigInt{

    public:

    std::vector<unsigned char> digits {};  //Store the magniude
    bool sign;      //Store the sign. True => Positive, False => Negative

    BigInt() = default;                 //Default constructior
    BigInt(std::string n);              //constructor to initializ bigint with a long string of digits
    BigInt(const BigInt&) = default;    //Default copy constuctor
    BigInt(BigInt&&) = default;         //Default move constructor
    ~BigInt() = default;                //Default destructor
};