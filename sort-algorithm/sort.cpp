//快速排序，最快的，如果有比他更快的，那么他就得改名字了
//1.反正大致上：快速排序>堆排序>归并排序>基数排序>希尔排序
//2.O(n)复杂度的排序有3个，计数排序、基数排序、桶排序，不过使用场景有限制，对元素也有要求
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/time.h>
using namespace std;
inline int min(int a,int b) {
    return a<b?a:b;
    }
void print(vector<int> array){
    for(int i=0;i< array.size();i++){
     cout<<array[i]<<'\t';
    }
    cout<<endl;
}
/*=========================================================*/
//01-冒泡排序
void bubble(vector<int> &array){
    int len = array.size();
    for(int i=0;i<len-1;i++){
     // i代表趟数，每一躺找出最大元素
        for(int j=0;j<len-i-1;j++){
            if(array[j]>array[j+1]){
                swap(array[j],array[j+1]);
            }
        }
    }
}
/*=========================================================*/
//02-优化的冒泡排序
//优化的冒泡排序，如果第i躺排序中没有进行swap，说明已经排好序了，可以直接返回
void bubble2(vector<int> &array){
    int len = array.size();
    bool is_swap = true;
    for(int i=0;i<len-1;i++){
     // i代表趟数，每一躺找出最大元素
        if(is_swap){
            is_swap = false;
            for(int j=0;j<len-i-1;j++){
                if(array[j]>array[j+1]){
                    swap(array[j],array[j+1]);
                    is_swap = true;
                }
            }
        }else{
            break;
        }
    }
}
/*=========================================================*/
//03-双向的冒泡排序(鸡尾酒排序)
//也是冒泡排序的变种，从后往前找最小，从前往后找最大
void cocktail(vector<int> &v) {
    int high=v.size();
    int low=0;
    bool swapped=true;
    while(swapped) {
        swapped=false;
        for(int i=high-1; i>low; i--) {
            if(v[i]<v[i-1]) {
                swap(v[i],v[i-1]);
                swapped=true;
            }
        }
        low++;
        for(int i=low; i<high; i++) {
            if(v[i]>v[i+1]) {
                swap(v[i],v[i+1]);
                swapped=true;
            }
        }
        high--;
    }
}
/*=========================================================*/
//04-奇偶的冒泡排序(奇偶排序)
void oddeven(vector<int> &v){
    int i,j;
    bool swapped=true;
    int len = v.size();
    while(swapped){
        swapped=0;
        for(i=0;i<len-1;i+=2){
            if(v[i]>v[i+1]){
                swap(v[i],v[i+1]);
                swapped=true;
            }
        }
        for(i=1;i<len-1;i+=2){
            if(v[i]>v[i+1]){
                swap(v[i],v[i+1]);
                swapped=true;
            }
        }
    }
}
/*=========================================================*/
//05-选择排序
//交换的次数明显少于冒泡排序，性能应该优于冒泡排序
void select(vector<int> &v){
    int j,min;
    int len = v.size();
    for(int i=0;i<len;i++){
        for(j=i+1,min=i;j<len;j++){
            if(v[j]<v[min]) min=j;
        }
        swap(v[i],v[min]);
    }
}
/*=========================================================*/
//06-插入排序
void insert(vector<int> &v){
    int len = v.size();
    int i,j,tmp; //存放当前待插入的元素
    for(i=1;i<len;i++){
        tmp=v[i];
        for(j=i;j>0&&v[j-1]>tmp;j--){
            v[j]=v[j-1];
        }
        v[j] = tmp;
    }
}
/*=========================================================*/
//07-希尔排序
void shell(vector<int> &v) {
    int gap,i,j,k,tmp,len=v.size();
    for(gap=len/2; gap>0; gap/=2)
        for(i=0; i<gap; i++) {
            for(j=i+gap; j<len; j+=gap) {
                tmp=v[j];
                for(k=j; k>=gap&&tmp<v[k-gap]; k=k-gap) {
                    v[k]=v[k-gap];
                }
                v[k]=tmp;
            }
        }
}

/*=========================================================*/
//08-快速排序
//第一个元素作为关键字，从后往前找比关键字小的元素，直接赋值给low，
//从前往后找比关键字大的元素，直接赋值给high,最后把关键赋值给low
int partition(vector<int> &v,int low,int high) {
    int tmp=v[low];
    while(low<high) {
        while(v[high]>tmp&&high>low)  high--;
        v[low]=v[high];
        while(v[low]<=tmp&&low<high)  low++;
        v[high]=v[low];
    }
    v[low]=tmp;
    return low;
}
void quicksort(vector<int> &v,int low,int high) {
    if(low<high) {
        int k=partition(v,low,high);
        quicksort(v,low,k-1);
        quicksort(v,k+1,high);
    }
}

/*=========================================================*/
//09-归并排序
//不断拆分，只剩一个元素，然后合并
void merge(vector<int> &v,int first,int mid,int last) {
    vector<int> tmp(last-first+1);
    int i=first,j=mid+1;//充当指针的作用，分别指向两个数组的起始位置
    int t=0;//临时数组的指针
    while(i!=mid+1&&j!=last+1) {
        if(v[i]<v[j])
            tmp[t++]=v[i++];
        else
            tmp[t++]=v[j++];
    }
    while(i!=mid+1) {
        tmp[t++]=v[i++];//补上尾巴
    }
    while(j!=last+1) {
        tmp[t++]=v[j++];//补上尾巴，只有一个while循环会被执行
    }
    for(i=first,t=0; i<=last; ++i,++t) {
        v[i]=tmp[t];//没有返回值，参数是引用
    }
}
void mergesort(vector<int> &v,int first,int last) { //first和last都是下标
    if(first<last) {
        int mid=(first+last)/2;
        mergesort(v,first,mid);
        mergesort(v,mid+1,last);
        merge(v,first,mid,last);
    }
}
void mergesort2(vector<int> &v) { //非递归，自底向上的归并排序
    for(int i=2; i<v.size(); i*=2) {
        for(int j=0; j<v.size(); j+=i) {
            int end=min(j+i-1,v.size()-1);
            merge(v,j,(j+end)/2,end);
        }
    }
}
/*=========================================================*/
//10-堆排序
//如果要升序，那么就要建立大根堆
void adjust(vector<int> &v,int end,int parent) { //从上往下调整，小的元素一直下沉
    //建立父子节点索引
    int tmp=v[parent];
    int child=2*parent+1;
    while(child<end) {
        //找到子节点中的较大索引
        if(child+1<end&v[child]<v[child+1])
            ++child;
        //如果父节点比两个都大，说明满足约束，跳出循环,因为是从最后一个父节点开始调整的
        if(tmp>=v[child]){
            break;
        }else{
            //如果子节点大，那就把父子节点值交换，继续和孙节点比较
            swap(v[parent],v[child]);
            parent=child;
            child=2*child+1;
        }
    }
}
void heapsort(vector<int> &v) {
    for(int i = v.size()/2 -1; i >= 0; i--) {
        //从最后一个父节点开始调整
        adjust(v,v.size(),i);//首先堆化数组
    }
    for(int i=v.size()-1; i>0; i--) {
        swap(v[0],v[i]);//堆顶元素和最后一个元素交换
        adjust(v,i,0);//堆被改变了，需要重新调整
    }
}


int main(){
    struct timeval start,end;
    float cost_ms;
    srand(time(NULL));
    const int LEN = 10000;
    vector<int> array(LEN);
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);

    //01
    //print(array);
    gettimeofday(&start,NULL);
    bubble(array);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("01普通冒泡排序  cost: [%f]ms\n",cost_ms);
    //print(array);

    //02
    array.clear();
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);
    //print(array);
    gettimeofday(&start,NULL);
    bubble2(array);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("02优化冒泡排序  cost: [%f]ms\n",cost_ms);
    //print(array);

    //03
    array.clear();
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);
    //print(array);
    gettimeofday(&start,NULL);
    cocktail(array);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("03鸡尾酒冒泡排序cost: [%f]ms\n",cost_ms);
    //print(array);
    
    //04
    array.clear();
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);
    //print(array);
    gettimeofday(&start,NULL);
    oddeven(array);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("04奇偶排序cost: [%f]ms\n",cost_ms);
    //print(array);

    //05
    array.clear();
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);
    //print(array);
    gettimeofday(&start,NULL);
    select(array);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("05选择排序cost: [%f]ms\n",cost_ms);
    //print(array);

    //06
    array.clear();
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);
    //print(array);
    gettimeofday(&start,NULL);
    insert(array);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("06插入排序cost: [%f]ms\n",cost_ms);
    //print(array);

    //07
    array.clear();
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);
    //print(array);
    gettimeofday(&start,NULL);
    shell(array);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("07希尔排序cost: [%f]ms\n",cost_ms);
    //print(array);
    
    //08
    array.clear();
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);
    //print(array);
    gettimeofday(&start,NULL);
    quicksort(array,0,LEN-1);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("08快速排序cost: [%f]ms\n",cost_ms);
    //print(array);

    //09
    array.clear();
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);
    //print(array);
    gettimeofday(&start,NULL);
    mergesort(array,0,LEN-1);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("09归并排序cost: [%f]ms\n",cost_ms);
    //print(array);

    //10
    array.clear();
    for(int i=0;i<LEN;i++) array.push_back(rand()%1001);
    //print(array);
    gettimeofday(&start,NULL);
    heapsort(array);
    gettimeofday(&end,NULL);
    cost_ms = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec-start.tv_usec)/1000;
    printf("10堆排序  cost: [%f]ms\n",cost_ms);
    //print(array);




    return 0;
}
