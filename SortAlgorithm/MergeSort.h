#pragma once

#include "SortAlgo.h"

/*
    �鲢����
    1���ȶ���������������Ҫ��Merge���̣�����������Ԫ�ذ����Ƚ�ʱ��<=���������ѡ���������Ԫ��,���ܱ�֤�ȶ���
    2��ʱ�临�Ӷ� O(N*LogN)
    3���ռ临�Ӷ� O(N)  ��Merge������Ҫ��
    4���������죬���ҿ����ȶ��Ե������㷨����ѡ��
    5�������������ʵ���㷨��
        (1) �ݹ�д��������д����
        (2) ����д���������ԣ��ȱ�֤�˲����ջ�����Ч��Ҳ�Կ��ڵݹ�汾��
*/

//�ݹ�汾
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

    //�ϲ�[left,mid] �� [mid+1, right]
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


//�ǵݹ�汾
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

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty())return;

        MergeSortMain_NoRecursion(SortResults);
    }

    void MergeSortMain_NoRecursion(std::vector<int>& SortResults)
    {
        // ���ϲ����г��ȣ�1��ʾ��������Ϊ1��������Ҫ�ϲ����������η�Χ2��4��8...
        int WillMergeArrayLength = 1;

        int DataLength = SortResults.size();
        for (int i = WillMergeArrayLength; i < DataLength; i *= 2)
        {
            //��һ���ϲ����е����䣬�����Ǳ����䡾left,mid���͡�mid+1��right��
            int left = 0;
            int mid = left + i - 1;
            int right = mid + i;

            //�������
            while(right < DataLength)
            {
                Merge(SortResults, left, mid, right);
                left += 2 * i;
                mid = left + i - 1;
                right = mid + i;
            }

            //����������⴦����Ϊ��������Right�п��ܳ����������Χ��
            if(left < DataLength && mid < DataLength)
            {
                Merge(SortResults, left, mid, DataLength - 1);
            }
        }
    }

    //�ϲ������䡾left,mid�� �� ��mid+1, right��
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