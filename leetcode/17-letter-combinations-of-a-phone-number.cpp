/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** letterCombinations(char * digits, int* returnSize){
    if(strlen(digits) == 0) {
        *returnSize = 0;
        return NULL;
    } 
    int n = 1;
    char *it = digits;
    int *l = (int *)malloc(sizeof(int) * strlen(digits));
    char dic[8] = {'a', 'd', 'g', 'j', 'm', 'p', 't', 'w'};
    int i = 0;
    while(*it) {
        if(*it != '7' && *it != '9') {
            n *= 3;
            l[i++] = 3;
        } else {
            n *= 4;
            l[i++] = 4;
        }
        it++;
    }
    *returnSize = n;
    char **ret = (char **)malloc(sizeof(char *) * n);
    for(i = 0; i < n; i++) {
        ret[i] = (char *)malloc(sizeof(char) * (strlen(digits) + 1));
        memset(ret[i], 0, strlen(digits) + 1);
    }

    i = 0;
    int loop = 1;
    do {
        int repeat = n/l[i];
        int it = 0;
        for(int m = 0; m < loop; m++) { 
            for(int j = 0; j < l[i]; j++) {
                for(int k = 0; k < repeat; k++) {
                    ret[it++][i] = dic[digits[i] - '2'] + j;
                }
            }
        }
        n /= l[i];
        loop *= l[i++];
    } while(n > 1);
    return ret;
}

#include <map>
class Solution {
public:
    map<string, string> dic;
    //dic["1"] = "abc";
    vector<string> ret;
    void backtrack(string comb, string digs) {
        if(digs.length() == 0) {
            ret.push_back(comb);
        } else {
            string dig = digs.substr(0, 1);
            string alps = dic[dig];
            for(int i = 0; i < alps.length(); i++) {
                backtrack(comb + alps.substr(i, 1), digs.substr(1, digs.length() - 1));
            }
        }
    }
    vector<string> letterCombinations(string digits) {
        if(digits.length() == 0)
            return ret
        dic.insert(pair<string, string>("2", "abc"));
        dic.insert(pair<string, string>("3", "def"));
        dic.insert(pair<string, string>("4", "ghi"));
        dic.insert(pair<string, string>("5", "jkl"));
        dic.insert(pair<string, string>("6", "mno"));
        dic.insert(pair<string, string>("7", "pqrs"));
        dic.insert(pair<string, string>("8", "tuv"));
        dic.insert(pair<string, string>("9", "wxyz"));

        backtrack("", digits);
        return ret; 
    }
};
