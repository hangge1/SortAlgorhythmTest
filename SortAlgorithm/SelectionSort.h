#pragma once

#pragma once


class SelectionSort : public SortAlgo
{
public:
    static SelectionSort& Get()
    {
        static SelectionSort sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "SelectionSort";
    }

    //ºŸ…Ë…˝–Ú
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