#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <regex>

namespace fs = std::filesystem;
using namespace std;

// 辅助函数：从文件夹名称中提取数字以便排序
int extractNumber(const string& s) {
    regex re("\\d+"); // 匹配连续数字
    smatch match;
    if (regex_search(s, match, re)) {
        return stoi(match.str());
    }
    return 0; // 如果没找到数字，默认排在前面
}

int main() {
    // 路径配置
    string txtPath = "D:/software/calibre/Calibre Portable/Calibre Library/01112/hello.txt";
    string folderPath = "D:/software/calibre/Calibre Portable/Calibre Library/01112";

    // 1. 提取集合A (hello.txt 的行内容)
    vector<string> listA;
    ifstream file(txtPath);
    if (!file.is_open()) {
        cerr << "无法打开文本文件！" << endl;
        return 1;
    }
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            listA.push_back(line);
        }
    }
    file.close();

    // 2. 获取所有文件夹并排序
    vector<fs::path> folders;
    try {
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_directory()) {
                folders.push_back(entry.path());
            }
        }
    }
    catch (const exception& e) {
        cerr << "路径访问错误: " << e.what() << endl;
        return 1;
    }

    // 按名称中的数字进行排序
    sort(folders.begin(), folders.end(), [](const fs::path& a, const fs::path& b) {
        return extractNumber(a.filename().string()) < extractNumber(b.filename().string());
        });

    // 3. 校验数量并重命名
    if (folders.size() != listA.size()) {
        cout << "警告：文件夹数量(" << folders.size() << ") 与 文件行数(" << listA.size() << ") 不匹配！" << endl;
        cout << "是否继续处理较短的一方？(y/n): ";
        char choice; cin >> choice;
        if (choice != 'y') return 0;
    }

    size_t count = min(folders.size(), listA.size());
    for (size_t i = 0; i < count; ++i) {
        string oldName = folders[i].filename().string();
        string suffix = listA[i];

        // 构建新路径：原路径 + 集合A内容
        // 注意：这里简单的在后面添加，如果需要加空格或下划线可以写成 oldName + "_" + suffix
        fs::path newPath = folders[i].parent_path() / (oldName + "_" + suffix);

        try {
            fs::rename(folders[i], newPath);
            cout << "成功: " << oldName << " -> " << newPath.filename().string() << endl;
        }
        catch (const fs::filesystem_error& e) {
            cerr << "重命名失败: " << oldName << " 原因: " << e.what() << endl;
        }
    }

    cout << "任务完成！" << endl;
    std::cin.get();
    return 0;
}