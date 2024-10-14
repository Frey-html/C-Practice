//7-1 To Fill or Not to Fill 
//关键是贪心策略的选择，并非每到一站都需要加油，到了可行距离内最便宜的一站可以直接把油加满
//需注意到各种变量对于策略的影响
#include <iostream>
#include <iomanip>
using namespace std;
#define MaxStation 550
#define MaxPrice 10000

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

int main(){
    int capacity;
    int D;
    int Davg;
    int N;
    double price[MaxStation];
    int distance[MaxStation];
    
    scanf("%d %d %d %d", &capacity, &D, &Davg, &N);
    for(int i = 0;i < N;i++){
        scanf("%lf %d", &price[i], &distance[i]);
    }

    double maxdistance = 0, totalprice = 0;

    //sort the station with their distance, sort the price of the station correspondingly
    QuickSort(distance, price, 0, N - 1);
    
    //set the destination
    distance[N] = D;
    price[N] = 0;

    int dist = capacity * Davg; //the farest distance currently avalible
    int now = 0; // current position of station
    int farest_station = 0; //index farest station currently avalible
    int cheapest = 0; //index of cheapest station currently avalible
    int next = 0; //next station 
    int done = 0;
    //可能需要double
    double remain = 0; //remaining gas
    double lowest;
    int lowest_sta;

    //PrintArray(distance, N+1);
    //PrintArray(price, N+1);
    while(1){
        //reach a new station
        if(distance[0] != 0){
            break;
        }
        maxdistance = distance[now];
        if(now == N){
            done = 1;
            break;
        }
        if(distance[now+1] - distance[now] > dist){
            maxdistance += dist;
            break;
        }

        farest_station = now;
        for(int i = 0;i <= N;i++){
            if(distance[i] - distance[now] <= dist){
                farest_station = i;
            }
        }

        next = now;
        lowest_sta = now;
        lowest = MaxPrice;
        for(int i = now;i <= farest_station;i++){
            if(price[i] < price[now]){
                next = i;
                break;
            }
            if(price[i] < lowest && i != now){
                lowest = price[i];
                lowest_sta = i;
            }
        }

        //exist a station whose gas price lower than current avaliable
        if(next != now){
            //need to refill to get to next station 
            if(remain * Davg < distance[next] - distance[now]){
                totalprice += price[now] * (distance[next] - distance[now] - remain * Davg)/Davg;
                remain = 0;
            }else{
                remain -= (double)(distance[next] - distance[now])/Davg;
            }
            now = next;
        }else{
            totalprice += (capacity - remain) * price[now];
            remain = capacity;
            remain -= (double)(distance[lowest_sta] - distance[now])/Davg;
            now = lowest_sta;
        }  
        
    }   

    if(done == 0){
        cout<<"The maximum travel distance = "<<setiosflags(ios::fixed)<<setprecision(2)<<maxdistance;
    }
    else{
        cout<<setiosflags(ios::fixed)<<setprecision(2)<<totalprice;
    }
}

