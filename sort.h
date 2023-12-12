#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <atomic>
#include <chrono>

/*
    声明
*/
class SortArray{
public:
    SortArray() = delete;
    SortArray(const std::vector<int>& arr) : _res(arr) {};

    // 快速排序（接口）
    void quickSort();
    // 冒泡排序（接口）
    void bubbleSort();
    // 选择排序接口
    void selectionSort();

    void show_time(){
        std::cout << "快速排序用时：" << this->_quick_time.count() << "s" << std::endl;
        std::cout << "冒泡排序用时：" << this->_bubble_time.count() << "s" << std::endl;
        std::cout << "选择排序用时：" << this->_selection_time.count() << "s" << std::endl;
    }

    // 看程序是否执行完了
    // 原子操作，起到通知作用
    // 似乎用condition_variable会更好
    std::atomic<bool> _run_quick{ false };
    std::atomic<bool> _run_bubble{ false };
    std::atomic<bool> _run_selection{ false };

private:
    // 资源数组
    const std::vector<int> _res;

    // 检验是否排序成功
    bool verify(const std::vector<int>& arr);

    // 程序计时
    std::chrono::duration<double> _quick_time;      // 快排用时
    std::chrono::duration<double> _bubble_time;     // 冒泡排序用时
    std::chrono::duration<double> _selection_time;  // 选择排序用时

    
    // 内置接口
    void quickSort(std::vector<int>& arr);
    void bubbleSort(std::vector<int>& arr);
    void selectionSort(std::vector<int> &arr);
};



/*
    定义开始
*/
bool SortArray::verify(const std::vector<int>& arr){
    if(arr.empty()){
        std::cerr << "程序出错，数组为空";
        return false;
    }

    return std::is_sorted(arr.begin(), arr.end());
}



void SortArray::quickSort()
{
    // 判空
    if(this->_res.empty()){
        std::cerr << "资源数组_res为空" << std::endl;
        return;
    }

    // 创建拷贝
    std::vector<int> res = this->_res;
    // 开始排序、计时
    quickSort(res);

    // 运行完毕
    _run_quick.store(true, std::memory_order_relaxed);
}




void SortArray::quickSort(std::vector<int>& arr) {
    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(0, arr.size() - 1));

    // 开始计时：
    auto start = std::chrono::high_resolution_clock::now(); // 获取当前时间点

    while (!stack.empty()) {
        int low = stack.top().first;
        int high = stack.top().second;
        stack.pop();

        // 初始化的基准数是arr[0]
        int pivot = arr[low];

        int i = low + 1;
        int j = high;

        // 在i, j范围内相对有序
        while (i <= j) {
            while (i <= j && arr[i] <= pivot) {
                ++i;
            }
            // 现在arr[i] > 基准数
            // 不符合排序要求了

            while (i <= j && arr[j] > pivot) {
                --j;
            }
            // 现在arr[j] <= 基准数
            // 也不符合要求了

            if (i < j) {
                // 调换它们两个的位置
                std::swap(arr[i], arr[j]);
            }
        }

        // 更换基准数位置
        // 避免反复以同一个基准数为标准
        std::swap(arr[low], arr[j]);

        if (low < j - 1) {
            stack.push(std::make_pair(low, j - 1));
        }

        if (j + 1 < high) {
            stack.push(std::make_pair(j + 1, high));
        }
    }

    // 停止计时：
    auto end = std::chrono::high_resolution_clock::now(); // 获取当前时间点
    std::chrono::duration<double, std::milli> elapsed = end - start; // 计算时间差，单位是毫秒
    this->_quick_time += elapsed;

    // 测试是否排序成功
    bool ordered = verify(arr);
    if(ordered){
        std::cout << "快速排序，成功!" << std::endl;
    }
    else{
        std::cerr << "快速排序，失败" << std::endl;
    }

    return;
}



void SortArray::bubbleSort()
{
    // 判空
    if(this->_res.empty()){
        std::cerr << "资源数组_res为空" << std::endl;
        return;
    }

    // 创建拷贝
    std::vector<int> res = this->_res;
    // 开始排序、计时
    bubbleSort(res);

    // 更改状态
    _run_bubble.store(true, std::memory_order_relaxed);
}



void SortArray::bubbleSort(std::vector<int>& arr){
    // 开始计时：
    auto start = std::chrono::high_resolution_clock::now(); // 获取当前时间点


    for(int left=0; left < static_cast<int>(arr.size()-1); left++){
        for(int right=left+1; right < static_cast<int>(arr.size()); right++){
            if(arr[left] > arr[right]){
                std::swap(arr[left], arr[right]);
            }
        }
    }

    // 停止计时：
    auto end = std::chrono::high_resolution_clock::now(); // 获取当前时间点
    std::chrono::duration<double, std::milli> elapsed = end - start; // 计算时间差，单位是毫秒
    this->_bubble_time += elapsed;

    // 是否有序？
    bool ordered = verify(arr);
    if(ordered){
        std::cout << "冒泡排序，成功!" << std::endl;
    }
    else{
        std::cerr << "冒泡排序，失败" << std::endl;
    }
}



void SortArray::selectionSort(){
    // 判空
    if(this->_res.empty()){
        std::cerr << "资源数组_res为空" << std::endl;
        return;
    }

    // 创建拷贝
    std::vector<int> res = this->_res;
    // 开始排序、计时
    selectionSort(res);

    // 更改状态
    _run_selection.store(true, std::memory_order_relaxed);
}


void SortArray::selectionSort(std::vector<int> &arr) {
    auto start = std::chrono::high_resolution_clock::now(); // 获取当前时间点

    for (int i = 0; i < static_cast<int>(arr.size()-1); i++) {
        int min_idx = i;
        for (int j = i + 1; j < static_cast<int>(arr.size()); j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(arr[i], arr[min_idx]);
        }
    }

    // 停止计时：
    auto end = std::chrono::high_resolution_clock::now(); // 获取当前时间点
    std::chrono::duration<double, std::milli> elapsed = end - start; // 计算时间差，单位是毫秒
    this->_selection_time += elapsed;

    // 是否有序？
    bool ordered = verify(arr);
    if(ordered){
        std::cout << "选择排序，成功!" << std::endl;
    }
    else{
        std::cerr << "选择排序，失败" << std::endl;
    }
}