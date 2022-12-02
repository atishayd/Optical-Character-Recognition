#ifndef BIGINT_H
#define BIGINT_H
#include <string>
#include <vector>

class BigInt {
public:
    BigInt(std::string s, int base=10); // convert string to BigInt
    std::string to_string() const; // get string representation
    void add(BigInt b); // add another BigInt to this one
    void sub(BigInt b); // subtract another BigInt to this one
    BigInt operator+(const BigInt& rhs);
    BigInt operator-(const BigInt& rhs);
    bool operator<(const BigInt& rhs);

    
private:
    std::vector<int> vec;
    int bases;
    void removeLeadingZeroes();
};

#endif
