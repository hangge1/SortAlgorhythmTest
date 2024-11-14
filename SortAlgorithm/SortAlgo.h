#pragma once

#include <vector>
#include <string>
#include "Tool.h"

template<typename T>
class SortAlgo
{
public:
    static T& Get()
    {
        static T sort;
        return sort;
    }

    virtual std::string Name() const = 0;

    //默认方式：不在原始数据上排序，拷贝一份原始数据，然后排序
    virtual void Sort(const std::vector<int>& InputData, std::vector<int>& SortResults) = 0;
};