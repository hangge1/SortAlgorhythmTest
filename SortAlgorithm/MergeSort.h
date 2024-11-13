#pragma once

#include "SortAlgo.h"

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