// this is the implementation file for the Argument class
// this class is used to store the arguments passed from the 
// viewer to the controller
// the arguments are stored as a key-value pair, where the key is the 
// argument name and the value is a vector of strings
// the key is an enum class that defines all the possible argument names
// the values are the actual values passed for that argument
// edit logging:
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add implementation of the Argument class
// reason: to support storing the arguments passed 
//         from the viewer to the controller


#include "argument.hpp"

using namespace std;






Argument::Argument(ArgumentKey key, vector<string> values) : 
                m_key(key), m_values(values) {}

Argument::ArgumentKey Argument::GetKey() const
{
    ArgumentKey key = m_key;
    return key;
}

vector<string> Argument::GetValues() const
{
    vector<string> valuesCopy = m_values;
    return valuesCopy;
}