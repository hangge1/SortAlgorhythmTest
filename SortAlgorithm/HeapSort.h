#pragma once

#include "SortAlgo.h"
#include <assert.h>

/*
    堆排序
    1、不稳定
    2、时间复杂度 O(N*LogN)
    3、空间复杂度 O(1)
    4、性能由于、空间占用O(1)、不考虑稳定性，首选堆排
    5、这里给出两种写法，主要的差异在于建堆的过程
     (1) 第一种HeapSort_Normal 是自顶向下，不断heapInsert ，时间复杂度O(NLogN)
     (2) 第二种HeapSort_Opt_CreateHeap 是自底向上，不断heapify，时间复杂度O(N)
    
    注：堆的两个核心操作： heapInsert 和 heapify
      (1) heapInsert操作，不断往上看，如果是大根堆，比父节点大，就不断和父节点交换和递进
      (2) heapify操作，不断往下看，如果是大根堆，比孩子节点小，就不断和孩子节点交换和递进
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

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty()) return;

        //1 建堆
        for (int i = 1; i < SortResults.size(); i++)
        {
            HeapInsert(SortResults, i);
        }     
        
        //2 交换根和尾节点，Heapify Root
        int HeapSize = (int)SortResults.size();
        while(HeapSize > 1)
        {
            std::swap(SortResults[0], SortResults[HeapSize - 1]);
            HeapSize--;
            Heapify(SortResults, 0, HeapSize);
        }

    }

    //不断往上看，如果自己比父亲大就交换！
    void HeapInsert(std::vector<int>& Heap, int i)
    {
        if(i < 0 || i >= Heap.size())
        {
            assert(false);
        }

        //Root的parents为0，也就是说在Root节点进行Heap[i] == Heap[parents]会跳出循环
        int current = i;
        int parent = (current - 1) / 2;
        while(Heap[current] > Heap[parent])
        {
            std::swap(Heap[current], Heap[parent]);            
            current = parent;
            parent = (current - 1) / 2;
        }
    }

    //注意这个size，表示一种显示的对于堆的控制！
    void Heapify(std::vector<int>& Heap, int i, int size)
    {
        int current = i;
        while(current < size)
        {
            int left = 2 * current + 1;
            //如果没有左孩子，直接退出
            if(left >= size)
            {
                break;
            }

            int best = Heap[left] > Heap[current] ? left : current;

            //如果没有右孩子 && 自己比左孩子大
            if(left + 1 >= size && best == current)
            {
                break;
            }

            //有右孩子，也有左孩子，比较谁最大
            if(left + 1 < size && Heap[left + 1] > Heap[best])
            {
                best = left + 1;
            }

            //自己最大
            if(best == current)
            {
                break;
            }

            //左孩子大
            if(best == left)
            {
                std::swap(Heap[left], Heap[current]);
                current = left;
            }
            else //右孩子大
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

    //假设升序
    virtual void Sort(const std::vector<int>& InputDatas, std::vector<int>& SortResults) override
    {
        SortResults = InputDatas;
        if(SortResults.empty()) return;

        //1 建堆【优化版本，此处从第一个非叶子节点开始从后往前，不断的Heapify】
        //第一个非叶子节点的下标是  len / 2 - 1
        int size = (int)SortResults.size();
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            Heapify(SortResults, i, size);
        }
        
        //2 交换根和尾节点，Heapify Root
        int HeapSize = size;
        while(HeapSize > 1)
        {
            std::swap(SortResults[0], SortResults[HeapSize - 1]);
            HeapSize--;
            Heapify(SortResults, 0, HeapSize);
        }

    }

    //不断往上看，如果自己比父亲大就交换！
    void HeapInsert(std::vector<int>& Heap, int i)
    {
        if(i < 0 || i >= Heap.size())
        {
            assert(false);
        }

        //Root的parents为0，也就是说在Root节点进行Heap[i] == Heap[parents]会跳出循环
        int current = i;
        int parent = (current - 1) / 2;
        while(Heap[current] > Heap[parent])
        {
            std::swap(Heap[current], Heap[parent]);            
            current = parent;
            parent = (current - 1) / 2;
        }
    }

    //注意这个size，表示一种显示的对于堆的控制！
    void Heapify(std::vector<int>& Heap, int i, int size)
    {
        int current = i;
        while(current < size)
        {
            int left = 2 * current + 1;
            //如果没有左孩子，直接退出
            if(left >= size)
            {
                break;
            }

            int best = Heap[left] > Heap[current] ? left : current;

            //如果没有右孩子 && 自己比左孩子大
            if(left + 1 >= size && best == current)
            {
                break;
            }

            //有右孩子，也有左孩子，比较谁最大
            if(left + 1 < size && Heap[left + 1] > Heap[best])
            {
                best = left + 1;
            }

            //自己最大
            if(best == current)
            {
                break;
            }

            //左孩子大
            if(best == left)
            {
                std::swap(Heap[left], Heap[current]);
                current = left;
            }
            else //右孩子大
            {
                std::swap(Heap[left + 1], Heap[current]);
                current = left + 1;
            }
        }
    }
};