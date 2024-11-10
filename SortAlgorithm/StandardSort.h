#pragma once
#include <algorithm>

class StandardSort : public SortAlgo
{
public:
    static StandardSort& Get()
    {
        static StandardSort sort;
        return sort;
    }

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