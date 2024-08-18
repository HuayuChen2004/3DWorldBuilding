// [file name] : response.hpp
// [function] : declare the class Response
// [author] : Huayu Chen
// [date] : 2024/8/3

// [edit history] :
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

// notes for the Response class
// -----------------------------------------------------------
// [class name] : Response
// [function] : store the response from the controller to the viewer
// [notes on interface] :
// 1. the response is stored as a key-value pair, where the key is the
//    response name and the value is a vector of strings that contains the
//    actual values returned for that response
// 2. the key is an enum class that defines all the possible response names
// 3. there are constant getters to get the key and values
// [author] : Huayu Chen
// [date] : 2024/8/3
// -----------------------------------------------------------

class Response
{
public:
    // notes for the ResponseKey enum class
    // -----------------------------------------------------------
    // [class name] : ResponseKey
    // [function] : define all the possible response names
    // [notes on interface] :
    // 1. the key is an enum class that defines all the possible response names
    //    so there are no member variables or functions
    // 2. some error responses are added to handle invalid arguments 
    //    and runtime errors
    // 3. add new response names if the program needs to support more responses
    // [author] : Huayu Chen
    // [date] : 2024/8/3
    // -----------------------------------------------------------
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
        UNKNOWN_INVALID_ARGUMENT,
        UNKNOWN_RUN_TIME_ERROR,
        ADD_FACE_FAILED,
        MODIFY_FACE_POINT_FAILED,
        DELETE_FACE_FAILED,
        ADD_LINE_FAILED,
        MODIFY_LINE_POINT_FAILED,
        DELETE_LINE_FAILED,
        INDEX_OUT_OF_RANGE,
        DUPLICATE_FACE,
        DUPLICATE_LINE,
        NOT_A_FACE,
        NOT_A_LINE,
        INVALID_NUMBER_FORMAT,
        NOT_A_POINT,
        INPUT_NUMBER_ERROR,
        INVALID_INPUT,
        PARSE_FAILED,
        OPEN_FILE_FAILED,
        NO_MODEL_TO_EXPORT,
        NO_3D_MODEL,
    };
    // constructor, response key: the type of response,
    // values: the values returned for that response
    Response(ResponseKey key, vector<string> values);
    // virtual destructor
    virtual ~Response();
    // getter for the key
    ResponseKey GetKey() const;
    // getter for the values
    vector<string> GetValues() const;
private:
    // private member variables, key and values
    ResponseKey m_key;
    vector<string> m_values;
};

#endif // RESPONSE_HPP