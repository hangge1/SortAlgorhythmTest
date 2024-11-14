#pragma once

#include <iostream>
#include <chrono>

#include "SortAlgo.h"
#include "StandardSort.h"
#include "TimeStatistics.h"

//�������ò���
struct TestConfigParam
{
    //���Դ���
    int TestTimes = 1;

    //�������ݸ���
    int Numbers = 5;

    //������Сֵ
    int MinNum = 1;

    //�������ֵ
    int MaxNum = 20;

    //�Ƿ��ӡ��ʱ
    bool IsPrintTime = true;

    //�Ƿ��ӡ�м����
    bool IsPrintTemp = false;

    //�Ƿ��ӡ���Խ��
    bool IsPrintResult = true;
};

//���β��Խ��
struct OneTestResult
{
    bool IsPass = false; //�Ƿ�ͨ��
    float SpeedTime = 0.0f; //����ʱ��(ms)
};

//һ��ִ�е����в��Խ������
struct TestAllResults
{
    std::vector<OneTestResult> Results;

    //������������StatisticTime() ���ú󱻸�ֵ
    float SumTime = 0.0f;
    float AverageTime = 0.0f;
public:
    bool GetOneTestPass(int index)
    {
        if(index < 0 || index >= Results.size())
        {
            assert(false);
        }
        return Results[index].IsPass;
    }

    bool IsAllPass() const
    {
        bool IsAllPass = true;
        for (int i = 0; i < Results.size(); i++)
        {
            if(!Results[i].IsPass)
            {
                IsAllPass = false;
                break;
            }
        }
        return IsAllPass;
    }

    float GetPassRate() const
    {
        int passCount = 0;
        for (int i = 0; i < Results.size(); i++)
        {
            if(Results[i].IsPass)
            {
                passCount++;
            }
        }

        return (float)passCount / Results.size() * 100;
    }

    void StatisticTime()
    {
        SumTime = GetSumTime();

        if(Results.empty()) AverageTime = 0.0f;
        else AverageTime = GetSumTime() / Results.size();
    }

    float GetAverageTime() const
    {
        if(Results.empty()) return 0.0f;

        return GetSumTime() / Results.size();
    }

    float GetSumTime() const
    {
        float sumTime = 0.0f;
        for (const OneTestResult& res : Results)
        {
            sumTime += res.SpeedTime;
        }
        return sumTime;
    }

    //�����ӡ���
    void PrintEveryTestResult() const
    {
        for (int i = 0; i < Results.size(); i++)
        {
            printf("  ��[%d]���Խ�� => %s\n",i, Results[i].IsPass ? "Pass" : "Failed");
        }
    }

    void PrintAllPassInfo(int TestTimes) const
    {
        printf("  ��%d�ֲ���: %s\n\n", TestTimes, IsAllPass() ? "ȫ��ͨ��" : "δͨ��");
        printf("  ͨ����: %.2f%%\n", GetPassRate());
    }

    void PrintSpeedTimeInfo() 
    {
        StatisticTime();
        std::cout <<  "  ƽ����ʱ: " << AverageTime << " ms\n";
        std::cout <<  "  �ܺ�ʱ: " << SumTime << " ms\n";
    }
};

//�����㷨�Ƚϻ���
class SortAlgoCompareInstrument
{
public:
    //Ĭ�ϲ������ò���
    constexpr static TestConfigParam DefaultTestConfig;

    static SortAlgoCompareInstrument& Get()
    {
        static SortAlgoCompareInstrument self;
        return self;
    }

    //��д����������Ĭ������
    template<typename SortAlgoType>
    void Execute_Test(const TestConfigParam& config = DefaultTestConfig) const
    {
        printf("========================== Begin %s TEST ========================== \n\n",SortAlgoType::Get().Name().c_str());

        TestAllResults TestResults = SortAlgoCompareInstrument::Get().VerifySortManyTime<SortAlgoType>(config);

        printf("[%s] ���Խ������: \n\n", SortAlgoType::Get().Name().c_str());
        if(config.IsPrintTemp)
        {
            TestResults.PrintEveryTestResult();
        }

        if(config.IsPrintResult)
        {
            TestResults.PrintAllPassInfo(config.TestTimes);
        }

        if(config.IsPrintTime)
        {
            TestResults.PrintSpeedTimeInfo();
        }
        
        printf("\n========================== End %s TEST ========================== \n\n",SortAlgoType::Get().Name().c_str());
    }

private:

    //��������������㷨��֤
    template<typename SortAlgoType>
    OneTestResult VerifySortOneTime(const TestConfigParam& configParam) const
    {
        std::vector<int> BeSortDatas = Tool::Get().GenerateTestData(configParam.Numbers, configParam.MinNum, configParam.MaxNum);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(BeSortDatas, "\nԭʼ����: \n");

        std::vector<int> StandardSortResult;
        StandardSort::Get().Sort(BeSortDatas, StandardSortResult);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(StandardSortResult, "\n��ȷ���: \n");

        std::vector<int> ToBeVerifiedSortAlgoResult;

        TimeStatistics timeStatic;
        SortAlgoType::Get().Sort(BeSortDatas, ToBeVerifiedSortAlgoResult);
        timeStatic.Stop();

        if(configParam.IsPrintTemp) Tool::Get().PrintData(ToBeVerifiedSortAlgoResult,"\n" + SortAlgoType::Get().Name() + "Ӧ�ý��: \n");

        return { StandardSortResult == ToBeVerifiedSortAlgoResult, timeStatic.GetTime_ms() };
    }

    //�������������㷨��֤
    template<typename SortAlgoType>
    TestAllResults VerifySortManyTime(const TestConfigParam& configParam) const
    {
        TestAllResults testResuls;

        int i = 0;
        while(i < configParam.TestTimes)
        {
            if(configParam.IsPrintTemp) std::cout << "------------------ Begin Test[" << i << "] ------------------ \n";

            testResuls.Results.emplace_back(VerifySortOneTime<SortAlgoType>(configParam));

            if(configParam.IsPrintTemp) std::cout << "------------------ End Test[" << i << "] ------------------\n\n";
            i++;
        }

        return testResuls;
    }

private:

    SortAlgoCompareInstrument() = default;
    ~SortAlgoCompareInstrument() = default;

    SortAlgoCompareInstrument(const SortAlgoCompareInstrument&) = delete;
    SortAlgoCompareInstrument& operator=(const SortAlgoCompareInstrument&) = delete;

    SortAlgoCompareInstrument(SortAlgoCompareInstrument&&) = delete;
    SortAlgoCompareInstrument& operator=(SortAlgoCompareInstrument&&) = delete;
};