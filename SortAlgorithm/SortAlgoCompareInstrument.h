#pragma once

#include <iostream>
#include <chrono>
#include <random>

#include "SortAlgo.h"
#include "StandardSort.h"


struct SortAlgoCompareInstrumentConfig
{
    int TestTimes = 1;
    int Numbers = 10;
    int MinNum = 1;
    int MaxNum = 20;
    bool IsPrintTime = true;
    bool InIsPrintTemp = true;
};

class SortAlgoCompareInstrument
{
public:
    
    //��������������ָ���
    inline static int Default_Test_Number_Count = 10;
    inline static int Default_Test_MinNumber = 1;
    inline static int Default_Test_MaxNumber = 20;

    long long LastLoopSpeedTime = 0;
    double AverageTime = 0.0;
    double SumTime = 0.0;

    bool IsPrintTemp = false;

    static SortAlgoCompareInstrument& Get()
    {
        static SortAlgoCompareInstrument self;
        return self;
    }

    template<typename SortAlgoType>
    void Execute_Test(const SortAlgoCompareInstrumentConfig& config)
    {
        Execute_Test<SortAlgoType>(config.TestTimes, config.Numbers, config.MinNum, config.MaxNum, config.IsPrintTime, config.InIsPrintTemp);
    }

    template<typename SortAlgoType>
    void Execute_Test(int TestTimes, int Numbers, int MinNum, int MaxNum, bool IsPrintTime = true, bool InIsPrintTemp = true)
    {
        IsPrintTemp = InIsPrintTemp;
        SumTime = 0;
        AverageTime = 0;
        SortAlgoCompareInstrument::Default_Test_Number_Count = Numbers;
        SortAlgoCompareInstrument::Default_Test_MinNumber = MinNum;
        SortAlgoCompareInstrument::Default_Test_MaxNumber = MaxNum;
        std::vector<bool> Results = SortAlgoCompareInstrument::Get().VerifyAlgo(SortAlgoType::Get(), TestTimes);

        if(InIsPrintTemp)
        {
            for (int i = 0; i < Results.size(); i++)
            {
                std::cout << "��[" << i << "]���Խ�� => " << (Results[i] ? "OK" : "Failed") << std::endl;
            }
        }

        if(IsPrintTime)
        {
            std::cout << "[" << SortAlgoType::Get().Name() << "]ƽ����ʱ: " << AverageTime / 1000.0 << " ms\n";
            std::cout << "[" << SortAlgoType::Get().Name() << "]�ܺ�ʱ: " << SumTime / 1000.0 << " ms\n";
        } 
        
        std::cout << std::endl;
    }

    //�������������
    bool VerifyAlgoOneTime(SortAlgo& ToBeVerifiedSortAlgo)
    {      
        std::vector<int> BeSortDatas = GenerateTestData(Default_Test_Number_Count, Default_Test_MinNumber, Default_Test_MaxNumber);
        if(IsPrintTemp) PrintData(BeSortDatas, "����ǰ: \n");

        std::vector<int> StandardSortResult;
        StandardSort::Get().Sort(BeSortDatas, StandardSortResult);
        if(IsPrintTemp) PrintData(StandardSortResult, StandardSort::Get().Name() + "�����: \n");

        std::vector<int> ToBeVerifiedSortAlgoResult;

        auto start = std::chrono::high_resolution_clock::now();
        ToBeVerifiedSortAlgo.Sort(BeSortDatas, ToBeVerifiedSortAlgoResult);
        LastLoopSpeedTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();

        if(IsPrintTemp) PrintData(ToBeVerifiedSortAlgoResult, ToBeVerifiedSortAlgo.Name() + "�����: \n");

        return StandardSortResult == ToBeVerifiedSortAlgoResult;
    }

    //������������
    std::vector<bool> VerifyAlgo(SortAlgo& ToBeVerifiedSortAlgo, int testTimes = 5)
    {
        std::vector<bool> testResuls;

        int i = 0;
        while(i < testTimes)
        {
            if(IsPrintTemp) std::cout << "===Test[" << i << "]===\n";
            bool testFlag = VerifyAlgoOneTime(ToBeVerifiedSortAlgo);
            AverageTime += LastLoopSpeedTime / (double)testTimes;
            SumTime += LastLoopSpeedTime;

            testResuls.emplace_back(testFlag);
            if(IsPrintTemp) std::cout << "---------------------------------------------------------------\n";
            i++;
        }

        return testResuls;
    }


    std::vector<int> GenerateTestData(int NumberOfRandomData, int MinNum = 0, int MaxNum = 99) const
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(MinNum, MaxNum);

        std::vector<int> result;
        for (int i = 0; i < NumberOfRandomData; i++)
        {
            result.emplace_back(distrib(gen));
        }

        return result;
    }

    void PrintData(const std::vector<int>& Data, std::string prefixWords = "", std::string postWords = "\n") const
    {
        std::cout << prefixWords;
        for (int num : Data)
        {
            std::cout << num << " ";
        }
        std::cout << postWords;
    }

private:

    SortAlgoCompareInstrument()
    {
        
    }

    SortAlgoCompareInstrument(const SortAlgoCompareInstrument&) = delete;
    SortAlgoCompareInstrument& operator=(const SortAlgoCompareInstrument&) = delete;
};