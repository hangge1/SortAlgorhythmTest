#pragma once

#include <iostream>
#include <chrono>

#include "SortAlgo.h"
#include "StandardSort.h"
#include "TimeStatistics.h"

//测试配置参数
struct TestConfigParam
{
    //测试次数
    int TestTimes = 1;

    //样本数据个数
    int Numbers = 5;

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

//单次测试结果
struct OneTestResult
{
    bool IsPass = false; //是否通过
    float SpeedTime = 0.0f; //花费时间(ms)
};

//一次执行的所有测试结果归总
struct TestAllResults
{
    std::vector<OneTestResult> Results;

    //以下俩变量在StatisticTime() 调用后被赋值
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

    //结果打印相关
    void PrintEveryTestResult() const
    {
        for (int i = 0; i < Results.size(); i++)
        {
            printf("  第[%d]测试结果 => %s\n",i, Results[i].IsPass ? "Pass" : "Failed");
        }
    }

    void PrintAllPassInfo(int TestTimes) const
    {
        printf("  共%d轮测试: %s\n\n", TestTimes, IsAllPass() ? "全部通过" : "未通过");
        printf("  通过率: %.2f%%\n", GetPassRate());
    }

    void PrintSpeedTimeInfo() 
    {
        StatisticTime();
        std::cout <<  "  平均耗时: " << AverageTime << " ms\n";
        std::cout <<  "  总耗时: " << SumTime << " ms\n";
    }
};

//排序算法比较机构
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
    void Execute_Test(const TestConfigParam& config = DefaultTestConfig) const
    {
        printf("========================== Begin %s TEST ========================== \n\n",SortAlgoType::Get().Name().c_str());

        TestAllResults TestResults = SortAlgoCompareInstrument::Get().VerifySortManyTime<SortAlgoType>(config);

        printf("[%s] 测试结果汇总: \n\n", SortAlgoType::Get().Name().c_str());
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

    //单次随机数排序算法验证
    template<typename SortAlgoType>
    OneTestResult VerifySortOneTime(const TestConfigParam& configParam) const
    {
        std::vector<int> BeSortDatas = Tool::Get().GenerateTestData(configParam.Numbers, configParam.MinNum, configParam.MaxNum);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(BeSortDatas, "\n原始数据: \n");

        std::vector<int> StandardSortResult;
        StandardSort::Get().Sort(BeSortDatas, StandardSortResult);
        if(configParam.IsPrintTemp) Tool::Get().PrintData(StandardSortResult, "\n正确结果: \n");

        std::vector<int> ToBeVerifiedSortAlgoResult;

        TimeStatistics timeStatic;
        SortAlgoType::Get().Sort(BeSortDatas, ToBeVerifiedSortAlgoResult);
        timeStatic.Stop();

        if(configParam.IsPrintTemp) Tool::Get().PrintData(ToBeVerifiedSortAlgoResult,"\n" + SortAlgoType::Get().Name() + "应用结果: \n");

        return { StandardSortResult == ToBeVerifiedSortAlgoResult, timeStatic.GetTime_ms() };
    }

    //多次随机数排序算法验证
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