#pragma once

#include "SortAlgo.h"

/*
    计数排序
    1、稳定 
    2、时间复杂度 O(N + k) 【k表示数据样本的区间大小，也就是数据最大值和最小值的差距】
    3、空间复杂度 O(k)
    4、应用场景： 数据量特别大，但数据样本本身取值范围很小，如：统计全国高考分数排名，全国人口年龄排名等
    5、简单介绍一下写法
    （1）数据类型就是数值
        这种数据的排序，稳定性也不重要，只需要一个计数数组，按次序填空就可
    （2）数据类型是自定义类类型
        这种数据排序，稳定性是很重要的！我们给出的就是保持稳定性的标准做法，需要利用Counting数组计算累计数组，然后从后往前遍历原数据填空
    （3）注意一点，咱们写法是支持负数的，也不限制数字一定要用0开始！   
*/

class CountingSort : public SortAlgo<CountingSort>
{
public:
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
        for (int i = (int)SortResults.size() - 1; i >= 0; i--)
        {
           int v = SortResults[i];
           int pos = Counting[v - minNum] - 1;
           tmp[pos] = v;

           Counting[v - minNum]--;
        }

        SortResults = tmp;
    }
};