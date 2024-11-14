#pragma once

#pragma once

#include "SortAlgo.h"

/*
    ��������
    1���ȶ� 
    2��ʱ�临�Ӷ� O(N + k) ��k��ʾ���������������С��Ҳ�����������ֵ����Сֵ�Ĳ�ࡿ
    3���ռ临�Ӷ� O(k)
    4��Ӧ�ó����� ������10���ƵķǸ�����
    5���򵥽���һ��д��         
*/

class RadixSort : public SortAlgo
{
public:
    static RadixSort& Get()
    {
        static RadixSort sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "RadixSort";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty()) return;

        //����10������������λ��  0-999���ݷ�Χ�ķǸ�����
        RadixSortMain(SortResults, 10, 3);
    }

    //Base��ʾ���ֵĽ���,�����10����,����Ҫ0-9��10��Ͱ
    //MaxBits��ʾ���ݵ����λ��,����10��������1000,���λ������4,ǧλ,��λ,ʮλ,��λ
    void RadixSortMain(std::vector<int>& SortDatas, int Base, int MaxBits)
    {
        int size = (int)SortDatas.size();
        int Offset = 1;

        std::vector<int> bucksHelper(Base, 0); //����Ͱ�ṹ
        std::vector<int> tmp(size, 0); //�洢��λ������
        for(int i = MaxBits; i >= 0; i--)
        {
            std::fill(tmp.begin(), tmp.end(), 0);
            std::fill(bucksHelper.begin(), bucksHelper.end(), 0);
            
            for (int k = 0; k < size; k++)
            {
                //1 ȡ���ֵ�ĳλ
                int bitValue = (SortDatas[k] / Offset) % Base;
                //2 �ӽ�Ͱ��
                bucksHelper[bitValue]++;
            }

            //3 �����ۼ�����
            for (int k = 1; k < Base; k++)
            {
                bucksHelper[k] += bucksHelper[k-1];
            }

            //4 �Ӻ���ǰ����ԭ����,���л�ԭ
            for (int k = size - 1; k >= 0; k--)
            {
                //1 ȡ���ֵ�ĳλ
                int bitValue = (SortDatas[k] / Offset) % Base;

                //2 ����λ��
                int pos = bucksHelper[bitValue] - 1;

                //3 �ӽ���ʱ����
                tmp[pos] = SortDatas[k];

                //4 �ۼ�����-1
                bucksHelper[bitValue]--;
            }

            //5 ����ԭ����
            SortDatas = tmp;

            //Ϊ�˻����һλ���øı�ƫ��
            Offset *= Base;
        }
    }
};