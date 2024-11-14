#pragma once

#pragma once

#include "SortAlgo.h"

/*
    基数排序
    1、稳定 
    2、时间复杂度 O(N + k) 【k表示数据样本的区间大小，也就是数据最大值和最小值的差距】
    3、空间复杂度 O(k)
    4、应用场景： 常用于10进制的非负整数
    5、简单介绍一下写法         
*/

class RadixSort : public SortAlgo
{
public:
    static RadixSort& Get()
    {
        static RadixSort sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "RadixSort";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty()) return;

        //测试10进制数字且三位数  0-999数据范围的非负整数
        RadixSortMain(SortResults, 10, 3);
    }

    //Base表示数字的进制,如果是10进制,则需要0-9号10个桶
    //MaxBits表示数据的最大位数,比如10进制数据1000,最大位数就是4,千位,百位,十位,个位
    void RadixSortMain(std::vector<int>& SortDatas, int Base, int MaxBits)
    {
        int size = (int)SortDatas.size();
        int Offset = 1;

        std::vector<int> bucksHelper(Base, 0); //辅助桶结构
        std::vector<int> tmp(size, 0); //存储该位排序结果
        for(int i = MaxBits; i >= 0; i--)
        {
            std::fill(tmp.begin(), tmp.end(), 0);
            std::fill(bucksHelper.begin(), bucksHelper.end(), 0);
            
            for (int k = 0; k < size; k++)
            {
                //1 取数字的某位
                int bitValue = (SortDatas[k] / Offset) % Base;
                //2 扔进桶里
                bucksHelper[bitValue]++;
            }

            //3 计算累计数组
            for (int k = 1; k < Base; k++)
            {
                bucksHelper[k] += bucksHelper[k-1];
            }

            //4 从后往前便利原数据,进行还原
            for (int k = size - 1; k >= 0; k--)
            {
                //1 取数字的某位
                int bitValue = (SortDatas[k] / Offset) % Base;

                //2 计算位置
                int pos = bucksHelper[bitValue] - 1;

                //3 扔进临时数组
                tmp[pos] = SortDatas[k];

                //4 累计数组-1
                bucksHelper[bitValue]--;
            }

            //5 覆盖原数组
            SortDatas = tmp;

            //为了获得下一位，得改变偏移
            Offset *= Base;
        }
    }
};