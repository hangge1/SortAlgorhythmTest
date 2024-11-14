

#include <iostream>

#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "CountingSort.h"
#include "HeapSort.h"
#include "RadixSort.h"

#include "SortAlgoCompareInstrument.h"
#include <thread>

void PresetTest(const TestConfigParam& TestConfigParams)
{
    //插入、冒泡、选择
    SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<SelectionSort>(TestConfigParams);
    
    //快排、归并
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Easy>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_RandomPivot>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Medium3Pivot>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_UnRecursive>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<MergeSort>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<MergeSort_NoRecursion>(TestConfigParams);

    // 堆排序
    SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Normal>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Opt_CreateHeap>(TestConfigParams);
    
    // 计数排序
    SortAlgoCompareInstrument::Get().Execute_Test<CountingSort>(TestConfigParams);
    // 基数排序
    SortAlgoCompareInstrument::Get().Execute_Test<RadixSort>(TestConfigParams);
  
    // 希尔排序【用的很少】
}


int main()
{
    //测试配置参数
    TestConfigParam TestConfigParams;
    TestConfigParams.TestTimes = 2; //测试次数
    TestConfigParams.Numbers = 20; //样本数据个数
    TestConfigParams.MinNum = 1; //最小数字
    TestConfigParams.MaxNum = 999; //最大数字
    TestConfigParams.IsPrintTime = true; //是否开启耗时打印
    TestConfigParams.IsPrintTemp = false; //是否开启中间过程打印
    TestConfigParams.IsPrintResult = true; //是否开启结果打印

    //你可以打开下面注释, 来观察打印效果
    //PresetTest(TestConfigParams);
    
    //TODO: 你可以添加自己的排序算法,如下编写
    //SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    

    return 0;
}