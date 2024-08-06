// this is the header file for the Response class
// the Response class is used to store the response from the controller
// to the viewer
// the response is stored as a key-value pair, where the key is the
// response name and the value is a vector of strings
// the key is an enum class that defines all the possible response names
// the values are the actual values returned for that response
// edit logging:
// -----------------------------------------------------------
// date: 2024/8/3
// author: Huayu Chen
// edit: init Response class
//       add key-value pair for responses
//       add functions to get key and values
// reason: to support storing the response from the controller
//         to the viewer and provide a way to access the response
//         values from the viewer
// -----------------------------------------------------------


#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string>
#include <vector>

using namespace std;

class Response
{
public:
    enum class ResponseKey {
        EMPTY_PATH,
        NOT_OBJ_PATH,
        NOT_EXIST_PATH,
        IMPORT_SUCCESS,
        EXPORT_SUCCESS,
        DELETE_FACE_SUCCESS,
        ADD_FACE_SUCCESS,
        MODIFY_FACE_POINT_SUCCESS,
        DELETE_LINE_SUCCESS,
        ADD_LINE_SUCCESS,
        MODIFY_LINE_POINT_SUCCESS,
        UNKNOWN,
        EXPORT_FAILED,
        IMPORT_FAILED,
        DISPLAY_ALL_FACES,
        DISPLAY_FACE_POINTS,
        DISPLAY_ALL_LINES,
        DISPLAY_LINE_POINTS,
        DISPLAY_STATISTICS,
    };
    Response(ResponseKey key, vector<string> values);
    virtual ~Response();
    ResponseKey GetKey() const;
    vector<string> GetValues() const;
private:
    ResponseKey m_key;
    vector<string> m_values;
};

#endif // RESPONSE_HPP