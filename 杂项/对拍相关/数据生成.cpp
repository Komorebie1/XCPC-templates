srand(time(0));  // 以当前时间作为随机种子，需要 time.h 库，每秒钟种子变化一次
int a = rand();  // rand 函数生成的整数在 [0,2^15-1] 之间均匀分布
int rrand() { return (rand() << 15) | rand(); }  // 生成[0,2^30-1]间的整数