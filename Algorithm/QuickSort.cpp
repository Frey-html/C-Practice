//quicksort 此处为同时对两个数组排序，一为主，一为从
//未选取更优pivot
//未进行小N时速度优化
#include <iostream>
using namespace std;

template <typename T>
void Swap(T *a, T *b){
    T temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

template <typename T>
void PrintArray(T *array, int size){
    for(int i = 0;i < size;i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
}

template <typename T1, typename T2>
void QuickSort(T1 *distance, T2 *price, int left, int right){
    if(right - left <= 0) return;
    int pivot, i, j;
    pivot = (left + right) / 2;
    Swap(distance + pivot, distance + right);
    Swap(price + pivot, price + right);
    i = left - 1;
    j = right;
    pivot = distance[right];
    while(1){
        while(distance[++i] < pivot){}
        while(distance[--j] > pivot){}
        if(i < j){
            Swap(distance + i, distance + j);
            Swap(price + i, price + j);
        }
        else break;
    }
    Swap(distance + i, distance + right);
    Swap(price + i, price + right);
    QuickSort(distance, price, left, i - 1);
    QuickSort(distance, price, i+1, right);
}