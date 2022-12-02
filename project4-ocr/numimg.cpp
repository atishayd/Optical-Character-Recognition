#include "digitblob.h"
#include "numimg.h"
#include "bmplib.h"
#include <algorithm> // for std::sort
#include <deque>
#include <iomanip>
#include <iostream>

using namespace std;

// TO DO: Complete this function
NumImg::NumImg(const char* bmp_filename)
{
    
    //  Note: readGSBMP dynamically allocates a 2D array
    //    (i.e. array of pointers (1 per row/height) where each
    //    point to an array of unsigned char (uint8_t) pixels)
    
    // TO DO:
    // call readGSBMP to initialize img_, h_, and w_;
    img_ = readGSBMP(bmp_filename, h_, w_);
    // Leave this check
    if(img_ == NULL)
    {
        throw std::logic_error("Could not read input file");
    }
    
    // Convert to Black and White using a fixed threshold
    for(int i =0; i < h_; i++)
    {
        for(int j = 0; j < w_; j++)
        {
            if(img_[i][j] > 150)
            {
                img_[i][j] = 255;
            }
            else
            {
                img_[i][j] = 0;
            }
        }
    }
    
    explored = new bool*[h_];
    
    for (int i = 0; i < h_; i++)
    {
        explored[i] = new bool[w_];
    }
    
    //Setting every element in the grid to false initially
    for (int i = 0; i < h_; i++)
    {
        for (int j = 0; j < w_; j++)
        {
            explored[i][j] = false;
        }
    }
    // Perform any other initialization you need
}

// TO DO: Complete this function
NumImg::~NumImg()
{
    // Add code here if necessary
    for (int i = 0; i < h_; i++ )
    {
        delete [] img_[i];
    }
    
    delete [] img_;
    
    for (int i = 0; i < h_; i++)
    {
        delete [] explored[i];
    }
    delete [] explored;
    
}

// TO DO: Complete this function
size_t NumImg::findAndCreateDigitBlobs()
{
    for (int i = 0; i < h_; i++)
    {
        for (int j = 0; j < w_; j++)
        {
            if ((explored[i][j] == false) && img_[i][j] == 0)
            {
              explored[i][j] = true;
              blobs_.push_back(createDigitBlob(explored, i, j));
            }
        }
    }
    sortDigitBlobs();
    return blobs_.size();
}

// Complete - Do not alter
std::string NumImg::classify(bool withDebug)
{
    std::string res;
    for(size_t i = 0; i < blobs_.size(); i++)
    {
        blobs_[i].classify();
        if(withDebug)
        {
            blobs_[i].printClassificationResults();
        }
        char c = blobs_[i].getClassification();
        res += c;
    }
    return res;
}

// Complete - Do not alter
void NumImg::printBoundingBoxes() const
{
    cout << setw(2) << "i" << setw(6) << "ULRow" << setw(6) << "ULCol" << setw(4) << "Ht." << setw(4) << "Wi." << endl;
    for(size_t i = 0; i < blobs_.size(); i++)
    {
        const DigitBlob& b = blobs_[i];
        cout << setw(2) << i << setw(6) << b.getUpperLeft().row << setw(6) << b.getUpperLeft().col
        << setw(4) << b.getHeight() << setw(4) << b.getWidth()  << endl;
        // cout << "Blob " << i << " ul=(" << b.getUpperLeft().row << "," << b.getUpperLeft().col
        //     << ") h=" << b.getHeight() << " w=" << b.getWidth() << endl;
    }
    
}

// Complete - Do not alter
const DigitBlob& NumImg::getDigitBlob(size_t i) const
{
    if(i >= blobs_.size())
    {
        throw std::out_of_range("Index to getDigitBlob is out of range");
    }
    return blobs_[i];
}

// Complete - Do not alter
size_t NumImg::numDigitBlobs() const
{
    return blobs_.size();
}

// Complete - Do not alter
void NumImg::sortDigitBlobs()
{
    std::sort(blobs_.begin(), blobs_.end());
}

// Complete - Do not alter
void NumImg::drawBoundingBoxesAndSave(const char* filename)
{
    for(size_t i=0; i < blobs_.size(); i++)
    {
        Location ul = blobs_[i].getUpperLeft();
        int h = blobs_[i].getHeight();
        int w = blobs_[i].getWidth();
        for(int i = ul.row-1; i < ul.row + h + 1; i++)
        {
            img_[i][ul.col-1] = 128;
            img_[i][ul.col+w] = 128;
        }
        for(int j = ul.col-1; j < ul.col + w + 1; j++)
        {
            img_[ul.row-1][j] = 128;
            img_[ul.row+h][j] = 128;
        }
    }
    writeGSBMP(filename, img_, h_, w_);
}

// TO DO:
// Add other (helper) function definitions here

DigitBlob NumImg::createDigitBlob(bool** explored, int pr, int pc)
{
    // Arrays to help produce neighbors easily in a loop
    // by encoding the **change** to the current location.
    // Goes in order N, NW, W, SW, S, SE, E, NE
    int neighbor_row[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int neighbor_col[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    
    // Add your code here
    deque<Location> queue;
    Location start;
    start.row = pr;
    start.col = pc;
    queue.push_back(start);
    explored[pr][pc] = 1;
    Location current;
    int maxRow = pr;
    int maxCol = pc;
    int minRow = pr;
    int minCol = pc;
    int height = 0;
    int width = 0;
    Location temp;
    
    while (!queue.empty())
    {
        current = queue.front();
        queue.pop_front();
        
        for (int i = 0; i < 8; i++)
        {
            temp = current;
            temp.row += neighbor_row[i];
            temp.col += neighbor_col[i];
            
            if ((temp.row >= 0) && (temp.col < w_) && (temp.row < h_)
                && (temp.col >= 0) && (explored[temp.row][temp.col] == false)
                && (img_[temp.row][temp.col] == 0))
            {
                explored[temp.row][temp.col] = true;
                queue.push_back(temp);
            }
        }
        
        if (current.row > maxRow)
        {
            maxRow = current.row;
        }
        if (current.col > maxCol)
        {
            maxCol = current.col;
        }
        if (current.row < minRow)
        {
            minRow = current.row;
        }
        if (current.col < minCol)
        {
            minCol = current.col;
        }
        
    }
    height = (maxRow - minRow)+1;
    width = (maxCol - minCol)+1;
    
    Location upperleft;
    upperleft.row = minRow;
    upperleft.col = minCol;
    DigitBlob blob(img_, upperleft, height, width);
    return blob;
}

