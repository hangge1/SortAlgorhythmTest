

#include <iostream>
#include "SortAlgoCompareInstrument.h"
#include "InsertionSort.h"
#include "BubbleSort_Easy.h"


int main()
{
    //�����㷨��
    //���Դ���
    //��������ָ���
    //��С����
    //�������
    SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(10, 10000, 1, 1000, true, false);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(10, 10000, 1, 1000, true, false);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(10, 10000, 1, 1000, true, false);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(10, 10000, 1, 1000, true, false);

    return 0;
}