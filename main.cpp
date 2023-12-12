#include "./sort.h"
#include "./opt.h"
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

int main() {
    vector<int> arr;
    // ���������arr
    cout << "��������Ҫ��������ĸ�����" << '\n';
    int num;
    cin >> num;
    arr = generate_random_number::choseNum(num);
    SortArray target(arr);

    // ���߳�����
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

        // while����һֱ�ظ��ж�
        // �������Ϊwhile��������������
        // ����1s
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}