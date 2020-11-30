#ifndef SORT_H
#define SORT_H

#include "Object.h"
#include "Array.h"

namespace JSLib
{

class Sort : public Object
{
private:
    Sort();
    Sort(const Sort&);
    Sort& operator =(const Sort&);

    template <typename T>
    static void Swap(T& a,T& b)
    {
        T c(a);
        a = b;
        b = c;
    }

    //归并排序递归函数
    template < typename T>
    static void Merge(T array[],T helper[],int begin,int end,bool min2max)
    {
        int mid = (begin + end) / 2;          //将原来的数组平分
        if( begin < end)
        {
            Merge(array,helper,begin,mid,min2max);
            Merge(array,helper,mid+1,end,min2max);
            Merge(array,helper,begin,mid,end,min2max);
        }
    }

    /**
     **归并排序最后一步，将最终的两个有序序列归并排序到辅助空间当中
     **然后再将辅助空间的元素全部写回原来的空间
     **默认从小到大排序，min2max为真时从小到大排序
     **/
    template < typename T>
    static void Merge(T src[],T helper[],int begin,int mid,int end,bool min2max)
    {
        int i = begin;
        int j = mid+1;
        int k = begin;

        while((i<=mid) && (j<=end))
        {
            if(min2max ? (src[i] < src[j]) : (src[i] > src[j]))
            {
                helper[k++] = src[i++];
            }

            if(min2max ? (src[i] >= src[j]) :(src[i] <= src[j]) )
            {
                helper[k++] = src[j++];
            }
        }

        while(i<=mid)
        {
            helper[k++] = src[i++];
        }

        while(j<=end)
        {
            helper[k++] = src[j++];
        }

        for(i=begin;i<=end;i++)
        {
            src[i] = helper[i];
        }
    }

    //快速排序
    template < typename T>
    static void Quick(T array[],int begin,int end,bool min2max)
    {
        if(begin < end)
        {
            int pivot = Partition(array,begin,end,min2max);       //快速排序的基准点
            Quick(array,begin,pivot-1,min2max);
            Quick(array,pivot+1,end,min2max);
        }
    }

    //得到快速排序中的基准点元素下标
    template < typename T>
    static int Partition(T array[],int begin,int end,bool min2max)
    {
        T tem = array[begin];

        while(begin < end)
        {
            while((begin < end) && (min2max ? (array[end] > tem) : (array[end] < tem)))
            {
                end--;
            }

            Swap(array[end],array[begin]);

            while((begin < end) && (min2max ? (array[begin] <= tem) : (array[begin] >= tem)))
            {
                begin++;
            }

             Swap(array[end],array[begin]);
        }

        //array[begin] = tem;
        return begin;
    }

public:
    template < typename T>
    static void Select(T array[],int len,bool min2max = true)       //选择排序方法，默认从小到大排序
    {                                                               //min2max为真时从小到大排序
        for(int i=0;i<len;i++)
        {
            int min = i;

            for(int j=i+1;j<len;j++)
            {
                if(min2max ? array[j]<array[min] : array[j]>array[min])
                {
                    min = j;
                }

            }

            if(min != i)
            {
                Swap(array[i],array[min]);
            }

        }
    }

    template < typename T>
    static void Insert(T array[],int len,bool min2max = true)   //插入排序方法，默认从小到大排序
    {                                                           //min2max为真时从小到大排序
        for(int i=1;i<len;i++)
        {
            int k = i;
            T e = array[k];

            for(int j=i-1;((j>=0) && (min2max ? array[j] > e : array[j] < e));j--)
            {
                k = j;
                array[j + 1] = array[j];
            }

            if(k != i)
            {
                array[k] =  e;
            }
        }


    }

    /**
     **冒泡排序。exchange为真表示待排序序列中已排序后的序列的后面任为一个无序序列
     **还需继续进行冒泡排序
     **/
    template < typename T>
    static void Bubble(T array[],int len,bool min2max = true)
    {
        bool exchange = true;

        for(int i=0;(i<len) && exchange;i++)
        {
            exchange = false;

            for(int j=len-1;j>i;j--)
            {
                if(min2max ? array[j] < array[j - 1] : array[j] > array[j - 1])
                {
                    Swap(array[j],array[j-1]);
                    exchange = true;
                }
            }
        }
    }

    //希尔排序
    template < typename T>
    static void Shell(T array[],int len,bool min2max = true)
    {
        int d = len;
        do
        {
            d = d / 3 + 1;           //将序列分组

            for(int i=d;i<len;i+=d)      //分组完成后进行插入排序
            {
                int k = i;
                T e = array[k];

                for(int j=i-d;(j>=0) && (min2max ? array[j] > e : array[j] < e);j-=d)
                {

                    k = j;
                    array[j + d] = array[j];
                }

                if(k != i)
                {
                    array[k] = e;
                }
            }


        }while(d > 1);
    }

    //归并排序
    template < typename T>
    static void Merge(T array[],int len,bool min2max = true)
    {
        T* helper = new T[len];    //申请一个辅助空间

        if(helper != NULL)
        {
            Merge(array,helper,0,len-1,min2max);
        }

    }

    //快速排序
    template < typename T>
    static void Quick(T array[],int len,bool min2max = true)
    {
        Quick(array,0,len-1,min2max);
    }

    /**
     **以下函数族是为了将Sort类适用于库中的Array类
     **/
    template < typename T>
    static void Select(Array<T>&array,bool min2max = true)
    {
        Select(array.array(),array.length(),min2max);
    }

    template < typename T>
    static void Insert(Array<T>&array,bool min2max = true)
    {
        Insert(array.array(),array.length(),min2max);
    }

    template < typename T>
    static void Bubble(Array<T>&array,bool min2max = true)
    {
        Bubble(array.array(),array.length(),min2max);
    }

    template < typename T>
    static void Shell(Array<T>&array,bool min2max = true)
    {
        Shell(array.array(),array.length(),min2max);
    }

    template < typename T>
    static void Merge(Array<T>&array,bool min2max = true)
    {
        Merge(array.array(),array.length(),min2max);
    }

    template < typename T>
    static void Quick(Array<T>&array,bool min2max = true)
    {
        Quick(array.array(),array.length(),min2max);
    }


};

}


#endif // SORT_H
