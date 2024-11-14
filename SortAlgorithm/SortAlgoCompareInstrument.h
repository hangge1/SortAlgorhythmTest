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
    int Numbers = 10;

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

        TestAllResults TestResults = SortAlgoCompareInstrument::Get().VerifyAlgo(SortAlgoType::Get(), config);

        printf("[%s] ���Խ������: \n\n", SortAlgoType::Get().Name().c_str());
        if(config.IsPrintTemp)
        {
            for (int i = 0; i < TestResults.Results.size(); i++)
            {
                bool isPass = TestResults.GetOneTestPass(i);
                printf("  ��[%d]���Խ�� => %s\n",i, isPass ? "Pass" : "Failed");
            }
        }

        if(config.IsPrintResult)
        {
            //std::cout << "[" << SortAlgoType::Get().Name() << "] ���Խ���� " << "(��" << config.TestTimes << "��)" 
            //    << (TestResults.IsAllPass() ? "ȫ��ͨ��" : "δͨ��") << std::endl;

            printf("  ��%d�ֲ���: %s\n\n", config.TestTimes, (TestResults.IsAllPass() ? "ȫ��ͨ��" : "δͨ��"));
            printf("  ͨ����: %.2f%%\n", TestResults.GetPassRate());
        }

        if(config.IsPrintTime)
        {
            TestResults.StatisticTime();
            std::cout <<  "  ƽ����ʱ: " << TestResults.AverageTime << " ms\n";
            std::cout <<  "  �ܺ�ʱ: " << TestResults.SumTime << " ms\n";
        } 
        
        printf("\n========================== End %s TEST ========================== \n",SortAlgoType::Get().Name().c_str());
        std::cout << std::endl;
    }

private:

    //�������������
    OneTestResult VerifyAlgoOneTime(SortAlgo& ToBeVerifiedSortAlgo, const TestConfigParam& configParam) const
    {
        std::vector<int> BeSortDatas = Tool::Get().GenerateTestData(configParam.Numbers, configParam.MinNum, configParam.MaxNum);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(BeSortDatas, "\nԭʼ����: \n");

        std::vector<int> StandardSortResult;
        StandardSort::Get().Sort(BeSortDatas, StandardSortResult);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(StandardSortResult, "\n��ȷ���: \n");

        std::vector<int> ToBeVerifiedSortAlgoResult;

        TimeStatistics timeStatic;
        ToBeVerifiedSortAlgo.Sort(BeSortDatas, ToBeVerifiedSortAlgoResult);
        timeStatic.Stop();

        if(configParam.IsPrintTemp) Tool::Get().PrintData(ToBeVerifiedSortAlgoResult,"\n" + ToBeVerifiedSortAlgo.Name() + "Ӧ�ý��: \n");

        return { StandardSortResult == ToBeVerifiedSortAlgoResult, timeStatic.GetTime_ms() };
    }

    //������������
    TestAllResults VerifyAlgo(SortAlgo& ToBeVerifiedSortAlgo, const TestConfigParam& configParam) const
    {
        TestAllResults testResuls;

        int i = 0;
        while(i < configParam.TestTimes)
        {
            if(configParam.IsPrintTemp) std::cout << "------------------ Begin Test[" << i << "] ------------------ \n";

            OneTestResult oneResult = VerifyAlgoOneTime(ToBeVerifiedSortAlgo, configParam);
            testResuls.Results.emplace_back(oneResult);

            //AverageTime += testResult.UseTime / (float)configParam.TestTimes;
            //SumTime += testResult.UseTime;
            //testResuls.emplace_back(testResult.IsPass);

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