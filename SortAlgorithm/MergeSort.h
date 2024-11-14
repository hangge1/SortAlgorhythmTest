#pragma once

#include "SortAlgo.h"

/*
    归并排序
    1、稳定【假设升序排序，要求Merge过程，针对两区间的元素挨个比较时，<=的情况优先选择左边区间元素,才能保证稳定】
    2、时间复杂度 O(N*LogN)
    3、空间复杂度 O(N)  【Merge过程需要】
    4、性能优异，并且考虑稳定性的排序算法，首选！
    5、这里给出两种实现算法：
        (1) 递归写法【常规写法】
        (2) 迭代写法【经测试，既保证了不会堆栈溢出，效率也略快于递归版本】
*/

//递归版本
class MergeSort : public SortAlgo
{
public:
    static MergeSort& Get()
    {
        static MergeSort sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "MergeSort";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty())return;

        MergeSortMain(SortResults, 0, SortResults.size() - 1);
    }

    //[left, right]
    void MergeSortMain(std::vector<int>& SortResults, int Left, int Right)
    {
        if(Left >= Right) return;

        int Mid = Left + (Right - Left) / 2;

        MergeSortMain(SortResults, Left, Mid);
        MergeSortMain(SortResults, Mid + 1, Right);

        Merge(SortResults, Left, Mid, Right);
    }

    //合并[left,mid] 和 [mid+1, right]
    void Merge(std::vector<int>& SortResults, int left, int mid, int right)
    {
        std::vector<int> tmp(right - left + 1);

        int i = 0;
        int p1 = left;
        int p2 = mid + 1;

        while(p1 <= mid && p2 <= right)
        {
            if(SortResults[p1] <= SortResults[p2]) tmp[i++] = SortResults[p1++];
            else tmp[i++] = SortResults[p2++];
        }

        while(p1 <= mid) tmp[i++] = SortResults[p1++];
        while(p2 <= right) tmp[i++] = SortResults[p2++];

        for (int i = 0; i < tmp.size(); i++)
        {
            SortResults[i + left] = tmp[i];
        }
    }
};


//非递归版本
class MergeSort_NoRecursion : public SortAlgo
{
public:
    static MergeSort_NoRecursion& Get()
    {
        static MergeSort_NoRecursion sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "MergeSort_NoRecursion";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty())return;

        MergeSortMain_NoRecursion(SortResults);
    }

    void MergeSortMain_NoRecursion(std::vector<int>& SortResults)
    {
        // 带合并序列长度，1表示两个长度为1的序列需要合并！后面依次范围2、4、8...
        int WillMergeArrayLength = 1;

        int DataLength = SortResults.size();
        for (int i = WillMergeArrayLength; i < DataLength; i *= 2)
        {
            //第一个合并序列的区间，这里是闭区间【left,mid】和【mid+1，right】
            int left = 0;
            int mid = left + i - 1;
            int right = mid + i;

            //区间后移
            while(right < DataLength)
            {
                Merge(SortResults, left, mid, right);
                left += 2 * i;
                mid = left + i - 1;
                right = mid + i;
            }

            //最后区间特殊处理【因为最后区间的Right有可能超过数组最大范围】
            if(left < DataLength && mid < DataLength)
            {
                Merge(SortResults, left, mid, DataLength - 1);
            }
        }
    }

    //合并闭区间【left,mid】 和 【mid+1, right】
    void Merge(std::vector<int>& SortResults, int left, int mid, int right)
    {
        std::vector<int> tmp(right - left + 1);

        int i = 0;
        int p1 = left;
        int p2 = mid + 1;

        while(p1 <= mid && p2 <= right)
        {
            if(SortResults[p1] <= SortResults[p2]) tmp[i++] = SortResults[p1++];
            else tmp[i++] = SortResults[p2++];
        }

        while(p1 <= mid) tmp[i++] = SortResults[p1++];
        while(p2 <= right) tmp[i++] = SortResults[p2++];

        for (int i = 0; i < tmp.size(); i++)
        {
            SortResults[i + left] = tmp[i];
        }
    }
};