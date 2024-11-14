#pragma once

#include "SortAlgo.h"
#include <assert.h>

/*
    ������
    1�����ȶ�
    2��ʱ�临�Ӷ� O(N*LogN)
    3���ռ临�Ӷ� O(1)
    4���������ڡ��ռ�ռ��O(1)���������ȶ��ԣ���ѡ����
    5�������������д������Ҫ�Ĳ������ڽ��ѵĹ���
     (1) ��һ��HeapSort_Normal ���Զ����£�����heapInsert ��ʱ�临�Ӷ�O(NLogN)
     (2) �ڶ���HeapSort_Opt_CreateHeap ���Ե����ϣ�����heapify��ʱ�临�Ӷ�O(N)
    
    ע���ѵ��������Ĳ����� heapInsert �� heapify
      (1) heapInsert�������������Ͽ�������Ǵ���ѣ��ȸ��ڵ�󣬾Ͳ��Ϻ͸��ڵ㽻���͵ݽ�
      (2) heapify�������������¿�������Ǵ���ѣ��Ⱥ��ӽڵ�С���Ͳ��Ϻͺ��ӽڵ㽻���͵ݽ�
*/

class HeapSort_Normal : public SortAlgo
{
public:
    static HeapSort_Normal& Get()
    {
        static HeapSort_Normal sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "HeapSort_Normal";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty()) return;

        //1 ����
        for (int i = 1; i < SortResults.size(); i++)
        {
            HeapInsert(SortResults, i);
        }     
        
        //2 ��������β�ڵ㣬Heapify Root
        int HeapSize = (int)SortResults.size();
        while(HeapSize > 1)
        {
            std::swap(SortResults[0], SortResults[HeapSize - 1]);
            HeapSize--;
            Heapify(SortResults, 0, HeapSize);
        }

    }

    //�������Ͽ�������Լ��ȸ��״�ͽ�����
    void HeapInsert(std::vector<int>& Heap, int i)
    {
        if(i < 0 || i >= Heap.size())
        {
            assert(false);
        }

        //Root��parentsΪ0��Ҳ����˵��Root�ڵ����Heap[i] == Heap[parents]������ѭ��
        int current = i;
        int parent = (current - 1) / 2;
        while(Heap[current] > Heap[parent])
        {
            std::swap(Heap[current], Heap[parent]);            
            current = parent;
            parent = (current - 1) / 2;
        }
    }

    //ע�����size����ʾһ����ʾ�Ķ��ڶѵĿ��ƣ�
    void Heapify(std::vector<int>& Heap, int i, int size)
    {
        int current = i;
        while(current < size)
        {
            int left = 2 * current + 1;
            //���û�����ӣ�ֱ���˳�
            if(left >= size)
            {
                break;
            }

            int best = Heap[left] > Heap[current] ? left : current;

            //���û���Һ��� && �Լ������Ӵ�
            if(left + 1 >= size && best == current)
            {
                break;
            }

            //���Һ��ӣ�Ҳ�����ӣ��Ƚ�˭���
            if(left + 1 < size && Heap[left + 1] > Heap[best])
            {
                best = left + 1;
            }

            //�Լ����
            if(best == current)
            {
                break;
            }

            //���Ӵ�
            if(best == left)
            {
                std::swap(Heap[left], Heap[current]);
                current = left;
            }
            else //�Һ��Ӵ�
            {
                std::swap(Heap[left + 1], Heap[current]);
                current = left + 1;
            }
        }
    }
};

class HeapSort_Opt_CreateHeap : public SortAlgo
{
public:
    static HeapSort_Opt_CreateHeap& Get()
    {
        static HeapSort_Opt_CreateHeap sort;
        return sort;
    }

    virtual std::string Name() const override
    {
        return "HeapSort_Opt_CreateHeap";
    }

    //��������
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty()) return;

        //1 ���ѡ��Ż��汾���˴��ӵ�һ����Ҷ�ӽڵ㿪ʼ�Ӻ���ǰ�����ϵ�Heapify��
        //��һ����Ҷ�ӽڵ���±���  len / 2 - 1
        int size = (int)SortResults.size();
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            Heapify(SortResults, i, size);
        }
        
        //2 ��������β�ڵ㣬Heapify Root
        int HeapSize = size;
        while(HeapSize > 1)
        {
            std::swap(SortResults[0], SortResults[HeapSize - 1]);
            HeapSize--;
            Heapify(SortResults, 0, HeapSize);
        }

    }

    //�������Ͽ�������Լ��ȸ��״�ͽ�����
    void HeapInsert(std::vector<int>& Heap, int i)
    {
        if(i < 0 || i >= Heap.size())
        {
            assert(false);
        }

        //Root��parentsΪ0��Ҳ����˵��Root�ڵ����Heap[i] == Heap[parents]������ѭ��
        int current = i;
        int parent = (current - 1) / 2;
        while(Heap[current] > Heap[parent])
        {
            std::swap(Heap[current], Heap[parent]);            
            current = parent;
            parent = (current - 1) / 2;
        }
    }

    //ע�����size����ʾһ����ʾ�Ķ��ڶѵĿ��ƣ�
    void Heapify(std::vector<int>& Heap, int i, int size)
    {
        int current = i;
        while(current < size)
        {
            int left = 2 * current + 1;
            //���û�����ӣ�ֱ���˳�
            if(left >= size)
            {
                break;
            }

            int best = Heap[left] > Heap[current] ? left : current;

            //���û���Һ��� && �Լ������Ӵ�
            if(left + 1 >= size && best == current)
            {
                break;
            }

            //���Һ��ӣ�Ҳ�����ӣ��Ƚ�˭���
            if(left + 1 < size && Heap[left + 1] > Heap[best])
            {
                best = left + 1;
            }

            //�Լ����
            if(best == current)
            {
                break;
            }

            //���Ӵ�
            if(best == left)
            {
                std::swap(Heap[left], Heap[current]);
                current = left;
            }
            else //�Һ��Ӵ�
            {
                std::swap(Heap[left + 1], Heap[current]);
                current = left + 1;
            }
        }
    }
};