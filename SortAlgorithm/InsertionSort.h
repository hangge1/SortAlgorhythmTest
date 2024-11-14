#pragma once

#include "SortAlgo.h"

/*
    ֱ�Ӳ�������
    1���ȶ� ���ȽϹ��̣��������������ܽ�������Ȼ���ȶ���
    2��ʱ�临�Ӷ� O(N^2)����������������ΪO(N)��
    3���ռ临�Ӷ� O(1)
    4���������Ƚ�С����������������й��̵���ѡӦ���㷨
    5���Ż�˼·
     (1) �����㷨�����������а�˳���ҵ��Լ���λ�ò��룻 ������ö��ַ��ӿ����λ�õĹ��̣�
*/

class InsertionSort : public SortAlgo<InsertionSort>
{
public:
    virtual std::string Name() const override
    {
        return "InsertionSort";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        for (int i = 1; i < SortResults.size(); i++)
        {
            //���ϸ�֮ǰ������Ԫ�رȽϴ�С, If < ǰ��
            int CurrentCompareElement = SortResults[i];
            int InsetIndex = i - 1;
            while(InsetIndex >= 0 && CurrentCompareElement < SortResults[InsetIndex])
            {
                SortResults[InsetIndex + 1] = SortResults[InsetIndex];
                InsetIndex--;
            }

            SortResults[InsetIndex + 1] = CurrentCompareElement;
        }
    }
};