#include <iostream>
#include <thread>
#include "./log/log.h"

using namespace std;

void Thread_push(int id) {
    for (int i = 1; i <= INT16_MAX; i++) {
        std::cout << id << "--" << i << std::endl;
        Log::instance().write_log(Level::DEBUG, "This is %d by thread %d\n", i, id);
    }
}

int main() {
    // 新建十个线程执行函数Thread_push, Thread_push中传递的参数分别是1~10
//    for (int i = 0; i < 10; i++) {
//        std::thread thread(Thread_push, i);
//        thread.join();
//    }
    Log::instance().init();
    for (int i = 1; i <= 50001; i++) {
        if (i == 50001) {
            cout << "haha" << endl;
        }
        Log::instance().write_log(Level::DEBUG, "This is %d.", i);
    }

    std::cout << "Finish!" << std::endl;
    return 0;
}
