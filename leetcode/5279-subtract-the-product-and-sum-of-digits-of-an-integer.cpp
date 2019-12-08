int subtractProductAndSum(int n){
    int a = 1, b = 0;
    while(n) {
        int one = n % 10;
        a *= one;
        b += one; 
        n /= 10;
    }
    return (a - b);
}
