
#pragma once

#include "SortAlgo.h"

/*
    冒泡排序
    1、稳定
    2、时间复杂度 O(N^2)【特例，已有序下为O(N)】
    3、空间复杂度 O(1)
    4、这里给出三种写法
    (1) 第一种是小白入门写法
    (2) 第二种利用flag优化，已有序下中止循环
    (3) 第三种考虑不断冒泡，所以外层循环的范围是不断缩小的

    TODO: 鸡尾酒排序，更高级的优化【思路就是不仅从前往后冒泡，也从后往前冒泡】
*/


// the simplest way to write Bubble Sort 
// It has not been optimized and theoretically is relatively slow
class BubbleSort_Easy : public SortAlgo
{
public:
    static BubbleSort_Easy& Get()
    {
        static BubbleSort_Easy sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "BubbleSort_Easy";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;

        //每一轮冒泡的序列的结束下标
        for (int i = SortResults.size() - 1; i >= 0; i--)
        {
            //针对从[0, i]不断和下一个元素比较和交换
            for (int j = 0; j < i; j++)
            {
                if(SortResults[j] > SortResults[j + 1])
                {
                    std::swap(SortResults[j], SortResults[j + 1]);
                }
            }
        }
    }
};

// use a flag to Optimize the situation where the sequence is basically ordered
class BubbleSort_Flag_Opt : public SortAlgo
{
public:
    static BubbleSort_Flag_Opt& Get()
    {
        static BubbleSort_Flag_Opt sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "BubbleSort_Flag_Opt";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;

        //每一轮冒泡的序列的结束下标
        for (int i = SortResults.size() - 1; i >= 0; i--)
        {
            bool HasSwap = false; 
            //针对从[0, i]不断和下一个元素比较和交换
            for (int j = 0; j < i; j++)
            {
                if(SortResults[j] > SortResults[j + 1])
                {
                    std::swap(SortResults[j], SortResults[j + 1]);
                    HasSwap = true;
                }
            }

            if(!HasSwap)break;
        }
    }
};

// Optimize the number of iterations for each sequence
class BubbleSort_ForTime_Opt : public SortAlgo
{
public:
    static BubbleSort_ForTime_Opt& Get()
    {
        static BubbleSort_ForTime_Opt sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "BubbleSort_ForTime_Opt";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;

        //每一轮冒泡的序列的结束下标
        int HasSortedCount = 0;
        for (int i = SortResults.size() - 1 - HasSortedCount; i >= 0; i--)
        {
            bool HasSwap = false; 
            //针对从[0, i]不断和下一个元素比较和交换
            for (int j = 0; j < i; j++)
            {
                if(SortResults[j] > SortResults[j + 1])
                {
                    std::swap(SortResults[j], SortResults[j + 1]);
                    HasSwap = true;
                }
            }

            HasSortedCount++;
            if(!HasSwap)break;
        }
    }
};

//TODO 鸡尾酒算法