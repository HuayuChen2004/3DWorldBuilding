#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>

std::vector<double> ExtractNumbers(const std::string& input) {
    std::vector<double> numbers;
    std::string trimmedInput = input;

    // 去除前后的括号和空格
    trimmedInput.erase(trimmedInput.begin(), std::find_if(trimmedInput.begin(), trimmedInput.end(), [](unsigned char ch) {
        return !std::isspace(ch) && ch != '(';
    }));
    trimmedInput.erase(std::find_if(trimmedInput.rbegin(), trimmedInput.rend(), [](unsigned char ch) {
        return !std::isspace(ch) && ch != ')';
    }).base(), trimmedInput.end());

    std::istringstream iss(trimmedInput);
    std::string token;

    while (iss) {
        if (iss.peek() == ' ' || iss.peek() == ',') {
            iss.get(); // 跳过分隔符
            continue;
        }

        if (iss >> token) {
            // 去除 token 前后的空格
            token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
            token.erase(std::find_if(token.rbegin(), token.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), token.end());

            if (token.empty()) {
                throw std::invalid_argument("Empty number found.");
            }
            try {
                double num = std::stod(token);
                numbers.push_back(num);
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid number format.");
            }
        }
    }

    return numbers;
}

int main() {
    try {
        std::string input = "1.2 3.4 5.6";
        std::vector<double> nums = ExtractNumbers(input);
        for (double num : nums) {
            std::cout << num << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
