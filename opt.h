#pragma once

#include <iostream>
#include <vector>
#include <ctime>

namespace generate_random_number
{
    static bool wh = false;
    // val���������ȡֵ��Χ����0~val
    std::vector<int> choseNum(const int &val)
    {
        std::vector<int> res = {};
        if (!wh)
        {
            std::srand(std::time(0));
            wh = true;
            std::cout << "��������������ɣ�" << '\n';
        }
        for (int time = 0; time < val; time++)
        {
            res.push_back(rand() % val);
        }
        return res;
    }
}