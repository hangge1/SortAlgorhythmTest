#pragma once

#include "SortAlgo.h"
#include <stack>

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
        int currentIndexs = startIndex + 1;
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
        std::swap(SortArray[startIndex], SortArray[currentIndexs - 1]);
        
   
        //递归执行
        SortMain(SortArray, startIndex, currentIndexs - 2);
        SortMain(SortArray, currentIndexs, endIndex); 
    }
};

// 优化Pivot的选取(随机选取)
class QuickSort_Opt_SelectPivot : public SortAlgo
{
public:
    static QuickSort_Opt_SelectPivot& Get()
    {
        static QuickSort_Opt_SelectPivot sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "QuickSort_Opt_SelectPivot";
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

        //法1：[随机选取]
        //int pivotIndex = Tool::Get().GetRandom(startIndex, endIndex);
        //int pivot = SortArray[pivotIndex];

        //法2：[Medium3]  寻找start、end、中点，值最小的作为pivot
        int pivotIndex = Medium3(SortArray, startIndex, endIndex);
        int pivot = SortArray[pivotIndex];

        std::swap(SortArray[pivotIndex], SortArray[startIndex]);
        
        //区间划分 <= 和 >
        int currentIndexs = startIndex + 1;
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

        std::swap(SortArray[startIndex], SortArray[currentIndexs - 1]);
        
        SortMain(SortArray, startIndex, currentIndexs - 2);
        SortMain(SortArray, currentIndexs, endIndex); 
    }

    int Medium3(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        int startValue = SortArray[startIndex];
        int middleIndex = startIndex + (endIndex - startIndex) / 2;
        int middleValue = SortArray[middleIndex];
        int endValue = SortArray[endIndex];
        int pivotIndex = startValue < middleValue ? startIndex : (middleValue < endValue ? middleIndex : endIndex);

        return pivotIndex;
    }
};


// 优化为非递归版本
class QuickSort_UnRecursive : public SortAlgo
{
public:
    struct Range
    {
        int start;
        int end;

        Range(int s = 0, int e = 0)
            :start(s), end(e)
        {}
    };

    static QuickSort_UnRecursive& Get()
    {
        static QuickSort_UnRecursive sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "QuickSort_UnRecursive";
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
        //Print(SortArray, startIndex, endIndex);
     
        std::stack<Range> RangeStack;
        RangeStack.emplace(startIndex, endIndex);

        while(!RangeStack.empty())
        {
            Range IndexRange = RangeStack.top();
            RangeStack.pop();

            int sIndex = IndexRange.start;
            int eIndex = IndexRange.end;
            if(sIndex >= eIndex || sIndex < 0 || eIndex >= SortArray.size()) continue;


            //[Medium3]
            int pivotIndex = Medium3(SortArray, sIndex, eIndex);
            int pivot = SortArray[pivotIndex];
            std::swap(SortArray[pivotIndex], SortArray[sIndex]);

            int currentIndexs = sIndex + 1;
            int lastBePutIndex = eIndex; 
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
            
            std::swap(SortArray[sIndex], SortArray[currentIndexs - 1]);
            
            RangeStack.emplace(sIndex, currentIndexs - 2);
            RangeStack.emplace(currentIndexs, eIndex);
        }
    }

    int Medium3(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        int startValue = SortArray[startIndex];
        int middleIndex = startIndex + (endIndex - startIndex) / 2;
        int middleValue = SortArray[middleIndex];
        int endValue = SortArray[endIndex];
        int pivotIndex = startValue < middleValue ? startIndex : (middleValue < endValue ? middleIndex : endIndex);

        return pivotIndex;
    }
};