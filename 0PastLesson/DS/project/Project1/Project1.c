/********************
Performance Measurement 

Fuctson:Judging the time costed in different Algorithm on computing X^N

Input:
	(1)a positive integer K -- the repeat times of calling a function to ensure the running time 
    exceed a tick
    (2)a positive integer N -- the exponent of X

Output:
    The Ticks, total time(sec) and duration(sec) of computing X^N with repeat times K 
    of three computing function
********************/

#include <stdio.h>
#include <time.h>
/********************
 *(1) Define Variable
*********************/         
const double X = 1.0001;        
clock_t start, stop;   
/********************
 * k must to be big enough to ensure tick of algorithm2 > 0 and not to big
 * to limit the running time of the program the largest N situation       
*********************/ 

/********************
 *(2) Function declaration
*********************/
double fun1(int Exponent);
//use N-1 multiplication

double fun2(int Exponent);
//iterative version of algorithm 2

double fun3(int Exponent, double X);
//recursive version of algorithm 2

int main(){
    double ans1 = 0, ans2 = 0, ans3 = 0;                   //store the answer of three function, judging if the answer is right
    double tick1 = 0, tick2 = 0, tick3 = 0;                //ticks of running fun1, fun2, fun3 k times
    double totaltime1 = 0, totaltime2 = 0, totaltime3 = 0; //total compute time of running fun1, fun2, fun3 separately k times
    double duration1 = 0, duration2 = 0, duration3 = 0;    //duration of running fun1, fun2, fun3 single time
    int N = 0, K = 0;                         //repeat times and exponent of X, iteration times of function
    
    printf("Please input N(exponent of X):");
    scanf("%d", &N);
    printf("Please input K(iteration times of function)):");
    scanf("%d", &K);                            //read in N, K

    start = clock();                           //caculate the computing time of fun1
    for(int i = 0;i < 100000;i++){
        ans1 = fun1(N);
    }
    stop = clock();
    tick1 = stop - start;
    totaltime1 = (double)tick1/CLK_TCK;
    duration1 = totaltime1/K;
    /****************
     * K needs to be big enough for algorithm2 to obtain a accurate running time
     * but K is too big for algorithm1 at the same time
     * K is set to 100000 for algorithm1 because 100000 is big enough when N = 1000
    *****************/

    start = clock();                           //caculate the computing time of fun2
    for(int i = 0;i < K;i++){
        ans2 = fun2(N);
    }
    stop = clock();
    tick2 = stop - start;
    totaltime2 = (double)tick2/CLK_TCK;
    duration2 = totaltime2/K;

    start = clock();                           //caculate the computing time of fun3
    for(int i = 0;i < K;i++){
        ans3 = fun3(N, X);
    }
    stop = clock();
    tick3 = stop - start;
    totaltime3 = (double)tick3/CLK_TCK;
    duration3 = totaltime3/K;

    //output the result
    printf("\n%25c %-20s %-20s %-20s %-20s\n", '\0', "Result", "Ticks", "Total time(sec)", "Duration(sec)");
    printf("%-25s %-20lf %-20lf %-20lf %-20.16lf\n", "Algorithm1", ans1, tick1, totaltime1, duration1);
    printf("%-25s %-20lf %-20lf %-20lf %-20.16lf\n", "Algorithm2(iterative)", ans2, tick2, totaltime2, duration2);
    printf("%-25s %-20lf %-20lf %-20lf %-20.16lf\n", "Algorithm2(recursive)", ans3, tick3, totaltime3, duration3);
    while(1){}
}

/********************
 *(4) Defination of the functions
*********************/
double fun1(int Exponent){
    long double ans = 1;
    for(int i = 0;i < Exponent;i++){
        ans *= X;
    }
    return ans;
}

double fun2(int Exponent){
    long double ans = 1;
    int noteven[20] = {0}; 
        /*****************
            noteven[i] records if X^(Exponet/2)*X^(Exponent/2) needs to mutiply X (that is Exponent is not even)
        in i(th) computation corresponding to the recursive method.
            the upper limit of the arry is set to 20 because the coresponding 
        recursive method time complexity is O(log N) and 2^20 > the largest K(100000)
        *****************/          
    int times = -1;    //record the times of divide Exponent by 2, index of array start by 0 so set times = -1 at first
    while(Exponent > 1){
        if(Exponent % 2 ==0)
            noteven[++times] = 0;
        else 
            noteven[++times] = 1;
        Exponent /= 2;
    }
    if(Exponent == 1) //after dividing the Exponent by 2, Exponent = 1 or Exponent = 0, Exponent = 1 means ans start by X
        ans = X;
    while(times >= 0){ //calculate the answer using the record of dividing times and if this time need to plus 1
        ans = ans*ans;
        if(noteven[times] == 1)
            ans *= X;
        times -= 1;
    }
    return ans;
}

double fun3(int Exponent, double X){
    if(Exponent == 0) return 1;
    if(Exponent == 1) return X;
    if(Exponent % 2 == 0)
        return fun3(Exponent/2, X*X);
    else
        return fun3(Exponent/2, X*X)*X;
}