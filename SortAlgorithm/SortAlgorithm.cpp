//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//
//#ifdef _DEBUG
//    #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//    // Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//    // allocations to be of _CLIENT_BLOCK type
//#else
//    #define DBG_NEW new
//#endif

#include <iostream>
#include "SortAlgoCompareInstrument.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"


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
    TestConfigParams.MaxNum = 16;
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
    SortAlgoCompareInstrument::Get().Execute_Test<MergeSort>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<MergeSortNoRecursion>(TestConfigParams);


    //TODO: 堆排、计数排序、桶排序、基数排序、希尔排序

    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    //_CrtDumpMemoryLeaks();
    return 0;
}