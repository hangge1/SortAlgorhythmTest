#pragma once

#include "SortAlgo.h"
#include <stack>

/*
    ���������׳ƿ��š�
    1�����ȶ�
    2��ʱ�临�Ӷ� O(N*LogN)
    3���ռ临�Ӷ� O(logN) ���ݹ�ջ�� 
    4���������죬������չ���������ȶ��ԣ���ѡ�������㷨��
    5�������������ʵ���㷨��
    ��ǰ���ֶ��ǵݹ�д����ֻ��pivotѡ�������  �������ǵ���д����
        (1) ��һ��QuickSort_Easy  ��ÿ�ζ�ѡ������ĵ�һ��Ԫ����Ϊpivot
        (2) �ڶ���QuickSort_RandomPivot  ��ÿ�ζ�ѡ����������һ��Ԫ����Ϊpivot
        (3) ������QuickSort_Medium3Pivot  ��Medium3��ѡ��ͷ��β���м����λ����Ϊpivot
        (4) �������ǵ���д�� QuickSort_UnRecursive
*/


class QuickSort_Easy : public SortAlgo<QuickSort_Easy>
{
public:
    virtual std::string Name() const override
    {
        return "QuickSort_Easy";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        
        if(SortResults.empty())return;

        SortMain(SortResults, 0, (int)SortResults.size() - 1);
    }

    //���������[startIndex, endIndex]�������Ԫ�أ�Ĭ������
    //���߱�������ʽ
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        if(startIndex >= endIndex || startIndex < 0 || endIndex >= SortArray.size()) return;

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
class QuickSort_RandomPivot : public SortAlgo<QuickSort_RandomPivot>
{
public:
    virtual std::string Name() const override
    {
        return "QuickSort_RandomPivot";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;       
        if(SortResults.empty())
            return;

        SortMain(SortResults, 0, (int)SortResults.size() - 1);
    }

    //��������ġ�startIndex, endIndex���������Ԫ�أ�Ĭ������
    //���߱�������ʽ
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        if(startIndex >= endIndex || startIndex < 0 || endIndex >= SortArray.size()) 
            return;

        //[���ѡȡ]
        int pivotIndex = Tool::Get().GetRandom(startIndex, endIndex);
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

// �Ż�Pivot��ѡȡ(Medium3)
class QuickSort_Medium3Pivot : public SortAlgo<QuickSort_Medium3Pivot>
{
public:
    virtual std::string Name() const override
    {
        return "QuickSort_Medium3Pivot";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        
        if(SortResults.empty())return;

        SortMain(SortResults, 0, (int)SortResults.size() - 1);
    }

    //��������ġ�startIndex, endIndex���������Ԫ�أ�Ĭ������
    //���߱�������ʽ
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
        if(startIndex >= endIndex || startIndex < 0 || endIndex >= SortArray.size()) return;

        //��2��[Medium3]  Ѱ��start��end���е㣬����λ����Ϊpivot
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
        struct helper
        {
            int v;
            int index;
        };

        int middleIndex = startIndex + (endIndex - startIndex) / 2;

        helper start { SortArray[startIndex], startIndex};
        helper middle { SortArray[middleIndex], middleIndex};
        helper end { SortArray[endIndex], endIndex};

        if(start.v < middle.v)
        {
            std::swap(start,middle);
        }

        if(start.v < end.v)
        {
            std::swap(start,end);
        }

        if(middle.v < end.v)
        {
            std::swap(middle,end);
        }

        return middle.index;
    }
};


// �Ż�Ϊ�ǵݹ�汾
class QuickSort_UnRecursive : public SortAlgo<QuickSort_UnRecursive>
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

    virtual std::string Name() const override
    {
        return "QuickSort_UnRecursive";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        
        if(SortResults.empty())return;

        SortMain(SortResults, 0, (int)SortResults.size() - 1);
    }

    //���������[startIndex, endIndex]�������Ԫ�أ�Ĭ������
    //���߱�������ʽ
    void SortMain(std::vector<int>& SortArray, int startIndex, int endIndex)
    {
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