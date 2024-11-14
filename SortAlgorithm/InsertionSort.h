#pragma once

#include "SortAlgo.h"

/*
    直接插入排序
    1、稳定 【比较过程，对于相等情况不能交换，不然不稳定】
    2、时间复杂度 O(N^2)【特例，已有序下为O(N)】
    3、空间复杂度 O(1)
    4、数据量比较小的情况，几乎是所有工程的首选应用算法
    5、优化思路
     (1) 朴素算法是在有序序列按顺序找到自己的位置插入； 这里可用二分法加快查找位置的过程！
*/

class InsertionSort : public SortAlgo<InsertionSort>
{
public:
    virtual std::string Name() const override
    {
        return "InsertionSort";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        for (int i = 1; i < SortResults.size(); i++)
        {
            //不断跟之前的所有元素比较大小, If < 前移
            int CurrentCompareElement = SortResults[i];
            int InsetIndex = i - 1;
            while(InsetIndex >= 0 && CurrentCompareElement < SortResults[InsetIndex])
            {
                SortResults[InsetIndex + 1] = SortResults[InsetIndex];
                InsetIndex--;
            }

            SortResults[InsetIndex + 1] = CurrentCompareElement;
        }
    }
};