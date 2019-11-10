def yihan():
    a = int(input("请输入一个1000以内的数字:"))
    for i in range(25):
        print("**********************************************************\n")
    m = int(input("请输入限制次数:"))
    i = 0
    while(1):
        b = int(input("猜猜我输入的数字:"))
        if b > a:
            print("太大了")
        elif b < a:
            print("太小了")
        if abs(b-a) < 5 and a != b:
            print("不过你已经接近了")
        if b == a:
            print("恭喜，你猜对了")
            break
        i += 1
        if i == m:
            print(str(i) + "次没猜对，结束")
            print("答案是")
            print(a)
            break
        print("还剩")
        print(m-i)
        print("次")


yihan()


