#include <iostream>
#include <regex>
#include <string>

using namespace std;


int GetIntegerInput(const string& InputString) {
    // 正则表达式匹配前后可以有空格的单个整数，并捕获该整数
    cout << "InputString: " << InputString << endl;
    regex pattern(R"(^(\d)$)");
    smatch match;

    if (regex_match(InputString, match, pattern)) {
        // 提取捕获的数字部分
        string number = match.str(1);
        return stoi(number);
    } else {
        throw invalid_argument("Invalid input");
    }
}

int main(){
    string input;
    cout << "Enter a single digit: ";
    cin >> input;

    try {
        int number = GetIntegerInput(input);
        cout << "You entered: " << number << endl;
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }

    return 0;

}