

#include <iostream>
#include "SortAlgoCompareInstrument.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
#include "SelectionSort.h"


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
    TestConfigParams.TestTimes = 1;
    TestConfigParams.Numbers = 100000;
    TestConfigParams.MinNum = 1;
    TestConfigParams.MaxNum = 10000;
    TestConfigParams.IsPrintTime = true;
    TestConfigParams.InIsPrintTemp = false;

    //�������ٶȣ��������ԣ�һ����˵   ѡ�� > ���� > ð��
    //SelectionSort > InsertionSort > BubbleSort
    SortAlgoCompareInstrument::Get().Execute_Test<InsertionSort>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Easy>(TestConfigParams);
    //SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_Flag_Opt>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<BubbleSort_ForTime_Opt>(TestConfigParams);
    SortAlgoCompareInstrument::Get().Execute_Test<SelectionSort>(TestConfigParams);

    

    return 0;
}