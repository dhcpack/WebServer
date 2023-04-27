#include <iostream>
#include <thread>
#include "./log/log.h"

using namespace std;

void Thread_push(int id) {
    for (int i = 1; i <= 50000; i++) {
        std::cout << id << "--" << i << std::endl;
        Log::instance().write_log(Level::DEBUG, "This is %d by thread %d\n", i, id);
    }
}

int main() {
    Log::instance().init();
    // 新建十个线程执行函数Thread_push, Thread_push中传递的参数分别是1~10
    vector<std::thread> threads;
    for (int i = 0; i < 50; i++) {
        threads.emplace_back(Thread_push, i);
    }

    for (auto &t: threads) t.join();

    std::cout << "Finish!" << std::endl;
    return 0;
}
