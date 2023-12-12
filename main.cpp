#include "./sort.h"
#include "./opt.h"
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

int main() {
    vector<int> arr;
    // 创建随机数arr
    cout << "请输入需要排序的数的个数：" << '\n';
    int num;
    cin >> num;
    arr = generate_random_number::choseNum(num);
    SortArray target(arr);

    // 多线程提速
    std::thread th_quick([&target](){ target.quickSort(); });
    std::thread th_bubble([&target](){ target.bubbleSort(); });
    std::thread th_selection([&target](){ target.selectionSort(); });

    th_quick.detach();
    th_bubble.detach();
    th_selection.detach();

    while(true) {
        if(target._run_bubble && target._run_quick && target._run_selection) {
            target.show_time();
            break;
        }

        // while不能一直重复判断
        // 程序会认为while”假死“而报错
        // 休眠1s
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}