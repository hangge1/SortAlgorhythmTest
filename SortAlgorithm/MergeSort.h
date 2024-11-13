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
        
        if(SortResults.empty()) return;

        MergeSortMain(SortResults, 0, SortResults.size() - 1);
    }

    //[left, right] 闭区间
    void MergeSortMain(std::vector<int>& SortData, int left, int right)
    {
        if(left >= right)return; //只有一个元素，已经有序

        int mid = left + (right - left) / 2;

        MergeSortMain(SortData, left, mid);
        MergeSortMain(SortData, mid + 1, right);

        Merge(SortData, left, mid, right);
    }

    //[left, mid] 和 [mid + 1, right] 拼接
    void Merge(std::vector<int>& SortData, int left, int mid, int right)
    {
        int p1 = left;
        int p2 = mid + 1;
        int i = 0;
        std::vector<int> tmp(right - left + 1);
        while(p1 <= mid && p2 <= right)
        {
            if(SortData[p1] <= SortData[p2]) tmp[i++] = SortData[p1++];
            else tmp[i++] = SortData[p2++];
        }

        while( p1 <= mid ) tmp[i++] = SortData[p1++];
        while( p2 <= right ) tmp[i++] = SortData[p2++];

        for (int i = 0; i < tmp.size(); i++) 
            SortData[left + i] = tmp[i];
    }
};

//非递归是自底向上
class MergeSortNoRecursion : public SortAlgo
{
public:
    static MergeSortNoRecursion& Get()
    {
        static MergeSortNoRecursion sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "MergeSortNoRecursion";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;  
        if(SortResults.empty()) return;

        MergeSortMain(SortResults);
    }

    //[left, right] 闭区间
    void MergeSortMain(std::vector<int>& SortData)
    {
        //待合并序列长度
        //默认是1，表示长度为1和1的序列合并; 后面依次翻倍,表示长度为2和2的序列合并、4和4的序列合并等以此类推
        int WillMergeArrayLength = 1; 
        int ArrayLength = SortData.size();

        for (int i = WillMergeArrayLength; i < ArrayLength; i *= 2)
        {
            //首个合并序列区间
            int left = 0;
            int mid = left + i - 1;
            int right = mid + i;

            //区间不断后移
            while(right <= ArrayLength - 1) //框框在区间内
            {
                Merge(SortData, left, mid, right);
                left += 2 * i;
                mid = left + i - 1;
                right = mid + i;
            }

            //单独考虑最后一段，长度可能小于两倍待合并序列长度
            if(left < ArrayLength && mid < ArrayLength)
            {
                Merge(SortData, left, mid, ArrayLength - 1);
            }
        }
    }

    //[left, mid] 和 [mid + 1, right] 拼接
    void Merge(std::vector<int>& SortData, int left, int mid, int right)
    {
        if(left >= right) return;

        int p1 = left;
        int p2 = mid + 1;
        int i = 0;
        std::vector<int> tmp(right - left + 1);
        while(p1 <= mid && p2 <= right)
        {
            if(SortData[p1] <= SortData[p2]) tmp[i++] = SortData[p1++];
            else tmp[i++] = SortData[p2++];
        }

        while( p1 <= mid ) tmp[i++] = SortData[p1++];
        while( p2 <= right ) tmp[i++] = SortData[p2++];

        for (int i = 0; i < tmp.size(); i++) 
            SortData[left + i] = tmp[i];
    }
};