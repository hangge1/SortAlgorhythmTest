

#include <iostream>
#include "SortAlgoCompareInstrument.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"
#include "QuickSort.h"


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
    TestConfigParams.TestTimes = 20;
    TestConfigParams.Numbers = 10000;
    TestConfigParams.MinNum = 1;
    TestConfigParams.MaxNum = 20;
    TestConfigParams.IsPrintTime = true;
    TestConfigParams.InIsPrintTemp = false;

    //�������ٶȣ��������ԣ�һ����˵   ѡ�� > ���� > ð��
    //SelectionSort > InsertionSort > BubbleSort
    //SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<SelectionSort>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Easy>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_Opt_SelectPivot>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<QuickSort_UnRecursive>(TestConfigParams);

    

    return 0;
}