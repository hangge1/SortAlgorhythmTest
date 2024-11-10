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
        int currentIndexs = startIndex + 1;
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
        std::swap(SortArray[startIndex], SortArray[currentIndexs - 1]);
        
   
        //�ݹ�ִ��
        SortMain(SortArray, startIndex, currentIndexs - 2);
        SortMain(SortArray, currentIndexs, endIndex); 
    }
};

// �Ż�Pivot��ѡȡ(���ѡȡ)
class QuickSort_Opt_SelectPivot : public SortAlgo
{
public:
    static QuickSort_Opt_SelectPivot& Get()
    {
        static QuickSort_Opt_SelectPivot sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "QuickSort_Opt_SelectPivot";
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

        //��1��[���ѡȡ]
        //int pivotIndex = Tool::Get().GetRandom(startIndex, endIndex);
        //int pivot = SortArray[pivotIndex];

        //��2��[Medium3]
        int startValue = SortArray[startIndex];
        int middleIndex = startIndex + (endIndex - startIndex) / 2;
        int middleValue = SortArray[middleIndex];
        int endValue = SortArray[endIndex];
        int pivotIndex = startValue < middleValue ? startIndex : (middleValue < endValue ? middleIndex : endIndex);
        int pivot = SortArray[pivotIndex];

        std::swap(SortArray[pivotIndex], SortArray[startIndex]);
        
        //���仮�� <= �� >
        int currentIndexs = startIndex + 1;
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

        std::swap(SortArray[startIndex], SortArray[currentIndexs - 1]);
        
        SortMain(SortArray, startIndex, currentIndexs - 2);
        SortMain(SortArray, currentIndexs, endIndex); 
    }
};