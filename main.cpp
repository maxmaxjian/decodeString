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
#include <algorithm>

using std::string;
using std::vector;

class solution {
  public:
    string decodeString(const string & s) {
      string result;
      if (s.empty())
	result = s;
      else {
	auto left = split(s,"\\[");
	// std::for_each(left.begin(), left.end(), [](int i){std::cout << i << " ";});
	// std::cout << std::endl;

	if (!left.empty()) {	
	  auto right = split(s,"\\]");
	  // auto right = split_right(s);
	  // std::for_each(right.begin(), right.end(), [](int i){std::cout << i << " ";});
	  // std::cout << std::endl;

	  // if (right.size() == 1) {
	  //   std::cout << s.substr(0, left[0]) << std::endl;
	  //   int num = std::stoi(s.substr(0,left[0]));
	  //   string temp = decodeString(s.substr(left[0]+2, right[0]-left[0]-2));
	  //   while (num-- > 0)
	  //     result.append(temp);
	  // }
	  // else {
	    vector<std::pair<size_t,size_t>> intv;
	    size_t begin = left[0];
	    while (true) {
	      auto end = std::upper_bound(right.begin(), right.end(), begin);
	      while (std::count_if(left.begin(), left.end(), myFunctor(*end)) != std::count_if(right.begin(), right.end(), myFunctor(*end))) {
		++end;
	      }
	      intv.push_back(std::make_pair(begin-1, *end));
	      std::cout << "(" << begin << "," << *end << ")";
	      auto it = std::upper_bound(left.begin(), left.end(), *end);
	      if (it != left.end())
		begin = *it;
	      else
		break;
	    }
	    std::cout << std::endl;

	    vector<string> substrs;
	    for (size_t i = 0; i < intv.size(); ++i) {
	      if (i == 0) {
		if (intv[i].first > 0)
		  substrs.push_back(s.substr(0, intv[i].first));
		substrs.push_back(s.substr(intv[i].first, intv[i].second-intv[i].first+1));
	      }
	      else {
		if (intv[i-1].second != intv[i].first-1) {
		  substrs.push_back(s.substr(intv[i-1].second+1, intv[i].first-intv[i-1].second));
		}
		substrs.push_back(s.substr(intv[i].first, intv[i].second-intv[i].first+1));
	      }
	      if (i == intv.size()-1) {
		if (intv[i].second != s.size()-1)
		  substrs.push_back(s.substr(intv[i].second+1));
	      }
	    }
	    std::for_each(substrs.begin(), substrs.end(), [](const string & str){std::cout << str << " ";});
	    std::cout << std::endl;

	    if (substrs.size() == 1) {
	      std::cout << s.substr(0, left.front()) << std::endl;
	      int num = std::stoi(s.substr(0, left.front()));
	      string temp = decodeString(s.substr(left.front()+2, right.back()-left.front()-2));
	      while (num-- > 0)
		result.append(temp);
	    }
	    else {
	      for (auto str : substrs)
		result.append(decodeString(str));
	    // }
	  }
	}
	else {
	  result = s;
	}
      }

      return result;
    }

  private:
  
  class myFunctor {
  private:
    size_t myval;
  public:
    myFunctor(size_t val) : myval(val) {}
    
    bool operator()(size_t v) {
      return v <= myval;
    }
  };
  
  vector<size_t> split(const string & s, const string & p) {
        string str = s;
        vector<size_t> result;
        std::smatch m;
        // std::regex exp("\\d\\[[a-z]*");
	// std::regex exp("\\]");
	std::regex exp(p);

        while (std::regex_search(str, m, exp)) {
            for (auto x : m) {
	      if (result.empty())
		result.push_back(str.find(x));
	      else
		result.push_back(result.back()+1+str.find(x));
	      // std::cout << x << " ";
            }
            // std::cout << std::endl;
            str = m.suffix().str();
        }
        
        return result;
    }

  bool isValid() {
    return true;
  }

  // vector<size_t> split_right(const string & s) {
  //   string str = s;
  //   vector<size_t> result;
  //   std::smatch m;
  //   std::regex exp("\\]([a-z]*|\\b)*");

  //   while (std::regex_search(str, m, exp)) {
  //     for (auto x : m) {
  // 	if (result.empty())
  // 	  result.push_back(str.find(x));
  // 	else
  // 	  result.push_back(result.back()+str.find(x));
  // 	std::cout << x << " ";
  //     }
  //     std::cout << std::endl;
  //     str = m.suffix().str();
  //     std::cout << "str = " << str << std::endl;
  //   }
        
  //   return result;
  // }
};

int main() {
    string s{"a3[db5[c]]2[bc]"};

    solution soln;
    string decoded = soln.decodeString(s);
    std::cout << "The decoded string is:\n"
              << decoded << std::endl;
}
