#pragma once

#include "SortAlgo.h"

class CountingSort : public SortAlgo
{
public:
    static CountingSort& Get()
    {
        static CountingSort sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "CountingSort";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty()) return;

        //1 统计最大值和最小值
        int maxNum = INT_MIN;
        int minNum = INT_MAX;
        for (int i = 0; i < SortResults.size(); i++)
        {
           if(SortResults[i] > maxNum) maxNum = SortResults[i];
           if(SortResults[i] < minNum) minNum = SortResults[i];
        }

        //2 开辟计数数组，遍历计数
        std::vector<int> Counting(maxNum - minNum + 1, 0);
        for (int i = 0; i < SortResults.size(); i++)
        {
           int v = SortResults[i];
           Counting[v - minNum]++;
        }

        //3 计算累计数组
        for (int i = 1; i < Counting.size(); i++)
        {
            Counting[i] += Counting[i-1];
        }

        //4 开辟结果数组，从后往前遍历原数据，根据累计数组值进行填写
        std::vector<int> tmp(SortResults.size());
        for (int i = SortResults.size() - 1; i >= 0; i--)
        {
           int v = SortResults[i];
           int pos = Counting[v - minNum] - 1;
           tmp[pos] = v;

           Counting[v - minNum]--;
        }

        SortResults = tmp;
    }
};