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
    TestConfigParams.MaxNum = 16;
    TestConfigParams.IsPrintTime = true;
    TestConfigParams.IsPrintTemp = false;
    TestConfigParams.IsPrintResult = true;

    //�������ٶȣ��������ԣ�һ����˵   ѡ�� > ���� > ð��
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


    //TODO: ���š���������Ͱ���򡢻�������ϣ������

    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    //_CrtDumpMemoryLeaks();
    return 0;
}