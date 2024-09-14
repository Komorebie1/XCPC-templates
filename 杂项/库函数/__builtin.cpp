// 返回x二进制下含1的数量
cout << __builtin_popcount(x); // 例如x=15时答案为4

// 返回x二进制下最后一个1的位置（从1开始计算）
cout << __builtin_ffs(x); // 例如x=1答案为1，x=8答案为4

// 返回x二进制下后导0的个数
cout << __builtin_ctz(x); // 例如x=1答案为0，x=8答案为3

// 返回x二进制下第一个1的位置（原函数是求前导0的个数）
cout << 31 - __builtin_clz(x); // x = 9(1001) 返回 3
cout << 63 - __builtin_clzll(x);