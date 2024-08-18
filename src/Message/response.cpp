// [file name] : response.cpp
// [function] : implement the Response class
// [author] : Huayu Chen
// [date] : 2024/8/3

// [edit history] :
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: add implementation of the Response class
// reason: to support storing the response from the controller
//         to the viewer
// -----------------------------------------------------------


#include "response.hpp"
#include <string>
#include <vector>

using namespace std;

// -----------------------------------------------------------
// [name] : Response
// [function] : constructor of the Response class
// [input] : a key of class ResponseKey and a vector of strings
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Response::Response(ResponseKey key, vector<string> values) : 
                m_key(key), m_values(values) {}

// -----------------------------------------------------------
// [name] : GetKey
// [function] : get the key of the response
// [input] : none
// [output] : the key of the response
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Response::ResponseKey Response::GetKey() const
{
    ResponseKey key = m_key;
    return key;
}

// -----------------------------------------------------------
// [name] : GetValues
// [function] : get the values of the response
// [input] : none
// [output] : a copy of the values of the response
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
vector<string> Response::GetValues() const
{
    vector<string> valuesCopy = m_values;
    return valuesCopy;
}

// -----------------------------------------------------------
// [name] : ~Response
// [function] : virtual destructor of the Response class
// [input] : none
// [output] : none
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------
Response::~Response() {}
