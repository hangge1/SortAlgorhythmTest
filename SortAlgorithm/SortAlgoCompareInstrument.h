#pragma once

#include <iostream>
#include <chrono>

#include "SortAlgo.h"
#include "StandardSort.h"


struct TestConfigParam
{
    //测试次数
    int TestTimes = 1;

    //样本数据个数
    int Numbers = 10;

    //数据最小值
    int MinNum = 1;

    //数据最大值
    int MaxNum = 20;

    //是否打印耗时
    bool IsPrintTime = true;

    //是否打印中间过程
    bool IsPrintTemp = false;

    //是否打印测试结果
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

//时间统计用的类
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

    //如果已经停止，就返回停止时的统计时间，否则返回实时时间!
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
    //默认测试配置参数
    constexpr static TestConfigParam DefaultTestConfig;

    static SortAlgoCompareInstrument& Get()
    {
        static SortAlgoCompareInstrument self;
        return self;
    }

    //不写参数，就是默认配置
    template<typename SortAlgoType>
    void Execute_Test(const TestConfigParam& config = DefaultTestConfig)
    {
        TestAllResults TestResults = SortAlgoCompareInstrument::Get().VerifyAlgo(SortAlgoType::Get(), config);

        if(config.IsPrintTemp)
        {
            for (int i = 0; i < TestResults.Results.size(); i++)
            {
                bool isPass = TestResults.GetOneTestPass(i);
                std::cout << "第[" << i << "]测试结果 => " << (isPass ? "OK" : "Failed") << std::endl;
            }
        }

        if(config.IsPrintResult)
        {
            std::cout << "[" << SortAlgoType::Get().Name() << "] 测试结果： " << "(共" << config.TestTimes << "轮)" 
                << (TestResults.IsAllPass() ? "全部通过" : "未通过") << std::endl;
        }

        if(config.IsPrintTime)
        {
            TestResults.StatisticTime();
            std::cout << "[" << SortAlgoType::Get().Name() << "] 平均耗时: " << TestResults.AverageTime << " ms\n";
            std::cout << "[" << SortAlgoType::Get().Name() << "] 总耗时: " << TestResults.SumTime << " ms\n";
        } 
        
        std::cout << std::endl;
    }


    //单次随机数测试
    OneTestResult VerifyAlgoOneTime(SortAlgo& ToBeVerifiedSortAlgo, const TestConfigParam& configParam)
    {
        std::vector<int> BeSortDatas = GenerateTestData(configParam.Numbers, configParam.MinNum, configParam.MaxNum);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(BeSortDatas, "排序前: \n");

        std::vector<int> StandardSortResult;
        StandardSort::Get().Sort(BeSortDatas, StandardSortResult);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(StandardSortResult, StandardSort::Get().Name() + "排序后: \n");

        std::vector<int> ToBeVerifiedSortAlgoResult;

        TimeStatistics timeStatic;
        ToBeVerifiedSortAlgo.Sort(BeSortDatas, ToBeVerifiedSortAlgoResult);
        timeStatic.Stop();

        if(configParam.IsPrintTemp) Tool::Get().PrintData(ToBeVerifiedSortAlgoResult, ToBeVerifiedSortAlgo.Name() + "排序后: \n");

        return { StandardSortResult == ToBeVerifiedSortAlgoResult, timeStatic.GetTime_ms() };
    }

    //多次随机数测试
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