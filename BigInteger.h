#include<string>
#include<vector>

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

    void operator = (BigInt b);
    bool operator != (BigInt b);
    bool operator == (BigInt b);
	bool operator > (BigInt b);
	bool operator < (BigInt b);
    bool operator <= (BigInt b);
    bool operator >= (BigInt b);
    BigInt absolute();
    BigInt operator + (BigInt b);
    BigInt operator - (BigInt b);
    BigInt& operator ++();
    BigInt operator ++(int);
	BigInt& operator --(); // prefix
	BigInt  operator --(int); // postfix
    BigInt& operator += (BigInt b);
    BigInt& operator -= (BigInt b);
	BigInt operator * (BigInt b);
	BigInt operator / (BigInt b);
    BigInt operator % (BigInt b);
    BigInt& operator *= (BigInt b);
	BigInt& operator /= (BigInt b);
	BigInt& operator %= (BigInt b);
    
private:

    std::string add (std::string n1, std::string n2);
    std::string subtract (std::string n1, std::string n2);
    std::string multiply(std::string n1, std::string n2);
    std::pair<std::string, long long> divide(std::string n, long long den);
    bool equals (BigInt &n1, BigInt &n2);
    bool less(BigInt &n1, BigInt &n2);
    bool greater (BigInt &n1, BigInt &n2);
    std::string toString(long long n);
	long long toInt(std::string s);
};