#include<string>
#include<vector>
// #include<iostream>

class BigInt{

    public:

    std::string digits;  //Store the magniude
    bool sign;      //Store the sign. True => Negative, False => Positive

    BigInt();                 //Default constructior
    BigInt(std::string n);
    BigInt(std::string n, bool param_sign);  
    BigInt(int n); 
    BigInt(const BigInt&) = default;    //Default copy constuctor
    BigInt(BigInt&&) = default;         //Default move constructor
    ~BigInt() = default;                //Default destructor
};