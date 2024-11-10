#pragma once

#include <vector>
#include <string>


class SortAlgo
{
public:
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) = 0;

    virtual std::string Name() const = 0;
};