

#include <iostream>
#include "SortAlgoCompareInstrument.h"
#include "InsertionSort.h"
#include "BubbleSort_Easy.h"


int main()
{
    //排序算法类
    //测试次数
    //数组的数字个数
    //最小数字
    //最大数字
    SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(10, 10000, 1, 1000, true, false);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(10, 10000, 1, 1000, true, false);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(10, 10000, 1, 1000, true, false);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(10, 10000, 1, 1000, true, false);

    return 0;
}