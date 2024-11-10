#pragma once

#include <vector>
#include <string>


class SortAlgo
{
public:
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) = 0;

    virtual std::string Name() const = 0;

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
};