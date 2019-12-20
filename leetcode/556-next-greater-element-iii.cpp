int nextGreaterElement(int n){
    int t[32] = {0};
    int index = 31;
    while(n) {
        t[index--] = n % 10;
        n = (n - n % 10) / 10;
    }
    int i = 0;
    for(i = 31; i > index + 1; i--) {
        int j = i - 1;
        if(t[j] >= t[i])
            continue;
        int k = i;
        while(k < 32 && t[k] > t[j]) {
            k++;
        }
        int tmp = t[j];
        t[j] = t[k-1];
        t[k-1] = tmp;
        k = i, j = 31;
        while(k < j){
            tmp = t[k];
            t[k] = t[j];
            t[j] = tmp;
            k++;
            j--;
        }
        long long r = 0;
        index++;
        while(index < 32)
            r = r * 10 + t[index++];
        if(r < pow(2, 31))
            return (int)r;
        return -1;
    }
    return -1;
}
