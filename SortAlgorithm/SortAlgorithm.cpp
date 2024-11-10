

#include <iostream>
#include "SortAlgoCompareInstrument.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "QuickSort.h"


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
    TestConfigParams.Numbers = 200;
    TestConfigParams.MinNum = 1;
    TestConfigParams.MaxNum = 2000;
    TestConfigParams.IsPrintTime = true;
    TestConfigParams.InIsPrintTemp = true;

    //单纯看速度，经过测试，一般来说   选择 > 插入 > 冒泡
    //SelectionSort > InsertionSort > BubbleSort
    SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<SelectionSort>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Easy>(TestConfigParams);

    

    return 0;
}