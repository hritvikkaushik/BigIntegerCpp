#include "BigInteger.h"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
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

bool BigInt::operator != (BigInt b){
    return !equals(*this,b);
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

BigInt& BigInt::operator += (BigInt b){
	(*this) = (*this) + b;
	return (*this);
}

BigInt& BigInt::operator -= (BigInt b){
	(*this) = (*this) - b;
	return (*this);
}

std::string BigInt::multiply (std::string n1, std::string n2){
    if(n1.length() > n2.length()) 
		n1.swap(n2);

	std::string product = "0";
	for(int i=n1.length()-1; i>=0; --i)
	{
		std::string temp = n2;
		int currentDigit = n1[i]-'0';
		int carry = 0;

		for(int j=temp.length()-1; j>=0; --j)
		{
			temp[j] = ((temp[j]-'0') * currentDigit) + carry;

			if(temp[j] > 9)
			{
				carry = (temp[j]/10);
				temp[j] -= (carry*10);
			}
			else
				carry = 0;

			temp[j] += '0'; // back to string mood
		}

		if(carry > 0)
			temp.insert(0, 1, (carry+'0'));
		
		temp.append((n1.length()-i-1), '0'); // as like productt by 10, 100, 1000, 10000 and so on

		product = add(product, temp); // O(n)
	}

	while(product[0] == '0' && product.length()!=1) // erase leading zeros
		product.erase(0,1);

	return product;
}

std::pair<std::string, long long> BigInt::divide(std::string n, long long den){
	long long rem = 0;
	std::string result; result.resize(10000);
	
	for(int indx=0, len = n.length(); indx<len; ++indx){
		rem = (rem * 10) + (n[indx] - '0');
		result[indx] = rem / den + '0';
		rem %= den;
	}
	result.resize( n.length() );

	while( result[0] == '0' && result.length() != 1)
		result.erase(0,1);

	if(result.length() == 0)
		result = "0";

	return make_pair(result, rem);
}

BigInt BigInt::operator * (BigInt b){
	BigInt product;

	product.digits = multiply(digits, b.digits);
	product.sign = ( sign != b.sign );

	if(product.digits == "0") // avoid (-0) problem
		product.sign = (false);

	return product;
}

//Denominator must be within "long long" range
BigInt BigInt::operator / (BigInt b)
{
	long long den = toInt( b.digits );
	BigInt div;

	div.digits = divide(digits, den).first;
	div.sign= sign != b.sign ;

	if(div.digits == "0") // avoid negative zero
		div.sign=false;

	return div;
}

//Denominator must be within "long long" range
BigInt BigInt::operator % (BigInt b)
{
	long long den = toInt( b.digits );

	BigInt rem;
	long long rem_int = divide(digits, den).second;
	rem.digits = toString(rem_int);
	rem.sign = (this->sign != b.sign );

	if(rem.digits == "0") // avoid negative zero
		rem.sign =false;

	return rem;
}

std::string BigInt::toString(long long n){
	std::stringstream ss;
	std::string temp;

	ss << n;
	ss >> temp;

	return temp;
}

long long BigInt::toInt(std::string s){
	long long sum = 0;

	for(int i=0; i<s.length(); i++)
		sum = (sum*10) + (s[i] - '0');

	return sum;
}