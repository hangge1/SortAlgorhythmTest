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

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        
        if(SortResults.empty()) return;

        MergeSortMain(SortResults, 0, SortResults.size() - 1);
    }

    //[left, right] ������
    void MergeSortMain(std::vector<int>& SortData, int left, int right)
    {
        if(left >= right)return; //ֻ��һ��Ԫ�أ��Ѿ�����

        int mid = left + (right - left) / 2;

        MergeSortMain(SortData, left, mid);
        MergeSortMain(SortData, mid + 1, right);

        Merge(SortData, left, mid, right);
    }

    //[left, mid] �� [mid + 1, right] ƴ��
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

//�ǵݹ����Ե�����
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

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;  
        if(SortResults.empty()) return;

        MergeSortMain(SortResults);
    }

    //[left, right] ������
    void MergeSortMain(std::vector<int>& SortData)
    {
        //���ϲ����г���
        //Ĭ����1����ʾ����Ϊ1��1�����кϲ�; �������η���,��ʾ����Ϊ2��2�����кϲ���4��4�����кϲ����Դ�����
        int WillMergeArrayLength = 1; 
        int ArrayLength = SortData.size();

        for (int i = WillMergeArrayLength; i < ArrayLength; i *= 2)
        {
            //�׸��ϲ���������
            int left = 0;
            int mid = left + i - 1;
            int right = mid + i;

            //���䲻�Ϻ���
            while(right <= ArrayLength - 1) //�����������
            {
                Merge(SortData, left, mid, right);
                left += 2 * i;
                mid = left + i - 1;
                right = mid + i;
            }

            //�����������һ�Σ����ȿ���С���������ϲ����г���
            if(left < ArrayLength && mid < ArrayLength)
            {
                Merge(SortData, left, mid, ArrayLength - 1);
            }
        }
    }

    //[left, mid] �� [mid + 1, right] ƴ��
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