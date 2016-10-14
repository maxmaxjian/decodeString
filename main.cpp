// #include <iostream>
// #include <string>
// #include <cctype>
// #include <cassert>

// using std::string;

// class solution {
//   public:
//     string decodeString(const string & str) {
//         string result;
//         size_t i = 0;
//         while (i < str.size() && isalpha[str[i]]) {
//             result.append(1, str[i]);
//             i++;
//         }
//         if (i < str.size()) {
//             if (isdigit(str[i])) {
//                 int count = atoi(str[i]);
//                 i++;
//                 string temp = getSubstr(str, i);
//                 string tmp = decodeString(temp);
//                 while (count-- > 0)
//                     result.append(tmp);
//                 i += temp.size()+2;
//                 result.append(decodeString(str.substr(i)));
//             }
//         }
        
//         return result;
//     }

//   private:
//     string getSubstr(const string & str, size_t start) {
//         assert(str[start] == '[');

//         string result;
//         size_t count = 1, i = start+1;
//         while (i < str.size()) {
//             if (count > 0) {
//                 result.append(1, str[i]);
//                 if (str[i] == '[')
//                     count++;
//                 else if (str[i] == ']')
//                     count--;
//                 i++;
//             }
//             else
//                 break;
//         }
//         result.pop_back();
//         return result;
//     }
// };

#include <iostream>
#include <vector>
#include <string>
#include <regex>

using std::string;
using std::vector;

class solution {
  public:
    string decodeString(const string & s) {
        auto temp = split(s);
        return temp[0];
    }

  private:
    vector<string> split(const string & s) {
        string str = s;
        vector<string> result;
        std::smatch m;
        std::regex exp("\\d\\[.*\\]");

        while (std::regex_search(str, m, exp)) {
            for (auto x : m) {
                result.push_back(x);
                std::cout << x << " ";
            }
            std::cout << std::endl;
            str = m.suffix().str();
        }
        
        return result;
    }
};

int main() {
    string s{"a3[d4[a]b5[c]]2[bc]"};

    solution soln;
    string decoded = soln.decodeString(s);
    std::cout << "The decoded string is:\n"
              << decoded << std::endl;
}
