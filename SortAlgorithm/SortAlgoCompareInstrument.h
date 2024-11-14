#pragma once

#include <iostream>
#include <chrono>

#include "SortAlgo.h"
#include "StandardSort.h"


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

struct OneTestResult
{
    bool IsPass = false;
    float SpeedTime = 0.0f;
};

struct TestAllResults
{
    std::vector<OneTestResult> Results;
    
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

//ʱ��ͳ���õ���
class TimeStatistics
{
public:
    TimeStatistics()
    {
        SetStartPoint();
    }

    ~TimeStatistics()
    {
        Stop();
    }

    float GetTime_s() const
    {
        return GetTime_us() / 1000000.f;
    }

    float GetTime_ms() const
    {
        return GetTime_us() / 1000.f;
    }

    //����Ѿ�ֹͣ���ͷ���ֹͣʱ��ͳ��ʱ�䣬���򷵻�ʵʱʱ��!
    float GetTime_us() const
    {
        if(HasStop) return Duration;
        
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }

    void Stop()
    {
        if(!HasStop) HasStop = true;
        Duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    }

    void Restart()
    {
        SetStartPoint();
        HasStop = false;
    }
private:
    void SetStartPoint()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    std::chrono::high_resolution_clock::time_point start;
    long long Duration = 0;
    bool HasStop = false;
};

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
    void Execute_Test(const TestConfigParam& config = DefaultTestConfig)
    {
        TestAllResults TestResults = SortAlgoCompareInstrument::Get().VerifyAlgo(SortAlgoType::Get(), config);

        if(config.IsPrintTemp)
        {
            for (int i = 0; i < TestResults.Results.size(); i++)
            {
                bool isPass = TestResults.GetOneTestPass(i);
                std::cout << "��[" << i << "]���Խ�� => " << (isPass ? "OK" : "Failed") << std::endl;
            }
        }

        if(config.IsPrintResult)
        {
            std::cout << "[" << SortAlgoType::Get().Name() << "] ���Խ���� " << "(��" << config.TestTimes << "��)" 
                << (TestResults.IsAllPass() ? "ȫ��ͨ��" : "δͨ��") << std::endl;
        }

        if(config.IsPrintTime)
        {
            TestResults.StatisticTime();
            std::cout << "[" << SortAlgoType::Get().Name() << "] ƽ����ʱ: " << TestResults.AverageTime << " ms\n";
            std::cout << "[" << SortAlgoType::Get().Name() << "] �ܺ�ʱ: " << TestResults.SumTime << " ms\n";
        } 
        
        std::cout << std::endl;
    }


    //�������������
    OneTestResult VerifyAlgoOneTime(SortAlgo& ToBeVerifiedSortAlgo, const TestConfigParam& configParam)
    {
        std::vector<int> BeSortDatas = GenerateTestData(configParam.Numbers, configParam.MinNum, configParam.MaxNum);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(BeSortDatas, "����ǰ: \n");

        std::vector<int> StandardSortResult;
        StandardSort::Get().Sort(BeSortDatas, StandardSortResult);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(StandardSortResult, StandardSort::Get().Name() + "�����: \n");

        std::vector<int> ToBeVerifiedSortAlgoResult;

        TimeStatistics timeStatic;
        ToBeVerifiedSortAlgo.Sort(BeSortDatas, ToBeVerifiedSortAlgoResult);
        timeStatic.Stop();

        if(configParam.IsPrintTemp) Tool::Get().PrintData(ToBeVerifiedSortAlgoResult, ToBeVerifiedSortAlgo.Name() + "�����: \n");

        return { StandardSortResult == ToBeVerifiedSortAlgoResult, timeStatic.GetTime_ms() };
    }

    //������������
    TestAllResults VerifyAlgo(SortAlgo& ToBeVerifiedSortAlgo, const TestConfigParam& configParam)
    {
        TestAllResults testResuls;

        int i = 0;
        while(i < configParam.TestTimes)
        {
            if(configParam.IsPrintTemp) std::cout << "===Test[" << i << "]===\n";

            OneTestResult oneResult = VerifyAlgoOneTime(ToBeVerifiedSortAlgo, configParam);
            testResuls.Results.emplace_back(oneResult);

            //AverageTime += testResult.UseTime / (float)configParam.TestTimes;
            //SumTime += testResult.UseTime;
            //testResuls.emplace_back(testResult.IsPass);

            if(configParam.IsPrintTemp) std::cout << "---------------------------------------------------------------\n";
            i++;
        }

        return testResuls;
    }


    std::vector<int> GenerateTestData(int NumberOfRandomData, int MinNum = 0, int MaxNum = 99) const
    {
        std::vector<int> result;
        for (int i = 0; i < NumberOfRandomData; i++)
        {
            result.emplace_back(Tool::Get().GetRandom(MinNum, MaxNum));
        }

        return result;
    }

   

private:

    SortAlgoCompareInstrument()
    {
        
    }

    SortAlgoCompareInstrument(const SortAlgoCompareInstrument&) = delete;
    SortAlgoCompareInstrument& operator=(const SortAlgoCompareInstrument&) = delete;
};