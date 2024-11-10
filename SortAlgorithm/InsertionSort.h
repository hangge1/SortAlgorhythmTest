#pragma once

class InsertionSort : public SortAlgo
{
public:
    static InsertionSort& Get()
    {
        static InsertionSort sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "InsertionSort";
    }

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        for (int i = 1; i < SortResults.size(); i++)
        {
            //不断跟之前的所有元素比较大小, If < 前移
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