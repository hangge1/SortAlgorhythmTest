

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

int main()
{
    //�������ò���
    TestConfigParam TestConfigParams;
    TestConfigParams.TestTimes = 2; //���Դ���
    TestConfigParams.Numbers = 20; //�������ݸ���
    TestConfigParams.MinNum = 1; //��С����
    TestConfigParams.MaxNum = 999; //�������
    TestConfigParams.IsPrintTime = true; //�Ƿ�����ʱ��ӡ
    TestConfigParams.IsPrintTemp = false; //�Ƿ����м���̴�ӡ
    TestConfigParams.IsPrintResult = true; //�Ƿ��������ӡ


    //���롢ð�ݡ�ѡ��
    SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<SelectionSort>(TestConfigParams);
    
    //���š��鲢
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Easy>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_RandomPivot>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Medium3Pivot>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_UnRecursive>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<MergeSort>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<MergeSort_NoRecursion>(TestConfigParams);

    // ������
    SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Normal>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Opt_CreateHeap>(TestConfigParams);
    
    // ��������
    SortAlgoCompareInstrument::Get().Execute_Test<CountingSort>(TestConfigParams);
    // ��������
    SortAlgoCompareInstrument::Get().Execute_Test<RadixSort>(TestConfigParams);
  
    // ϣ�������õĺ��١�
    

    return 0;
}