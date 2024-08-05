// this file contains the implementation of the Response class
// this class is used to store the response from the controller
// to the viewer
// the response is stored as a key-value pair, where the key is the
// response name and the value is a vector of strings
// the key is an enum class that defines all the possible response names
// the values are the actual values returned for that response
// edit logging:
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add implementation of the Response class
// reason: to support storing the response from the controller
//         to the viewer
// -----------------------------------------------------------


#include "response.hpp"

using namespace std;

Response::Response(ResponseKey key, vector<string> values) : 
                m_key(key), m_values(values) {}

Response::ResponseKey Response::GetKey() const
{
    ResponseKey key = m_key;
    return key;
}

vector<string> Response::GetValues() const
{
    vector<string> valuesCopy = m_values;
    return valuesCopy;
}
