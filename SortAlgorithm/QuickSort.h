#pragma once

#include "SortAlgo.h"
#include <stack>

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

        //��2��[Medium3]  Ѱ��start��end���е㣬ֵ��С����Ϊpivot
        int pivotIndex = Medium3(SortArray, startIndex, endIndex);
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

    int Medium3(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        int startValue = SortArray[startIndex];
        int middleIndex = startIndex + (endIndex - startIndex) / 2;
        int middleValue = SortArray[middleIndex];
        int endValue = SortArray[endIndex];
        int pivotIndex = startValue < middleValue ? startIndex : (middleValue < endValue ? middleIndex : endIndex);

        return pivotIndex;
    }
};


// �Ż�Ϊ�ǵݹ�汾
class QuickSort_UnRecursive : public SortAlgo
{
public:
    struct Range
    {
        int start;
        int end;

        Range(int s = 0, int e = 0)
            :start(s), end(e)
        {}
    };

    static QuickSort_UnRecursive& Get()
    {
        static QuickSort_UnRecursive sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "QuickSort_UnRecursive";
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
        //Print(SortArray, startIndex, endIndex);
     
        std::stack<Range> RangeStack;
        RangeStack.emplace(startIndex, endIndex);

        while(!RangeStack.empty())
        {
            Range IndexRange = RangeStack.top();
            RangeStack.pop();

            int sIndex = IndexRange.start;
            int eIndex = IndexRange.end;
            if(sIndex >= eIndex || sIndex < 0 || eIndex >= SortArray.size()) continue;


            //[Medium3]
            int pivotIndex = Medium3(SortArray, sIndex, eIndex);
            int pivot = SortArray[pivotIndex];
            std::swap(SortArray[pivotIndex], SortArray[sIndex]);

            int currentIndexs = sIndex + 1;
            int lastBePutIndex = eIndex; 
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
            
            std::swap(SortArray[sIndex], SortArray[currentIndexs - 1]);
            
            RangeStack.emplace(sIndex, currentIndexs - 2);
            RangeStack.emplace(currentIndexs, eIndex);
        }
    }

    int Medium3(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        int startValue = SortArray[startIndex];
        int middleIndex = startIndex + (endIndex - startIndex) / 2;
        int middleValue = SortArray[middleIndex];
        int endValue = SortArray[endIndex];
        int pivotIndex = startValue < middleValue ? startIndex : (middleValue < endValue ? middleIndex : endIndex);

        return pivotIndex;
    }
};