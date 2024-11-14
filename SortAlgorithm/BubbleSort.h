
#pragma once

#include "SortAlgo.h"

/*
    ð������
    1���ȶ�
    2��ʱ�临�Ӷ� O(N^2)����������������ΪO(N)��
    3���ռ临�Ӷ� O(1)
    4�������������д��
    (1) ��һ����С������д��
    (2) �ڶ�������flag�Ż�������������ֹѭ��
    (3) �����ֿ��ǲ���ð�ݣ��������ѭ���ķ�Χ�ǲ�����С��

    TODO: ��β�����򣬸��߼����Ż���˼·���ǲ�����ǰ����ð�ݣ�Ҳ�Ӻ���ǰð�ݡ�
*/


// the simplest way to write Bubble Sort 
// It has not been optimized and theoretically is relatively slow
class BubbleSort_Easy : public SortAlgo
{
public:
    static BubbleSort_Easy& Get()
    {
        static BubbleSort_Easy sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "BubbleSort_Easy";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;

        //ÿһ��ð�ݵ����еĽ����±�
        for (int i = SortResults.size() - 1; i >= 0; i--)
        {
            //��Դ�[0, i]���Ϻ���һ��Ԫ�رȽϺͽ���
            for (int j = 0; j < i; j++)
            {
                if(SortResults[j] > SortResults[j + 1])
                {
                    std::swap(SortResults[j], SortResults[j + 1]);
                }
            }
        }
    }
};

// use a flag to Optimize the situation where the sequence is basically ordered
class BubbleSort_Flag_Opt : public SortAlgo
{
public:
    static BubbleSort_Flag_Opt& Get()
    {
        static BubbleSort_Flag_Opt sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "BubbleSort_Flag_Opt";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;

        //ÿһ��ð�ݵ����еĽ����±�
        for (int i = SortResults.size() - 1; i >= 0; i--)
        {
            bool HasSwap = false; 
            //��Դ�[0, i]���Ϻ���һ��Ԫ�رȽϺͽ���
            for (int j = 0; j < i; j++)
            {
                if(SortResults[j] > SortResults[j + 1])
                {
                    std::swap(SortResults[j], SortResults[j + 1]);
                    HasSwap = true;
                }
            }

            if(!HasSwap)break;
        }
    }
};

// Optimize the number of iterations for each sequence
class BubbleSort_ForTime_Opt : public SortAlgo
{
public:
    static BubbleSort_ForTime_Opt& Get()
    {
        static BubbleSort_ForTime_Opt sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "BubbleSort_ForTime_Opt";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;

        //ÿһ��ð�ݵ����еĽ����±�
        int HasSortedCount = 0;
        for (int i = SortResults.size() - 1 - HasSortedCount; i >= 0; i--)
        {
            bool HasSwap = false; 
            //��Դ�[0, i]���Ϻ���һ��Ԫ�رȽϺͽ���
            for (int j = 0; j < i; j++)
            {
                if(SortResults[j] > SortResults[j + 1])
                {
                    std::swap(SortResults[j], SortResults[j + 1]);
                    HasSwap = true;
                }
            }

            HasSortedCount++;
            if(!HasSwap)break;
        }
    }
};

//TODO ��β���㷨