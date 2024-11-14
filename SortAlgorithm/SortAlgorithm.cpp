

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
    //�����㷨��
    //���Դ���
    //��������ָ���
    //��С����
    //�������
    //�Ƿ�����ʱ��ӡ
    //�Ƿ����м���̴�ӡ

    SortAlgoCompareInstrumentConfig TestConfigParams;
    TestConfigParams.TestTimes = 10;
    TestConfigParams.Numbers = 10000;
    TestConfigParams.MinNum = 1;
    TestConfigParams.MaxNum = 999;
    TestConfigParams.IsPrintTime = true;
    TestConfigParams.IsPrintTemp = false;
    TestConfigParams.IsPrintResult = true;


    //���롢ð�ݡ�ѡ�񡾵������ٶȣ������ԣ�ѡ�� ���� ���� ���� ð�ݡ�
    //SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<SelectionSort>(TestConfigParams);
    
    //���š�4���汾��3���ݹ�+1�����������鲢��2���汾��1���ݹ�+1��������
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_RandomPivot>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Medium3Pivot>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_UnRecursive>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<MergeSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<MergeSort_NoRecursion>(TestConfigParams);

    // �����򡾳���汾 �� �Ż��桿
    //SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Normal>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Opt_CreateHeap>(TestConfigParams);
    
    // ��������
    //SortAlgoCompareInstrument::Get().Execute_Test<CountingSort>(TestConfigParams);
    // ��������
    SortAlgoCompareInstrument::Get().Execute_Test<RadixSort>(TestConfigParams);
  
    // ϣ�������õĺ��١�
    

    return 0;
}