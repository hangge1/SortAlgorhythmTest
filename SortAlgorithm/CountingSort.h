#pragma once

#include "SortAlgo.h"

/*
    ��������
    1���ȶ� 
    2��ʱ�临�Ӷ� O(N + k) ��k��ʾ���������������С��Ҳ�����������ֵ����Сֵ�Ĳ�ࡿ
    3���ռ临�Ӷ� O(k)
    4��Ӧ�ó����� �������ر�󣬵�������������ȡֵ��Χ��С���磺ͳ��ȫ���߿�����������ȫ���˿�����������
    5���򵥽���һ��д��
    ��1���������;�����ֵ
        �������ݵ������ȶ���Ҳ����Ҫ��ֻ��Ҫһ���������飬��������վͿ�
    ��2�������������Զ���������
        �������������ȶ����Ǻ���Ҫ�ģ����Ǹ����ľ��Ǳ����ȶ��Եı�׼��������Ҫ����Counting��������ۼ����飬Ȼ��Ӻ���ǰ����ԭ�������
    ��3��ע��һ�㣬����д����֧�ָ����ģ�Ҳ����������һ��Ҫ��0��ʼ��   
*/

class CountingSort : public SortAlgo<CountingSort>
{
public:
    virtual std::string Name() const override
    {
        return "CountingSort";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty()) return;

        //1 ͳ�����ֵ����Сֵ
        int maxNum = INT_MIN;
        int minNum = INT_MAX;
        for (int i = 0; i < SortResults.size(); i++)
        {
           if(SortResults[i] > maxNum) maxNum = SortResults[i];
           if(SortResults[i] < minNum) minNum = SortResults[i];
        }

        //2 ���ټ������飬��������
        std::vector<int> Counting(maxNum - minNum + 1, 0);
        for (int i = 0; i < SortResults.size(); i++)
        {
           int v = SortResults[i];
           Counting[v - minNum]++;
        }

        //3 �����ۼ�����
        for (int i = 1; i < Counting.size(); i++)
        {
            Counting[i] += Counting[i-1];
        }

        //4 ���ٽ�����飬�Ӻ���ǰ����ԭ���ݣ������ۼ�����ֵ������д
        std::vector<int> tmp(SortResults.size());
        for (int i = (int)SortResults.size() - 1; i >= 0; i--)
        {
           int v = SortResults[i];
           int pos = Counting[v - minNum] - 1;
           tmp[pos] = v;

           Counting[v - minNum]--;
        }

        SortResults = tmp;
    }
};