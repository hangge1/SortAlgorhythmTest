#pragma once

#include "SortAlgo.h"

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