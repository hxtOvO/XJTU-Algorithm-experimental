#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<string> load_file(string file_path) {
    vector<string> result;
    freopen(file_path.c_str(), "r", stdin);
    string temp;
    while (getline(cin, temp)) {
        result.push_back(temp);
    }
    fclose(stdin);
    cin.clear();
    return result;
}

bool compare_str(string str1, string str2) {
    int end1 = str1.size() - 1, end2 = str2.size() - 1;
    while (end1 > 0 && (str1[end1] == ' ' || str1[end1] == '\t')) {
        end1--;
    }
    while (end2 > 0 && (str2[end2] == ' ' || str2[end2] == '\t')) {
        end2--;
    }
    if (end1 != end2) return false;
    for (int i = 0; i <= end1; i++) {
        if (str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

void compare(string result_path, string compare_path) {
    vector<string> result_lines = load_file(result_path);
    vector<string> compare_lines = load_file(compare_path);
    int i = 0, j = 0, len1 = result_lines.size(), len2 = compare_lines.size();
    if (len1 != len2) {
        cout << "check failed with unequal lines\n";
        cout << "origin lines: " << len1 << endl;
        cout << "compare lines: " << len2 << endl;
        return ;
    }
    for (int i = 0; i < len1; i++) {
        if (!compare_str(result_lines[i], compare_lines[i])) {
            cout << "check failed...\n";
            cout << "origin output is: " << result_lines[i] << endl;
            cout << "compare output is: " << compare_lines[i] << endl;
            return ;
        }
    }
    cout << "check passed\n";
}

int main() {
    string result_path = "./exp3_out.txt";
    string compare_path = "./exp3_out1.txt";
    compare(result_path, compare_path);
    
    return 0;
}
