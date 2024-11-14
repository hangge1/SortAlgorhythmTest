#pragma once

#include <iostream>
#include <vector>
#include <string>

/*
    工具类
    1、产生随机数
    2、对数组打印
*/

class Tool
{
public:
    static Tool& Get()
    {
        static Tool tool;
        return tool;
    }

    //获取随机数
    int GetRamdom()
    {
        return rand();
    }

    //获取[MinNum, MaxNum]闭区间的随机数
    int GetRandom(int MinNum, int MaxNum)
    {
        return (rand() % (MaxNum - MinNum + 1)) + MinNum;
    }

    void Print(const std::vector<int>& InputDatas) const
    {
        for (int num : InputDatas)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    void Print(const std::vector<int>& InputDatas, int startIndex, int endIndex) const
    {
        std::cout << "[" << startIndex << "-" << endIndex << "]: ";
        for(int i = startIndex; i <= endIndex; i++)
        {
            std::cout << InputDatas[i] << " ";
        }
        std::cout << std::endl;
    }

    void PrintData(const std::vector<int>& Data, std::string prefixWords = "", std::string postWords = "\n") const
    {
        std::cout << prefixWords;
        for (int num : Data)
        {
            std::cout << num << " ";
        }
        std::cout << postWords;
    }
private:
    Tool()
    {
        srand((unsigned)time(NULL));
    }
};