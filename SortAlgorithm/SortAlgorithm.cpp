

#include <iostream>
#include "SortAlgoCompareInstrument.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "CountingSort.h"
#include "HeapSort.h"


int main()
{
    //排序算法类
    //测试次数
    //数组的数字个数
    //最小数字
    //最大数字
    //是否开启耗时打印
    //是否开启中间过程打印

    SortAlgoCompareInstrumentConfig TestConfigParams;
    TestConfigParams.TestTimes = 10;
    TestConfigParams.Numbers = 10000;
    TestConfigParams.MinNum = 1;
    TestConfigParams.MaxNum = 20;
    TestConfigParams.IsPrintTime = true;
    TestConfigParams.IsPrintTemp = false;
    TestConfigParams.IsPrintResult = true;

    //单纯看速度，经过测试，一般来说   选择 > 插入 > 冒泡
    //SelectionSort > InsertionSort > BubbleSort
    //SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<SelectionSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Opt_SelectPivot>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_UnRecursive>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<MergeSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<MergeSort_NoRecursion>(TestConfigParams);

    // 计数排序【稳定写法】
    //SortAlgoCompareInstrument::Get().Execute_Test<CountingSort>(TestConfigParams);

    // 堆排序
    SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Normal>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Opt_CreateHeap>(TestConfigParams);
    

    // 基数排序
  
    // 桶排序
  
    // 希尔排序
    

    return 0;
}