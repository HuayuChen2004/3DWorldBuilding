//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//更改记录
//
//
//
//
//
//
#include "point.hpp"


#include <exception>
#include <stdexcept>

using namespace std;

//
//
//
double Point::At(unsigned int index) const
{
    // Check index
    if (index <= MIN_DIM)
    {
        throw out_of_range("Index should be greater than 0.");
    }
    if (index > m_uiDim)
    {
        throw out_of_range("Index should be less than or equal to dimension.");
    }
    // Return the value at the index
    try {
        // index - 1 because the input index starts from 1,
        // but the array index starts from 0.
        return m_vdCoords.at(index - 1);
    } 
    catch (exception& e) {
        throw e;
    }
    
}
//
//
//
double Point::operator[](unsigned int index) const
{
    return At(index);
}

//
//
//
