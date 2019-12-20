#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string cur;
        vector<string> result;
        //gen_all(cur, 2*n, 0, result);
        backtrace(cur, n, 0, 0, result);
        return result;
    }

    void backtrace(string cur, int n, int open, int close, vector<string> &result) {
        if(cur.size() == 2 * n) {
            result.push_back(cur);
        } else {
            if(open < n)
                backtrace(cur + "(", n, open + 1, close, result);
            if(close < open)
                backtrace(cur + ")", n, open, close + 1, result);
        }
    }

    void gen_all(string cur, int n, int pos, vector<string>& result) {
        if(n == pos) {
            if(valid(cur))
                result.push_back(cur);
        } else {
            cur += "(";
            gen_all(cur, n, pos + 1, result);
            cur.replace(pos, 1, ")");
            gen_all(cur, n, pos + 1, result);
        }
    }
    void show(vector<string> result) {
        for(auto i : result)
            cout << i << endl;
    }
    int valid(string str) {
        int cnt = 0;
        for(auto i : str) {
            if(i == '('){
                cnt++;
            } else {
                cnt--;
            }
            if(cnt < 0)
                return 0;
        }
        if(cnt == 0)
            return 1;
        else
            return 0;
    }
};


int main()
{
    Solution sl;
    vector<string> ret = sl.generateParenthesis(3);
    sl.show(ret);

    return 0;
}
