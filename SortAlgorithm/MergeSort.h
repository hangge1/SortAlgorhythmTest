#pragma once

#include "SortAlgo.h"

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

    //[left, right]
    void MergeSortMain_NoRecursion(std::vector<int>& SortResults)
    {
        int WillMergeArrayLength = 1;
        int DataLength = SortResults.size();
        for (int i = WillMergeArrayLength; i < DataLength; i *= 2)
        {
            int left = 0;
            int mid = left + i - 1;
            int right = mid + i;

            while(right < DataLength)
            {
                Merge(SortResults, left, mid, right);
                left += 2 * i;
                mid = left + i - 1;
                right = mid + i;
            }

            if(left < DataLength && mid < DataLength)
            {
                Merge(SortResults, left, mid, DataLength - 1);
            }
        }
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