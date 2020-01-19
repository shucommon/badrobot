
int maximum69Number (int num){
    int n = 1000;
    int tmp = num;
    while(n) {
        if(tmp / n == 6) {
            num += 3 * n; 
            return num;
        }
        tmp %= n; 
        n /= 10;
    }
    return num;
}
