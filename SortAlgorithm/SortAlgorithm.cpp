

#include <iostream>
#include "SortAlgoCompareInstrument.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "CountingSort.h"
#include "HeapSort.h"
#include "RadixSort.h"


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
    TestConfigParams.MaxNum = 999;
    TestConfigParams.IsPrintTime = true;
    TestConfigParams.IsPrintTemp = false;
    TestConfigParams.IsPrintResult = true;


    //插入、冒泡、选择【单纯看速度，经测试，选择 快于 插入 快于 冒泡】
    //SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<SelectionSort>(TestConfigParams);
    
    //快排【4个版本，3个递归+1个迭代】、归并【2个版本，1个递归+1个迭代】
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_RandomPivot>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Medium3Pivot>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_UnRecursive>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<MergeSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<MergeSort_NoRecursion>(TestConfigParams);

    // 堆排序【常规版本 和 优化版】
    //SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Normal>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Opt_CreateHeap>(TestConfigParams);
    
    // 计数排序
    //SortAlgoCompareInstrument::Get().Execute_Test<CountingSort>(TestConfigParams);
    // 基数排序
    SortAlgoCompareInstrument::Get().Execute_Test<RadixSort>(TestConfigParams);
  
    // 希尔排序【用的很少】
    

    return 0;
}