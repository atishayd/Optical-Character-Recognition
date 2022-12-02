#include "digitblob.h"
#include <iostream>
// Add more includes if necessary
#include <vector>

using namespace std;

bool Location::operator<(const Location& other) const
{
    Location lhs = *this;
    if (lhs.col < other.col)
    {
        return true;
    }
    else if (lhs.col > other.col){
      return false;
    }
    else
    {
        if (lhs.row < other.row)
        {
            return true;
        }
    }
  return false;
}

// TO DO - Complete this function
DigitBlob::DigitBlob()
{
    img_ = NULL;
    digit_ = '!'; // dummy value
    bq0_ = bq1_ = bq2_ = bq3_ = bq4_ = bqd_ = 0;
    euler_ = -2;

    // ul_'s Location default constructor already initializes it to -1,-1

    // Initilaize h_ and w_ and any other data members
    h_ = 0;
    w_ = 0;
    verticalSymmetry_ = 0;
    horizontalSymmetry_ = 0;
    verticalCentroid_ = 0;
    horizontalCentroid_ = 0;
}
// TO DO - Complete this function
DigitBlob::DigitBlob(uint8_t** img, Location upperleft, int height, int width)
{
    img_ = img;
    digit_ = '!'; // dummy value

    bq0_ = bq1_ = bq2_ = bq3_ = bq4_ = bqd_ = 0;
    euler_ = -2;

    // Initilaize ul_, h_ and w_ and any other data members
    h_ = height;
    w_ = width;
    ul_ = upperleft;

}

// TO DO - Complete this function if necessary
DigitBlob::~DigitBlob()
{
    // Add code if it is necessary

}

// TO DO - Complete this function
void DigitBlob::classify()
{
    calc_bit_quads(); 
    calc_euler_number();
    calc_symmetry();
    calc_centers_of_mass();
    // Call helper functions to calculate features


    // TO DO: use the results of helper functions to calculate features
    //    We suggest starting with the Euler number but you are free to
    //    change our structure   

    if (euler_ == 0)
    {
        if (verticalCentroid_ >= 0.50 && verticalCentroid_ <= 0.57)
        {
            if (horizontalSymmetry_ >= 0.75 && horizontalSymmetry_ <= 0.79)
            {
                if (verticalSymmetry_ >= 0.50 && verticalSymmetry_ <= 0.70)
                {
                    if (horizontalCentroid_ >= 0.42 && horizontalCentroid_ <= 0.46)
                    {
                         digit_ = '6';
                    }
                }
            }

        }
        if(horizontalSymmetry_ >=0.88)
        {
            digit_ = '0';
        }
        if(verticalCentroid_ >= 0.42 && verticalCentroid_ <= 0.48)
        {
            if(horizontalSymmetry_ >= 0.53 && horizontalSymmetry_ <= 0.755)
            {
                if(verticalSymmetry_ >= 0.50 && verticalSymmetry_ <= 0.68)
                {
                    digit_ = '9';
                }
            }
        }
        if (horizontalSymmetry_ >= 0.57 && horizontalSymmetry_ <= 0.59)
        {
            if(verticalSymmetry_ >= 0.70 && verticalSymmetry_ <= 0.780)
        {
            digit_ = '4';
        }
        }
    }
    else if (euler_ == 1)
    {
        if (verticalCentroid_ >= 0.320 && verticalCentroid_ <= 0.390)
        {
            if (horizontalSymmetry_ >= 0.62 && horizontalSymmetry_ <= 0.70)
            {
                if (verticalSymmetry_ >= 0.50 && verticalSymmetry_ <= 0.58)
                {
                    digit_ = '7';
                }
            }
        }
        if (verticalSymmetry_ >= 0.333 && verticalSymmetry_ <= 0.555)
        {
            if (horizontalSymmetry_ >= 0.466 && horizontalSymmetry_ <= 0.710)
            {
                if (verticalCentroid_ >= 0.450 && verticalCentroid_ <= 0.501)
                {
                    digit_ = '5';
                }
            }
        }
        if (verticalCentroid_ >= 0.520 && verticalCentroid_ <= 0.570)
        {
            if (horizontalSymmetry_ >= 0.54 && horizontalSymmetry_ <= 0.56)
            {
                if (horizontalCentroid_ >= 0.60 && horizontalCentroid_ <= 0.64)
                {
                    if (verticalSymmetry_ >= 0.57 && verticalSymmetry_ <= 0.88)
                    {
                        digit_ = '1';
                    }
                }
            }
        }
        if (horizontalSymmetry_ >= 0.53 && horizontalSymmetry_ <= 0.648)
        {
            if (verticalSymmetry_ >= 0.60 && verticalSymmetry_ <= 0.890)
            {
                digit_ = '3';
            }
        }
        if (verticalCentroid_ >= 0.530 && verticalCentroid_ <= 0.539)
        {
            if (verticalSymmetry_ >= 0.600 && verticalSymmetry_ <= 0.630)
            {
                if(horizontalSymmetry_ >= 0.70 && horizontalSymmetry_ <= 0.72)
                {
                    digit_ = '2';
                }
            }
        }
        
    }
    else
    {
        digit_ = '8';
    }
    

    getClassification();
}

// Complete - Do not alter
char DigitBlob::getClassification() const
{
    return digit_;
}

// TO DO - Complete this function
void DigitBlob::printClassificationResults() const
{
    cout << "Digit blob at " << ul_.row << "," << ul_.col << " h=" << h_ << " w=" << w_ << endl;
    cout << "Bit quads: 1, 2, D, 3, 4:";
    cout << " " << bq1_ << " " << bq2_ << " " << bqd_;
    cout << " " << bq3_ << " " << bq4_ << endl;
    cout << "Euler number is " << euler_ << endl;
    // TO DO: Add any other couts to print classification test data
    cout << "Vertical Center: " << verticalCentroid_ << endl;
    cout << "Horizontal Center: " << horizontalCentroid_ << endl;
    cout << "Vertical Symmetry: " << verticalSymmetry_ << endl;
    cout << "Horizontal Symmetry: " << horizontalSymmetry_ << endl;
    cout << "Percentage Vertical Symmetry: " << verticalSymmetry_*100 << "%"<< endl;
    cout << "Percentage Horizontal Symmetry: " << horizontalSymmetry_*100 << "%" << endl;
    cout << "****Classified as: " << digit_ << "\n\n" << endl;

}

// Complete - Do not alter
const Location& DigitBlob::getUpperLeft() const
{
    return ul_;
}

// Complete - Do not alter
int DigitBlob::getHeight() const
{
    return h_;
}

// Complete - Do not alter
int DigitBlob::getWidth() const
{
    return w_;
}

// Complete - Do not alter
bool DigitBlob::operator<(const DigitBlob& other)
{
    // Use Location's operator< for DigitBlob operator<
    return ul_ < other.ul_;
}

// Complete - Do not alter
void DigitBlob::calc_euler_number()
{
    euler_ = (bq1_ - bq3_ - 2*bqd_) / 4;
}

void DigitBlob::calc_centers_of_mass()
{
    //Horizontal
    double blackCount = 0;
    double verticalSum = 0;
    double horizontalSum = 0;
    for (int i = 0; i < h_; i++)
    {
        for (int j = 0; j < w_; j++)
        {
            if (img_[i+ul_.row][j+ul_.col] == 0)
            {
                blackCount++;
                verticalSum += i;
                horizontalSum += j;
            } 
        }
    }

    verticalSum/=blackCount;
    horizontalSum/=blackCount;

    verticalSum/=(h_-1);
    horizontalSum/=(w_-1);

    horizontalCentroid_ = horizontalSum;
    verticalCentroid_ = verticalSum;
}

// TO DO - Complete this function to set bq1_, bq2_, etc.
void DigitBlob::calc_bit_quads()
{
    for(int i=ul_.row-1; i < ul_.row + h_ ; i++)
    {
        for(int j=ul_.col-1; j < ul_.col + w_ ; j++)
        {
            int blackCount = 0;
            if(img_[i][j] == 0)
            {
                blackCount++;
            }
            if(img_[i][j+1] == 0)
            {
                blackCount++;
            }
            if(img_[i+1][j] == 0)
            {
                blackCount++;
            }
            if(img_[i+1][j+1] == 0)
            {
                blackCount++;
            }

            if (blackCount == 0)
            {
                bq0_++;
            }
            if (blackCount == 1)
            {
                bq1_++;
            }
            if (blackCount == 2)
            {
                if(img_[i][j] == 0 && img_[i+1][j+1] == 0)
                {
                    bqd_++;
                }
                else if (img_[i+1][j] == 0 && img_[i][j+1] == 0)
                {
                    bqd_++;
                }
                else
                {
                    bq2_++;
                }
            }
            if (blackCount == 3)
            {
                bq3_++;
            }
            if (blackCount == 4)
            {
                bq4_++;
            }
        }
    }
}

void DigitBlob::calc_symmetry()
{
    //Vertical
    double verticalCount=0;
    double horizontalCount=0;
    double size = 0;
    for (int i = 0 ; i < h_/2; i++)
    {
        for (int j = 0; j < w_; j++)
        {
            if (img_[i+ul_.row][j+ul_.col] == img_[ul_.row+h_-i-1][j+ul_.col]) 
            {
                verticalCount++;
            }
        }
    }
    for(int i = 0; i < h_; i++)
    {
        for(int j = 0; j < w_/2; j++)
        {
            if (img_[i+ul_.row][j+ul_.col] == img_[i+ul_.row][ul_.col+w_-j-1]) 
            {
                horizontalCount++;
            } 
        }
    }
    size = (h_*w_)/2.0;
    horizontalSymmetry_ = horizontalCount/size;
    verticalSymmetry_ = verticalCount/size;
}

// Add more private helper function implementations below

