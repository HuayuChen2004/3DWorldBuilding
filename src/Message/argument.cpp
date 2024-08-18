// [file name] : argument.cpp
// [function] : implement the Argument class
// [author] : Huayu Chen
// [date] : 2024/8/3

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add implementation of the Argument class
// reason: to support storing the arguments passed 
//         from the viewer to the controller


#include "argument.hpp"
#include <string>
#include <vector>

using namespace std;

// -----------------------------------------------------------
// [name] : Argument
// [function] : constructor of the Argument class
// [input] : a key of class ArgumentKey and a vector of strings
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Argument::Argument(ArgumentKey key, vector<string> values) : 
                m_key(key), m_values(values) {}

// -----------------------------------------------------------
// [name] : GetKey
// [function] : get the key of the argument
// [input] : none
// [output] : the key of the argument
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Argument::ArgumentKey Argument::GetKey() const
{
    ArgumentKey key = m_key;
    return key;
}

// -----------------------------------------------------------
// [name] : GetValues
// [function] : get the values of the argument
// [input] : none
// [output] : a copy of the values of the argument
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
vector<string> Argument::GetValues() const
{
    vector<string> valuesCopy = m_values;
    return valuesCopy;
}

// -----------------------------------------------------------
// [name] : ~Argument
// [function] : virtual destructor of the Argument class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Argument::~Argument() {}