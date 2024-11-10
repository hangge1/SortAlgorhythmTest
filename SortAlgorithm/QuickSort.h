#pragma once

#include "SortAlgo.h"

class QuickSort_Easy : public SortAlgo
{
public:
    static QuickSort_Easy& Get()
    {
        static QuickSort_Easy sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "QuickSort_Easy";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        
        if(SortResults.empty())return;

        SortMain(SortResults, 0, SortResults.size() - 1);
    }

    //���������[startIndex, endIndex]�������Ԫ�أ�Ĭ������
    //���߱�������ʽ
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        if(startIndex >= endIndex || startIndex < 0 || endIndex >= SortArray.size()) return;

        //Print(SortArray, startIndex, endIndex);

        //ѡȡһ��pivot [��򵥵�ѡȡ����ѡ��һ��]
        int pivot = SortArray[startIndex];
        int pivotIndex = startIndex;

        //���仮�� <= �� >
        int currentIndexs = startIndex;
        int lastBePutIndex = endIndex; 
        while(currentIndexs <= lastBePutIndex)
        {  
            if(SortArray[currentIndexs] <= pivot)
            {
                currentIndexs++;
            }
            else
            {
                std::swap(SortArray[currentIndexs], SortArray[lastBePutIndex]);
                lastBePutIndex--;
            }
        }

        //��ʱ�����±�< currentIndexs��Ԫ�ص�ֵ <= pivot
        //������Ҫ��pivot�������㲻����currentIndex�������㲻�ܱ�֤currentIndex�±��ֵ<= pivot, �������ǰһ���Ľ���swap
        std::swap(SortArray[pivotIndex], SortArray[currentIndexs - 1]);
        
   
        //�ݹ�ִ��
        SortMain(SortArray, startIndex, currentIndexs - 2);
        SortMain(SortArray, currentIndexs, endIndex); 
    }
};