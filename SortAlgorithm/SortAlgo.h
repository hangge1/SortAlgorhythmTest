#pragma once

#include <vector>
#include <string>
#include "Tool.h"

template<typename T>
class SortAlgo
{
public:
    static T& Get()
    {
        static T sort;
        return sort;
    }

    virtual std::string Name() const = 0;

    //Ĭ�Ϸ�ʽ������ԭʼ���������򣬿���һ��ԭʼ���ݣ�Ȼ������
    virtual void Sort(const std::vector<int>& InputData, std::vector<int>& SortResults) = 0;
};