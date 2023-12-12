#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <atomic>
#include <chrono>

/*
    ����
*/
class SortArray{
public:
    SortArray() = delete;
    SortArray(const std::vector<int>& arr) : _res(arr) {};

    // �������򣨽ӿڣ�
    void quickSort();
    // ð�����򣨽ӿڣ�
    void bubbleSort();
    // ѡ������ӿ�
    void selectionSort();

    void show_time(){
        std::cout << "����������ʱ��" << this->_quick_time.count() << "s" << std::endl;
        std::cout << "ð��������ʱ��" << this->_bubble_time.count() << "s" << std::endl;
        std::cout << "ѡ��������ʱ��" << this->_selection_time.count() << "s" << std::endl;
    }

    // �������Ƿ�ִ������
    // ԭ�Ӳ�������֪ͨ����
    // �ƺ���condition_variable�����
    std::atomic<bool> _run_quick{ false };
    std::atomic<bool> _run_bubble{ false };
    std::atomic<bool> _run_selection{ false };

private:
    // ��Դ����
    const std::vector<int> _res;

    // �����Ƿ�����ɹ�
    bool verify(const std::vector<int>& arr);

    // �����ʱ
    std::chrono::duration<double> _quick_time;      // ������ʱ
    std::chrono::duration<double> _bubble_time;     // ð��������ʱ
    std::chrono::duration<double> _selection_time;  // ѡ��������ʱ

    
    // ���ýӿ�
    void quickSort(std::vector<int>& arr);
    void bubbleSort(std::vector<int>& arr);
    void selectionSort(std::vector<int> &arr);
};



/*
    ���忪ʼ
*/
bool SortArray::verify(const std::vector<int>& arr){
    if(arr.empty()){
        std::cerr << "�����������Ϊ��";
        return false;
    }

    return std::is_sorted(arr.begin(), arr.end());
}



void SortArray::quickSort()
{
    // �п�
    if(this->_res.empty()){
        std::cerr << "��Դ����_resΪ��" << std::endl;
        return;
    }

    // ��������
    std::vector<int> res = this->_res;
    // ��ʼ���򡢼�ʱ
    quickSort(res);

    // �������
    _run_quick.store(true, std::memory_order_relaxed);
}




void SortArray::quickSort(std::vector<int>& arr) {
    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(0, arr.size() - 1));

    // ��ʼ��ʱ��
    auto start = std::chrono::high_resolution_clock::now(); // ��ȡ��ǰʱ���

    while (!stack.empty()) {
        int low = stack.top().first;
        int high = stack.top().second;
        stack.pop();

        // ��ʼ���Ļ�׼����arr[0]
        int pivot = arr[low];

        int i = low + 1;
        int j = high;

        // ��i, j��Χ���������
        while (i <= j) {
            while (i <= j && arr[i] <= pivot) {
                ++i;
            }
            // ����arr[i] > ��׼��
            // ����������Ҫ����

            while (i <= j && arr[j] > pivot) {
                --j;
            }
            // ����arr[j] <= ��׼��
            // Ҳ������Ҫ����

            if (i < j) {
                // ��������������λ��
                std::swap(arr[i], arr[j]);
            }
        }

        // ������׼��λ��
        // ���ⷴ����ͬһ����׼��Ϊ��׼
        std::swap(arr[low], arr[j]);

        if (low < j - 1) {
            stack.push(std::make_pair(low, j - 1));
        }

        if (j + 1 < high) {
            stack.push(std::make_pair(j + 1, high));
        }
    }

    // ֹͣ��ʱ��
    auto end = std::chrono::high_resolution_clock::now(); // ��ȡ��ǰʱ���
    std::chrono::duration<double, std::milli> elapsed = end - start; // ����ʱ����λ�Ǻ���
    this->_quick_time += elapsed;

    // �����Ƿ�����ɹ�
    bool ordered = verify(arr);
    if(ordered){
        std::cout << "�������򣬳ɹ�!" << std::endl;
    }
    else{
        std::cerr << "��������ʧ��" << std::endl;
    }

    return;
}



void SortArray::bubbleSort()
{
    // �п�
    if(this->_res.empty()){
        std::cerr << "��Դ����_resΪ��" << std::endl;
        return;
    }

    // ��������
    std::vector<int> res = this->_res;
    // ��ʼ���򡢼�ʱ
    bubbleSort(res);

    // ����״̬
    _run_bubble.store(true, std::memory_order_relaxed);
}



void SortArray::bubbleSort(std::vector<int>& arr){
    // ��ʼ��ʱ��
    auto start = std::chrono::high_resolution_clock::now(); // ��ȡ��ǰʱ���


    for(int left=0; left < static_cast<int>(arr.size()-1); left++){
        for(int right=left+1; right < static_cast<int>(arr.size()); right++){
            if(arr[left] > arr[right]){
                std::swap(arr[left], arr[right]);
            }
        }
    }

    // ֹͣ��ʱ��
    auto end = std::chrono::high_resolution_clock::now(); // ��ȡ��ǰʱ���
    std::chrono::duration<double, std::milli> elapsed = end - start; // ����ʱ����λ�Ǻ���
    this->_bubble_time += elapsed;

    // �Ƿ�����
    bool ordered = verify(arr);
    if(ordered){
        std::cout << "ð�����򣬳ɹ�!" << std::endl;
    }
    else{
        std::cerr << "ð������ʧ��" << std::endl;
    }
}



void SortArray::selectionSort(){
    // �п�
    if(this->_res.empty()){
        std::cerr << "��Դ����_resΪ��" << std::endl;
        return;
    }

    // ��������
    std::vector<int> res = this->_res;
    // ��ʼ���򡢼�ʱ
    selectionSort(res);

    // ����״̬
    _run_selection.store(true, std::memory_order_relaxed);
}


void SortArray::selectionSort(std::vector<int> &arr) {
    auto start = std::chrono::high_resolution_clock::now(); // ��ȡ��ǰʱ���

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

    // ֹͣ��ʱ��
    auto end = std::chrono::high_resolution_clock::now(); // ��ȡ��ǰʱ���
    std::chrono::duration<double, std::milli> elapsed = end - start; // ����ʱ����λ�Ǻ���
    this->_selection_time += elapsed;

    // �Ƿ�����
    bool ordered = verify(arr);
    if(ordered){
        std::cout << "ѡ�����򣬳ɹ�!" << std::endl;
    }
    else{
        std::cerr << "ѡ������ʧ��" << std::endl;
    }
}