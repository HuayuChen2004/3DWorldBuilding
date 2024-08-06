#include <iostream>
#include <filesystem> // 包含实验性filesystem头文件

namespace fs = std::filesystem; // 使用命名空间别名

int main() {
    fs::path p = "/tmp";
    if (fs::exists(p)) {
        std::cout << "Path exists!" << std::endl;
    } else {
        std::cout << "Path does not exist!" << std::endl;
    }
    return 0;
}
