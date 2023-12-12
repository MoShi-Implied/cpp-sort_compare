#pragma once

#include <iostream>
#include <vector>
#include <ctime>

namespace generate_random_number
{
    static bool wh = false;
    // val是随机数的取值范围，从0~val
    std::vector<int> choseNum(const int &val)
    {
        std::vector<int> res = {};
        if (!wh)
        {
            std::srand(std::time(0));
            wh = true;
            std::cout << "随机数种子已生成！" << '\n';
        }
        for (int time = 0; time < val; time++)
        {
            res.push_back(rand() % val);
        }
        return res;
    }
}