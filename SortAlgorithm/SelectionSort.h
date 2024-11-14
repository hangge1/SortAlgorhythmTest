#pragma once

#include "SortAlgo.h"

/*
    ѡ������
    1�����ȶ�
    2��ʱ�临�Ӷ� O(N^2)
    3���ռ临�Ӷ� O(1)
    4�����������������ã�ֻ�ǽ�ѧ�͵������㷨
    5���Ż�˼·
     (1) �����㷨ÿ���ҵ���Сֵ������ͷ���� ���Կ���һ���Ա����ҵ����ֵ����Сֵ���ֱ𽻻���ͷ����β����
*/

class SelectionSort : public SortAlgo<SelectionSort>
{
public:
    virtual std::string Name() const override
    {
        return "SelectionSort";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        for (int i = 0; i < SortResults.size(); i++)
        {
           int minElement = SortResults[i];
           int minIndex = i;

           for (int j = i + 1; j < SortResults.size(); j++)
           {
                if(SortResults[j] < minElement)
                {
                    minIndex = j;
                    minElement = SortResults[j];
                }
           }

           if(i != minIndex) std::swap(SortResults[minIndex], SortResults[i]);
        }
    }
};