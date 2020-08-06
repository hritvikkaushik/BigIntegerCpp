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

void BigInt::operator = (BigInt b){
	digits = b.digits;
	sign = b.sign;
}

bool BigInt::operator == (BigInt b){
    return equals(*this,b);
}

bool BigInt::operator < (BigInt b){
    return less(*this, b);
}

bool BigInt::operator > (BigInt b){
    return greater(*this, b);
}

bool BigInt:: operator <= (BigInt b){
    return less(*this,b) || equals(*this,b);
}

bool BigInt:: operator >= (BigInt b){
    return greater(*this,b) || equals(*this,b);
}

std::string BigInt::add(std::string n1, std::string n2){
    std::string sum = (n1.length() > n2.length() ? n1: n2);
    char carry = '0';

    if(n1.size() > n2.size())
        n2.insert(0, n1.size()-n2.size(), '0');
    else
        n1.insert(0, n2.size()-n1.size(), '0');

    for (int i=n1.size()-1; i>=0; i--){
        sum[i] = (carry - '0') + (n1[i] - '0') + (n2[i] - '0') + '0';

        if(i!=0){
            if(sum[i] > '9'){
                sum[i] -= 10;
                carry = '1';
            } else {
                carry = '0';
            }
        }

    }

    if(sum[0]>'9'){
        sum[0] -= 10;
        sum.insert(0,1,'1');
    }

    return sum;
}

std::string BigInt::subtract(std::string n1, std::string n2) {
    std::string difference = (n1.length()>n2.length())? n1 : n2;

    if(n1.size() > n2.size())
        n2.insert(0, n1.size()-n2.size(), '0');

    else
        n1.insert(0, n2.size()-n1.size(), '0');

    for(int i=n1.length()-1; i>=0; --i) {
        if(n1[i] < n2[i]) {
            n1[i] += 10;
            n1[i-1]--;
        }
        difference[i] = ((n1[i]-'0')-(n2[i]-'0')) + '0';
    }

    while(difference[0]=='0' && difference.length()!=1) // remove leading zeros
        difference.erase(0,1);

    return difference;
}

BigInt BigInt::absolute(){
	return BigInt( digits ); // +ve by default
}

bool BigInt::equals( BigInt &n1, BigInt &n2){
	return n1.digits == n2.digits && n1.sign == n2.sign;
}

bool BigInt::less(BigInt &n1, BigInt &n2){
	bool sign1 = n1.sign;
	bool sign2 = n2.sign;

	if(sign1 && ! sign2) // if n1 is -ve and n2 is +ve
		return true;

	else if(! sign1 && sign2)
		return false;

	else if(! sign1) {// both +ve
		if(n1.digits.length() < n2.digits.length() )
			return true;
		if(n1.digits.length() > n2.digits.length() )
			return false;
		return n1.digits < n2.digits;
	}
	else{ // both -ve

		if(n1.digits.length() > n2.digits.length())
			return true;
		if(n1.digits.length() < n2.digits.length())
			return false;
		return n1.digits.compare( n2.digits ) > 0;
	}
}

bool BigInt::greater (BigInt &n1, BigInt &n2){
    return !(equals(n1,n2) || less(n1,n2));
}

BigInt BigInt::operator + (BigInt b) {
    BigInt sum;
    if( this->sign == b.sign ) { // Same sign
        sum.digits = add(this->digits, b.digits);
        sum.sign = this->sign;
    } else { // Different signs
        if( absolute() > b.absolute() ) {
            sum.digits = subtract(digits, b.digits );
            sum.sign = sign;
        } else {
            sum.digits = subtract(b.digits, digits );
            sum.sign = b.sign;
        }
    }
    if(sum.digits == "0") // avoid (-0) problem
        sum.sign = false;

    return sum;
}

BigInt BigInt::operator - (BigInt b){
	b.sign = ! b.sign;
	return (*this) + b;
}

BigInt& BigInt::operator ++() { // prefix
	(*this) = (*this) + 1;
	return (*this);
}

BigInt BigInt::operator ++(int) { // postfix
	BigInt temp = (*this);
	(*this) = (*this) + 1;
	return temp;
}

BigInt& BigInt::operator --() {// prefix
	(*this) = (*this) - 1;
	return (*this);

}

BigInt BigInt::operator --(int) {// postfix	
	BigInt temp = (*this);
	(*this) = (*this) - 1;
	return temp;
}

