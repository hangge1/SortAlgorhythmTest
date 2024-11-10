#pragma once

#include "SortAlgo.h"

class QuickSort_Easy : public SortAlgo
{
public:
    static QuickSort_Easy& Get()
    {
        static QuickSort_Easy sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "QuickSort_Easy";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        
        if(SortResults.empty())return;

        SortMain(SortResults, 0, SortResults.size() - 1);
    }

    //排序数组的[startIndex, endIndex]闭区间的元素，默认升序
    //单边遍历的形式
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        if(startIndex >= endIndex || startIndex < 0 || endIndex >= SortArray.size()) return;

        //Print(SortArray, startIndex, endIndex);

        //选取一个pivot [最简单的选取，就选第一个]
        int pivot = SortArray[startIndex];
        int pivotIndex = startIndex;

        //区间划分 <= 和 >
        int currentIndexs = startIndex;
        int lastBePutIndex = endIndex; 
        while(currentIndexs <= lastBePutIndex)
        {  
            if(SortArray[currentIndexs] <= pivot)
            {
                currentIndexs++;
            }
            else
            {
                std::swap(SortArray[currentIndexs], SortArray[lastBePutIndex]);
                lastBePutIndex--;
            }
        }

        //此时所有下标< currentIndexs的元素的值 <= pivot
        //所以你要把pivot交换，你不能用currentIndex交换，你不能保证currentIndex下标的值<= pivot, 必须得用前一个的进行swap
        std::swap(SortArray[pivotIndex], SortArray[currentIndexs - 1]);
        
   
        //递归执行
        SortMain(SortArray, startIndex, currentIndexs - 2);
        SortMain(SortArray, currentIndexs, endIndex); 
    }
};