#include <iostream>
#include "bigint.h"

using namespace std;

BigInt::BigInt(std::string s, int base) //Constructor
{
    bases = base; //initialize data member
    for (int i = s.length()-1; i >= 0; i--) //loop through entire string
    {
        char c = s[i]; // assign char c to the particular ith index of array
        
        if (static_cast<int>(c) - '0' <10) // if c < 10
        {
            int x = static_cast<int>(c) - '0';
            vec.push_back(x);
        }
        // else
        // {
        //     int y = 10 + static_cast<int>(c) - 'A';
        //     vec.push_back(y);
        // }
        
    }
    removeLeadingZeroes();
    // convert string to BigInt

}
std::string BigInt::to_string() const
{
    // get string representation
    string temp = "";
    for (int i = vec.size()-1; i >= 0; i--)
    {
        char c = vec[i];
        if (static_cast<int>(c) - '0' <10)
        {
          temp+=static_cast<int>(c) + '0';
        }
    }
    return temp;
}

void BigInt::removeLeadingZeroes() 
{
  for (unsigned int i = 0; i < vec.size(); i++)
  {
    if (vec.back() == 0 && vec.size() > 1)
    {
      vec.pop_back();
    }
  }
}

void BigInt::add(BigInt x)
{
    // add another BigInt to this one
    
    int carry = 0; // what is carried
    int num = 0; // variable used to push back modulus of result later
    
    // if first row = second row in size
    if(x.vec.size() == vec.size())
    {
      //loop through the entire vec, add each specific index bigint
        for (unsigned int i = 0; i <= vec.size()-1; i++)
        {
          // actual addition of numbers
            int result = x.vec[i]+vec[i];
            //if result > base-1, for example: >9 in base 10, we carry 1
            if (result > bases-1) 
            {
                carry = 1;
            }
            //otherwise, our addition does not require a carry
            else
            {
                carry = 0;
            }
            //take the modulus of our result by the base giving you num.
            num = result%bases;
            //copy num (result of our addition) into the ith index of vec.
            vec[i] = num;
        }
        
        //within our givin sum, if carry !=0, means carry = 1,
        //so push back carry.
        if(carry != 0)
        {
            vec.push_back(carry);
        }
    }
    //else if first number > second number
    else if (vec.size() > x.vec.size())
    {
      // while their sizes aren't equal, populate with zeros
        while(x.vec.size() != vec.size())
        {
            x.vec.push_back(0);
        }
        //loop through the vec
        for (unsigned int i = 0; i <= vec.size()-1; i++)
        {
          //set reuslt to equal the first, second and carry addition
            int result = x.vec[i]+vec[i]+carry;
            //if result is > bases, push back another carry to next index
            if (result > bases-1)
            {
                carry = 1;
            }
            //else, nothing to carry, more of a sanity check.
            else
            {
                carry = 0;
            }
            vec[i] = result%bases;
        }
        
        //essentially, if carry is anything but 0 (1) then push_back
        if(carry != 0)
        {
            vec.push_back(carry);
        }
    }
    //if second number > first number
    else if (x.vec.size() > vec.size())
    {
      //while they aren't equal, populate with zeros
        while(vec.size() != x.vec.size())
        {
            vec.push_back(0);
        }
        //loop through the entire vec, add the numbers (individual indexes)
        for (unsigned int i = 0; i <= vec.size()-1; i++)
        {
          // result  is the first, second and carry summed up
            int result = x.vec[i]+vec[i]+carry;
            if (result > bases-1)
            {
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            vec[i] = result%bases;
        }
        if(carry != 0)
        {
            vec.push_back(carry);
        }
    }
    
}

void BigInt::sub(BigInt x)
{
  // subtract another BigInt to this one
  
    // if first row > second row in size
    if(x.vec.size() < vec.size())
    {
      while (x.vec.size() != vec.size())
      {
        x.vec.push_back(0);
      }
    }
 
for (unsigned int i = 0; i < vec.size(); i++)
{
    if (vec[i] < x.vec[i])
    {
      vec[i+1]--;
      vec[i] = (vec[i]+10)-x.vec[i];
      //cout << "hi" << vec[i] << endl;
    }
    else
    {
      vec[i] = (vec[i]-x.vec[i]);
    }
}

}

BigInt BigInt::operator+(const BigInt& rhs)
{
  BigInt b1 = *this;
  b1.add(rhs);
  return b1;
}

BigInt BigInt::operator-(const BigInt& rhs)
{
  BigInt b1 = *this;
  b1.sub(rhs);
  b1.removeLeadingZeroes();
  return b1;
}

bool BigInt::operator<(const BigInt& rhs)
{
  BigInt b1 = *this;

  if (b1.vec.size() < rhs.vec.size())
  {
    return true;
  }
  else if (b1.vec.size() > rhs.vec.size())
  {
    return false;
  }
  else if (b1.vec.size() == rhs.vec.size())
  {
    if(b1.vec.back() < rhs.vec.back())
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return true;
}




