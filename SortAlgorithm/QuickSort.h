#pragma once

#include "SortAlgo.h"
#include <stack>

/*
    快速排序【俗称快排】
    1、不稳定
    2、时间复杂度 O(N*LogN)
    3、空间复杂度 O(logN) 【递归栈】 
    4、性能优异，易于扩展，不考虑稳定性，首选的排序算法！
    5、这里给出四种实现算法：
    【前三种都是递归写法，只有pivot选择的区别！  第四种是迭代写法】
        (1) 第一种QuickSort_Easy  是每次都选择区间的第一个元素作为pivot
        (2) 第二种QuickSort_RandomPivot  是每次都选择区间的随机一个元素作为pivot
        (3) 第三种QuickSort_Medium3Pivot  是Medium3，选择头、尾、中间的中位数作为pivot
        (4) 第四种是迭代写法 QuickSort_UnRecursive
*/


class QuickSort_Easy : public SortAlgo<QuickSort_Easy>
{
public:
    virtual std::string Name() const override
    {
        return "QuickSort_Easy";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        
        if(SortResults.empty())return;

        SortMain(SortResults, 0, (int)SortResults.size() - 1);
    }

    //排序数组的[startIndex, endIndex]闭区间的元素，默认升序
    //单边遍历的形式
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        if(startIndex >= endIndex || startIndex < 0 || endIndex >= SortArray.size()) return;

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
class QuickSort_RandomPivot : public SortAlgo<QuickSort_RandomPivot>
{
public:
    virtual std::string Name() const override
    {
        return "QuickSort_RandomPivot";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;       
        if(SortResults.empty())
            return;

        SortMain(SortResults, 0, (int)SortResults.size() - 1);
    }

    //排序数组的【startIndex, endIndex】闭区间的元素，默认升序
    //单边遍历的形式
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        if(startIndex >= endIndex || startIndex < 0 || endIndex >= SortArray.size()) 
            return;

        //[随机选取]
        int pivotIndex = Tool::Get().GetRandom(startIndex, endIndex);
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

// 优化Pivot的选取(Medium3)
class QuickSort_Medium3Pivot : public SortAlgo<QuickSort_Medium3Pivot>
{
public:
    virtual std::string Name() const override
    {
        return "QuickSort_Medium3Pivot";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        
        if(SortResults.empty())return;

        SortMain(SortResults, 0, (int)SortResults.size() - 1);
    }

    //排序数组的【startIndex, endIndex】闭区间的元素，默认升序
    //单边遍历的形式
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        if(startIndex >= endIndex || startIndex < 0 || endIndex >= SortArray.size()) return;

        //法2：[Medium3]  寻找start、end、中点，的中位数作为pivot
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
        struct helper
        {
            int v;
            int index;
        };

        int middleIndex = startIndex + (endIndex - startIndex) / 2;

        helper start { SortArray[startIndex], startIndex};
        helper middle { SortArray[middleIndex], middleIndex};
        helper end { SortArray[endIndex], endIndex};

        if(start.v < middle.v)
        {
            std::swap(start,middle);
        }

        if(start.v < end.v)
        {
            std::swap(start,end);
        }

        if(middle.v < end.v)
        {
            std::swap(middle,end);
        }

        return middle.index;
    }
};


// 优化为非递归版本
class QuickSort_UnRecursive : public SortAlgo<QuickSort_UnRecursive>
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

    virtual std::string Name() const override
    {
        return "QuickSort_UnRecursive";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        
        if(SortResults.empty())return;

        SortMain(SortResults, 0, (int)SortResults.size() - 1);
    }

    //排序数组的[startIndex, endIndex]闭区间的元素，默认升序
    //单边遍历的形式
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
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