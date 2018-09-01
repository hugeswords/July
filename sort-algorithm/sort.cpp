#include<iostream>
#include<vector>
#include<stdlib.h>
using namespace std;
/*
 * brief:冒泡排序
 *
 *
 */
void bubble(vector<int> &array){
    for(int i=0;i<array.size()-1;i++){
        for(int j=0;j<array.size() -i-1;j++){
            if(array[j]>array[j+1]){
                swap(array[j],array[j+1]);
            }
        }
    }

}
void print(vector<int> array){
    for(int i=0;i< array.size();i++){
     cout<<array[i]<<'\t';
    }
    cout<<endl;
}
int main(){
    vector<int> array(10);
    for(int i=0;i<10;i++){
        array[i] = rand()%101;
    }
    print(array);
    bubble(array);
    print(array);
    return 0;
    
}
