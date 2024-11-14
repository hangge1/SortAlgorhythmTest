#pragma once

#include "SortAlgo.h"

/*
    选择排序
    1、不稳定
    2、时间复杂度 O(N^2)
    3、空间复杂度 O(1)
    4、几乎不被工程所用，只是教学型的排序算法
    5、优化思路
     (1) 朴素算法每次找到最小值交换到头部； 可以考虑一次性遍历找到最大值和最小值，分别交换到头部和尾部！
*/

class SelectionSort : public SortAlgo<SelectionSort>
{
public:
    virtual std::string Name() const override
    {
        return "SelectionSort";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        for (int i = 0; i < SortResults.size(); i++)
        {
           int minElement = SortResults[i];
           int minIndex = i;

           for (int j = i + 1; j < SortResults.size(); j++)
           {
                if(SortResults[j] < minElement)
                {
                    minIndex = j;
                    minElement = SortResults[j];
                }
           }

           if(i != minIndex) std::swap(SortResults[minIndex], SortResults[i]);
        }
    }
};