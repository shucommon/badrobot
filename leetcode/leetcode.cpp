
#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
#include<iterator>
#include<stack>
#include<string>

#include<map>
#include<set>

using namespace std;

// problem 1
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ret;
        map<int, int> arr;
        for(int i = 0; i < nums.size(); i++) {
            auto f = arr.find(target - nums.at(i));
            if(f != arr.end()) {
                ret.push_back(f->second);
                ret.push_back(i);
                return ret;
            }
            arr[nums.at(i)] = i;
        }
        return ret;
    }
};

// problem 2
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode ln(0);
        ListNode *pl1 = l1;
        ListNode *pl2 = l2;
        ListNode *it = &ln;

        int add = 0;
        while(pl1 && pl2) {
            ListNode *node = new ListNode(0);
            node->next = nullptr;
            node->val = (pl1->val + pl2->val + add) % 10;
            it->next = node;
            it = it->next;
            add = (pl1->val + pl2->val + add)/10;
            pl1 = pl1->next;
            pl2 = pl2->next;
        }
        if(pl1 != nullptr) {
            while(pl1) {
                ListNode *node = new ListNode(0);
                node->next = nullptr;
                node->val = (pl1->val + add) % 10;
                it->next = node;
                it = it->next;
                add = (pl1->val + add)/10;
                pl1 = pl1->next;
            }
        }
        if(pl2 != nullptr) {
            while(pl2) {
                ListNode *node = new ListNode(0);
                node->next = nullptr;
                node->val = (pl2->val + add) % 10;
                it->next = node;
                it = it->next;
                add = (pl2->val + add)/10;
                pl2 = pl2->next;
            }
        }
        if(add){
            ListNode *node = new ListNode(0);
            node->next = nullptr;
            node->val = add;
            it->next = node;
        }
        return ln.next;
    }
};

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        nums1.insert(nums1.begin(), nums2.begin(), nums2.end());
        sort(nums1.begin(), nums1.end());       
        if(nums1.size() % 2 == 0) {
            return (nums1.at(nums1.size() / 2) + nums1.at(nums1.size() / 2 - 1)) / 2;
        }
        return nums1.at(nums1.size()/2);
    }
};

// problem 5400
class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        map<string, string> p;
        for(auto pt : paths) {
            p[pt[0]] = pt[1];
        }
        for(auto m : p) {
            if(p.find(m.second) == p.end()) {
                return m.second;
            }
        }
        return nullptr;
    }
};

// probelm 5401
class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        vector<int>::iterator it = nums.begin();
        while(it != nums.end()) {
            while(it != nums.end() && *it == 0) it++;
            if(it == nums.end()) return true;
            it++;
            if(it == nums.end()) return true;

            int cnt = 0;
            while(it != nums.end() && *it == 0) {
                it++;
                cnt++;
            }
            if(it == nums.end()) return true;
            if(cnt < k) return false;
        }
        return false;
    }

    bool demo_kLengthApart(vector<int>& nums, int k) {
        bool ok = true;
        int L = -1000000;
        for(int i = 0; i < (int)nums.size(); i += 1)if(nums[i] == 1){
            if(i - L <= k) ok = false;
            L = i;
        }
        return ok;
    }
};

// problem 5402
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        multiset<int> ms;
        int j = 0;
        int Max = 0;
        for(int i = 0; i < nums.size(); i++) {
            while(j < nums.size()) {
                ms.insert(nums.at(j));
                copy(ms.begin(), ms.end(), ostream_iterator<int>(cout, " "));
                if(*ms.rbegin() - *ms.begin() > limit) {
                    ms.erase(nums.at(j));
                    Max = max(Max, j - i);
                    break;
                }
                j++;
            }
            if(j == nums.size()) {
                return max(Max, j - i);
            }
            ms.erase(ms.find(nums.at(i)));
        }
        return Max;
    }
};

// problem 5403
class Solution {
public:
    int sum(vector<vector<int>> &mat, vector<int> index) {
        int sum = 0;
        for(int i = 0; i < index.size(); i++) sum += mat[i][index[i]];
        return sum;
    }

    int kthSmallest(vector<vector<int>> &mat, int &k) {
        set<pair<int, vector<int>>> st;
        int m = mat.size(), n = mat[0].size();
        vector<int> vv(m, 0);
        int ksum = 0;
        //pair<int, vector<int>> pr(sum(mat, vector<int>(m, 0)), vector<int>(m, 0));
        //st.insert(pr);
        st.insert({sum(mat, vector<int>(m, 0)), vector<int>(m, 0)});
        for(int i = 0; i < k; i++) {
            auto p = *st.begin();
            st.erase(st.begin());
            ksum = p.first;
            auto v = p.second;
            for(int j = 0; j < m; j++) {
                if(v[j] + 1 < n) {
                    v[j] += 1;
                    //st.insert(pair<int, vector<int>>(sum(mat, v), v));
                    st.insert({sum(mat, v), v});
                    v[j] -= 1;
                }
            }
        }
        return ksum;
    }
};

// problem 5403
class Solution {
public:
    int sum(vector<vector<int>>& mat, const vector<int>& index){
        int res = 0;
        for(int i = 0; i < (int)index.size(); i += 1) res += mat[i][index[i]];
        return res;
    }
    int kthSmallest(vector<vector<int>>& mat, int k) {
        set<pair<int, vector<int>>> sp;
        int m = mat.size(), n = mat[0].size();
        sp.insert({sum(mat, vector<int>(m, 0)), vector<int>(m, 0)});
        int ans = 0;
        for(int i = 0; i < k; i += 1){
            auto p = *sp.begin();
            sp.erase(sp.begin());
            ans = p.first;
            auto v = p.second;
            for(int i = 0; i < m; i += 1) if(v[i] + 1 < n){
                v[i] += 1;
                sp.insert({sum(mat, v), v});
                v[i] -= 1;
            }
        }
        return ans;
    }
};

// problem 136
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        set<int> s;
        for(auto n : nums) {
            if(s.find(n) != s.end()) s.erase(s.find(n));
            else s.insert(n);
        }
        return *s.begin();

        // method 2, xor
        int s = 0;
        for(auto n : nums) {
            s = (s ^ n);
        }
        return s;

    }
};

// problem 190
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t ret = 0, cnt = 32;
        while(cnt) {
            ret = ((ret << 1) | (n % 2));
            n >>= 1;
            cnt--;
        }
        return ret;
    }
};

// problem 191
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt = 0;
        while(n) {
            if(n % 2) cnt++;
            n /= 2;
        }
        return cnt;

        // method 2
        // n & (n - 1) will make last 1 -> 0
        int cnt = 0;
        while(n) {
            cnt++;
            n = (n & (n - 1));
        }
        return n;
    }
};

// problem 709 
class Solution {
public:
    string toLowerCase(string str) {
        for(auto &c : str) {
            tolower(c);
        }
    }
};

// problem 201
class Solution {
public:
    int rangeBitwiseAnd(int m, int n) {
        //0 <= m <= n <= 2147483647
        // m: S S S 0 X X X X
        // n: S S S 1 X X X X
        // first different pos
        if(m == 0) return 0;
        int cnt = 0;
        while(m < n) {
            m >>= 1;
            n >>= 1;
            cnt++;
        }
        m <<= cnt;
        return m;
    }
};

// problem 342
class Solution {
public:
    bool isPowerOfFour(int num) {
       if(num <= 0) return false;
       if((num & (num - 1)) != 0) return false;
       // power 4, 1 will on even pos, 0 in odd pos
       if((num & 0xaaaaaaaa) != 0) return false;
       return true;
       /*
       int cnt = 0;
       while(num && num % 2 == 0) {
           cnt++;
           num /= 2;
       }
       if(cnt % 2 == 0) return true;
       return false;
       */
    }
};

// problem 405
class Solution {
public:
    string toHex(int num) {
        if(num == 0) return "0";
        union {
            int a;
            unsigned char b[4];
        } nm;
        nm.a = num;
        string s;
        string dic = "0123456789abcdef";
        for(int i = 0; i < 4; i++) {
            s.insert(s.begin(), dic[(nm.b[i] & 0xf0) >> 4]);
            s.insert(s.begin(), dic[nm.b[i] & 0xf]);
        }
        while(s.front() == '0') s.erase(s.begin());
        return s;

        // method 2
        if(num == 0) return "0";
        string s;
        string dic = "0123456789abcdef";
        unsigned int n = num > 0 ? num : (unsigned int)num;
        while(n) {
            s.insert(s.begin(), dic[(n % 16)]);
            n = (n - (n % 16)) / 16;
        }
        return s;
    }
};

// problem 461
class Solution {
public:
    int hammingDistance(int x, int y) {
        x = (x ^ y);
        int cnt = 0;
        while(x) {
            cnt++;
            x = (x & (x - 1));
        }
        return cnt;
    }
};

// problem 476
class Solution {
public:
    int findComplement(int num) {
        // method 1
        int n = 0;
        int mask = 1;
        while(num) {
            if(num % 2 == 0) n |= mask;
            mask <<= 1;
            num /= 2;
        }
        return n;


        // method 2
        int n = (num ^ 0xffffffff);
        int mask = 0;
        if((num & 0xffff0000) != 0) {
            num >>= 16;    
            mask = 0xffff;
        }
        if((num & 0xff00) != 0) {
            num >>= 8;    
            mask <<= 8;
            mask |= 0xff;
        }
        if((num & 0xf0) != 0) {
            num >>= 4;    
            mask <<= 4;
            mask |= 0xf;
        }
        if((num & 0xc) != 0) {
            num >>= 2;    
            mask <<= 2;
            mask |= 0x3;
        }
        if((num & 0x2) != 0) {
            num >>= 1;    
            mask <<= 2;
            mask |= 0x3;
        }
        return (n & mask);
    }
};

// problem 3
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
    //abcabcbb
        int m = 0;
        int cnt = 0;
        map<char, int> mp;
        int j = 0;
        for(int i = 0; i < s.length(); i++) {
            for(; j < s.length(); j++) {
                if(mp.find(s[j]) != mp.end()) break;
                mp[s[j]] = j;
                cnt++;
            }
            m = (m > cnt ? m : cnt);
            if(m >= s.length() - i - 1) break;
            cnt--;
            mp.erase(mp.find(s[i]));
        }
        return m;
    }
};

// problem 338
class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> v(1, 0);
        if(num == 0) return v;
        v.push_back(1);
        if(num == 1) return v;
        for(int i = 2; i <= num;) {
            int s = v.size();
            for(int j = 0; j < s; j++) {
                v.push_back(1 + v[j]);
                i++;
                if(i > num) break;
            }
        }
        return v;
    }
};

// problem 5
class Solution {
public:
    string longestPalindrome(string s) {
        int longest = 0;
        int l = 0, r = 0;
        for(int i = 0; i < s.length(); i++) {
            int len1 = subFind(s, i, i);
            int len2 = subFind(s, i, i + 1);
            len1 = max(len1, len2);
            if(longest < len1) {
                longest = len1;
                l = i - (longest - 1) / 2;
                r = i + longest / 2;
            }
        }
        return s.substr(l, r - l + 1);
    }
    int subFind(const string &s, int l, int r) {
        while(l >= 0 && r < s.length() && s[l] == s[r]) {
            l--;
            r++;
        }
        return r - l - 1;
    }
};

// problem 14
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size() == 1) return strs[0];

        string s;
        for(int i = 0; i < strs[0].length(); i++) {
            int j = 1;
            for(; j < strs.size(); j++) {
                if(strs[j][i] != strs[0][i]) break;
            }
            if(j < strs.size()) return s;
            s += strs[0][i];
        }
        return s;
    }
};

// problem 28
class Solution {
public:
    int strStr(string haystack, string needle) {
        // haystack = "hello", needle = "ll"
        if(needle.size() == 0) return 0;
        int hsize = haystack.size();
        int nsize = needle.size();
        for(int i = 0; i < hsize;) {
            int j = 0;
            while(i < hsize && haystack[i] != needle[j]) i++;
            if(hsize - i < nsize) return -1;
            int m = i;
            while(i < hsize && j < nsize && haystack[i] == needle[j]) {
                i++;
                j++;
            }
            if(j == nsize) return i - nsize;
            i = m + 1;
        }        
        return -1;
    }
};

// problem 67 
class Solution {
public:
    string addBinary(string a, string b) {
        // int i = std::stoi("01000101", nullptr, 2);
        // 输入: a = "11", b = "1"
        // 输出: "100"
        // method 1 - lenght limit
        int l1 = std::stoi(a, nullptr, 2);
        int l2 = std::stoi(b, nullptr, 2);
        l1 += l2;
        string s;
        while(l1) {
            s.insert(0, 1, (l1 % 2) + '0');
            l1 /= 2;
        }
        return s;

        // method 2
        int m = a.size() - 1, n = b.size() - 1; 
        string s;
        char add = '0';
        while(m >= 0 && n >= 0) {
            char x = add + a[m] + b[n] - 2 * '0';
            if(x == '2') {
                s.insert(0, 1, '0');
                add = '1';
            } else {
                s.insert(0, 1, x);
                add = '0';
            }
            m--;
            n--;
        }
        while(m >= 0) {
            char x = add + a[m] - '0';
            if(x == '2') {
                s.insert(0, 1, '0');
                add = '1';
            } else {
                s.insert(0, 1, x);
                add = '0';
            }
            m--;
        }
        while(n >= 0) {
            char x = add + b[n] - '0';
            if(x == '2') {
                s.insert(0, 1, '0');
                add = '1';
            } else {
                s.insert(0, 1, x);
                add = '0';
            }
            n--;
        }
        if(add == '1') s.insert(0, 1, add);
        return s;
    }
};

// problem 557
class Solution {
public:
    string reverseWords(string s) {
        // 输入: "Let's take LeetCode contest"
        // 输出: "s'teL ekat edoCteeL tsetnoc" 
        string ss;
        int pos = 0, pos1 = 0;
        for(auto l : s) {
            pos++;
            if(l == ' '){
                ss += ' ';
                pos1 = pos;
            }
            else {
                ss.insert(pos1, 1, l);
            }
        }
        return ss;
    }
};


// problem 151
class Solution {
public:
    string reverseWords(string s) {
        // 输入: "  hello world!  "
        // 输出: "world! hello"
        while(*s.begin() == ' ') s.erase(s.begin());
        string ss;
        for(int i = 0; i < s.length();) {
            string s1;
            while(i < s.length() && s[i] != ' ') {
                s1 += s[i];
                i++;
            }
            ss.insert(0, s1);
            if(i >= s.length()) return ss;
            while(i < s.length() && s[i] == ' ') i++;
            if(i < s.length()) ss.insert(0, 1, ' ');
        }
        return ss;
    }
};

// problem 1441
/*
输入：target = [1,3], n = 3
输出：["Push","Push","Pop","Push"]
解释： 
读取 1 并自动推入数组 -> [1]
读取 2 并自动推入数组，然后删除它 -> [1]
读取 3 并自动推入数组 -> [1,3]
*/
class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> str;
        auto it = target.begin();
        for (int i = 1; i <= n; i++) {
            if (it != target.end() && *it == i) {
                str.push_back("Push");
                it++;
            } else if (it != target.end()) {
                str.push_back("Push");
                str.push_back("Pop");
            }
        }           
        return str;
    }
};

// problem 1442
/*
给你一个整数数组 arr 。

现需要从数组中取三个下标 i、j 和 k ，其中 (0 <= i < j <= k < arr.length) 。

a 和 b 定义如下：

a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
注意：^ 表示 按位异或 操作。

请返回能够令 a == b 成立的三元组 (i, j , k) 的数目。
a ^ a = 0
a ^ !a = ff
a ^ 1 = !a
a ^ 0 = a
*/
class Solution {
public:
    int countTriplets(vector<int>& arr) { int n = arr.size();
        if(n < 2) return 0;

        int a = 0, b = 0, cnt = 0;
        for (int i = 0; i < n - 1; i++) {
            a = arr[i];
            for (int j = i + 1; j < n; j++) {
                if (j > i + 1) a ^= arr[j - 1];
                b = arr[j];
                if(a == b) cnt++;
                for (int k = j + 1; k < n; k++) {
                    b ^= arr[k];
                    if(a == b) cnt++;
                }
            }
        }
        return cnt;
    }
};

class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        multimap<int, int> mp;
        for (auto e : edges) {
            mp.insert(pair<int, int>(e[0], e[1]));
        }
        cnt = 0;
        search(mp, hasApple, edges[0][0]);
        return cnt;
    }
    bool search (multimap<int, int> &mp, vector<bool> &hasApple, int key) {
        auto it = mp.find(key);
        auto n = mp.count(key);
        int curCnt = cnt;
        for (int i = 0; i < n; i++, it++) {
            if (hasApple[it->second]) {
                cnt += 2;
            }
            if (mp.find(it->second) != mp.end()) {
                if (search(mp, hasApple, it->second) && !hasApple[it->second])  cnt += 2;
            }
        }
        if (curCnt != cnt) return true;
        return false;
    }
private:
    int cnt;
};

/*
"Jlhvvd wfwnphmxoa qcuucx qsvqskq cqwfypww dyphntfz hkbwx xmwohi qvzegb ubogo sbdfmnyeim tuqppyipb llwzeug hrsaebveez aszqnvruhr xqpqd ipwbapd mlghuuwvec xpefyglstj dkvhhgecd kry"
output: "Kry xqpqd ubogo hkbwx qvzegb jlhvvd xmwohi qcuucx qsvqskq llwzeug ipwbapd dyphntfz cqwfypww tuqppyipb dkvhhgecd sbdfmnyeim xpefyglstj mlghuuwvec aszqnvruhr hrsaebveez wfwnphmxoa"
expected: "Kry hkbwx ubogo xqpqd jlhvvd qcuucx xmwohi qvzegb qsvqskq llwzeug ipwbapd cqwfypww dyphntfz tuqppyipb dkvhhgecd wfwnphmxoa sbdfmnyeim hrsaebveez aszqnvruhr mlghuuwvec xpefyglstj"
*/

/*
text 以大写字母开头，然后包含若干小写字母以及单词间的单个空格。
1 <= text.length <= 10^5
*/
bool sortLen(string str1, string str2) {
    return (str1.length() < str2.length());
}
class Solution {
public:
    string arrangeWords(string text) {
        vector<string> str;       
        int pos = 0, npos = 0;
        while ((npos = text.find(" ", pos)) != string::npos) {
            str.push_back(text.substr(pos, npos - pos));
            pos = npos + 1;
        }
        str.push_back(text.substr(pos));
        if (str.size() > 1) {
            str[0][0] = tolower(str[0][0]);
        }
        sort(str.begin(), str.end(), sortLen);
        // will keep same element pos don't change
        stable_sort(str.begin(), str.end(), sortLen);

        string ret;
        for (auto v : str) {
            ret += v;
            ret += " ";
        }
        ret[0] = toupper(ret[0]);
        ret.erase(ret.length() - 1, 1);

        return ret;
    }
};

class Solution {
public:
    static bool cmp(vector<string> v1, vector<string> v2) {
        return (v1.size() < v2.size());
    }

    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        sort(favoriteCompanies.begin(), favoriteCompanies.end(), cmp);
        vector<int> ret;
        vector<set<string>> fc;
        for (auto f : favoriteCompanies) {
            set<string> s;
            for (auto v : f) {
                s.insert(v);
            }
            fc.push_back(s);
        }
        for (int i = 0; i < fc.size(); i++) {
            set<string> s = fc.at(i);
            int j = 0;
            for (; j < fc.size(); j++) {
                if (j == i) continue;
                set<string> f = fc.at(j);
                int size = f.size();
                f.merge(s.begin(), s.end()); 
                if (size == f.size()) break;
            }
            if (j >= fc.size()) ret.push_back(i);
        }

        return ret;
    }
};

class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int l1 = sentence.length();
        int l2 = searchWord.length();
        int index = 1;

        for(int i = 0; i < l1; i++) {
            int j = 0;
            for(; j < l2 && i < l1; j++, i++) {
                if(searchWord[j] != sentence[i]) break;
            }
            if (j == l2) return index;
            index++;
            while(sentence[i] != ' ') i++;
        }

        return -1;
    }
};

class Solution {
public:
    bool isVowels(char c) {
        return (c == 'a' ||
                c == 'e' ||
                c == 'i' ||
                c == 'o' ||
                c == 'u');
    }
    int maxVowels(string s, int k) {
        vector<int> index;
        for (int i = 0; i < s.length(); i++) {
            if (isVowels(s[i])) index.push_back(i);
        }
        if (index.size() == 0) return 0;
        int max = 1;
        int l = 0;
        for (int i = 0; i < index.size(); i++) {
            while (l <= i && index[i] - index[l] >= k) l++;
            max = max > (i - l + 1) ? max : (i - l + 1);
        }
        return max;
    }
};


int main()
{
    return 0;
}