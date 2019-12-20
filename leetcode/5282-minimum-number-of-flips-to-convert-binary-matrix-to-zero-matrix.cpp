class Solution {
public:
    int minFlips(vector<vector<int>>& a) {
        int dir1[] = {-1,1,0,0};
        int dir2[] = {0,0,-1,1};
        int n = a.size(), m = a[0].size();
        int sz = n*m;
        int ret = 1e9;
        
        for(int i=0;i<1<<sz;++i) {
            vector<vector<int>> tmp(n,vector<int>(m));
            for(int i=0;i<n;++i) for(int j=0;j<m;++j) tmp[i][j] = a[i][j];
            for(int j=0;j<sz;++j) {
                if(i&(1<<j)) {
                    int x=j/m,y=j%m;
                    tmp[x][y] = 1-tmp[x][y];
                    for(int k=0;k<4;++k) {
                        int xx=x+dir1[k],yy=y+dir2[k];
                        if(xx<0||yy<0||xx>=n||yy>=m) continue;
                        tmp[xx][yy] = 1-tmp[xx][yy];
                    }
                }
            }
            int ok=1;
            for(int i=0;i<n;++i) for(int j=0;j<m;++j) if(tmp[i][j]) ok=0;
            if(ok) ret=min(ret,__builtin_popcount(i));
        }
        if(ret > 1000) return -1;
        return ret;
    }
};

