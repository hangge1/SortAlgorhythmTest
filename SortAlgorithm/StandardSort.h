#pragma once
#include <algorithm>

//std::sort 提供的排序算法！
class StandardSort : public SortAlgo<StandardSort>
{
public:
    virtual std::string Name() const override
    {
        return "StandardSort";
    }

    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults.clear();
        SortResults = InputDatas;
        std::sort (SortResults.begin(), SortResults.end());   
    }
};