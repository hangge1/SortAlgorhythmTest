

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
    //�����㷨��
    //���Դ���
    //��������ָ���
    //��С����
    //�������
    //�Ƿ�����ʱ��ӡ
    //�Ƿ����м���̴�ӡ

    SortAlgoCompareInstrumentConfig TestConfigParams;
    TestConfigParams.TestTimes = 50;
    TestConfigParams.Numbers = 10000;
    TestConfigParams.MinNum = 1;
    TestConfigParams.MaxNum = 20;
    TestConfigParams.IsPrintTime = true;
    TestConfigParams.IsPrintTemp = false;
    TestConfigParams.IsPrintResult = true;

    //�������ٶȣ������ԣ�ѡ�� > ���� > ð��
    //���롢ð�ݡ�ѡ��
    //SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<SelectionSort>(TestConfigParams);
    
    //���š��鲢
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_RandomPivot>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Medium3Pivot>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_UnRecursive>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<MergeSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<MergeSort_NoRecursion>(TestConfigParams);

    // ���������ȶ�д����
    //SortAlgoCompareInstrument::Get().Execute_Test<CountingSort>(TestConfigParams);

    // �����򡾳���汾 �� �Ż��桿
    //SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Normal>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<HeapSort_Opt_CreateHeap>(TestConfigParams);
    
    // �������� ��RadixSort��
  
    // Ͱ����һ���������ͼ����������Ƕ���ΪͰ������������Σ��Ͳ�д���������ˡ�
  
    // ϣ�������õĺ��١�
    

    return 0;
}