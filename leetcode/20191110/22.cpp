class Solution {
public:
    vector<vector<int>> reconstructMatrix(int upper, int lower, vector<int>& colsum) {
        vector<vector<int>> arr;
        vector<vector<int>> emp;
        int sum = 0;
        for(auto c : colsum)
            sum += c;
        if(sum != (upper + lower))
            return emp;

        int n = colsum.size();
        arr = vector<vector<int>>(2, vector<int>(n, 0));
        for(int i = 0; i < n; i++) {
            if(colsum.at(i) == 2) {
                arr[0][i] = 1;
                arr[1][i] = 1;
                upper--;
                lower--;
            }
        }
        if(upper < 0 || lower < 0)
            return emp;
        int i = 0;
        while(upper) {
            if(colsum.at(i) == 1) {
                arr[0][i] = 1;
                upper--;
            }
            i++;
        }
        while(lower) {
            if(colsum.at(i) == 1) {
                arr[1][i] = 1;
                lower--;
            }
            i++;
        }
        return arr;
    }
};
