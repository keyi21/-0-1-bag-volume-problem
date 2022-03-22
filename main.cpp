//
//  main.cpp
//  软件工程1
//
//  Created by 可意 on 2022/3/9.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include<cstdlib>
#define N 6
using namespace std;

int BagVolume ;//规定背包最大容量
int  value[6]; //创建数组分别存储value及volume数据
int  volume[6];
float sortBest[6] = {0};
float Sort[6];
int number[N];
int num  ;
int V[200][200];//动态规划表格
int item[6];//动规选择标记
double start = 0,end = 0;//记录时间

double bagnow = 0.0;//当前背包重量
double bagvalue = 0.0;//当前背包中物品价值
double bestp = 0.0;//当前最优价值
double perp[100];//单位物品价值排序后
int order[100];//物品编号
int put[100];//设置是否装入

int Used[100];//背包使用状况


//打开文件
int FOP(){
    ifstream  myfile("/Users/keyi/Documents/专业作业/软件工程/软件工程1/data.txt");//从已有文件读入
    
    //打不开文件，返回
    if (!myfile.is_open()){
        cout << "can not open this file" << endl;
        return 0;
    }
    //从data文件中读入value数据
    myfile>>num;
    myfile>>BagVolume;
    cout<<"装入物品数量："<<num<<" 最多装入体积：" <<BagVolume<<endl;
    for (int i = 1; i<=num; i++) {
        for (int j = 0; j < 2; j++){
            if (j==0) {
                myfile>>value[i-1];
            }else{
                myfile>>volume[i-1];
            }
        }
        
    }
    cout<<"待选物体价值：";
    for (int i = 0; i<num; i++) {
        cout<<" "<<value[i];
    }
    cout<<endl;
    cout<<"待选物体体积：";
    for (int i = 0; i<num; i++) {
        cout<<" "<<volume[i];
    }
    cout<<endl;
    myfile.close();
    return 0;
}

//获得价值比
void VoDiVa(){
    cout<<"物质价值比：";
    for (int i = 0; i<num; i++) {
        sortBest[i] = (float)value[i]/volume[i];
        Sort[i] = sortBest[i];
        number[i] = i;
        printf("%2f ",Sort[i]);
    }
    cout<<endl;

}
void PopSort(){
    int swap1 = 0,swap2 = 0;
    
    for (int i = 0; i < num; ++i){
        for (int j = num - 2; j >= i; --j) {
            if (Sort[j] < Sort[j + 1]){
                swap1 = Sort[j+1];
                Sort[j+1] =Sort[j];
                Sort[j] = swap1;
                swap2 =number[j+1];
                number[j+1] = number[j];
                number[j] = swap2;
            }
        }
    }
   
    cout<<"价值比排序为:"<<endl;
    for (int i = 0; i<N; i++) {
        cout<<"["<<number[i]+1<<"]"<<Sort[i]<<"->";
    }
    cout<<"由大到小"<<endl;
}

//贪心算法
void Greed()
{
   float temp=0;
   float result=0;
   float bv=BagVolume;
    for(int i=0;i<num;i++)
    {
        //寻找最高价值的物品
        for(i=0;i<num;i++){
            if(temp<sortBest[i])
                temp=sortBest[i];
        }
        //将最高价值的物品装入背包
        for(i=0;i<num;i++){
            if (temp==sortBest[i]){
                sortBest[i]=0;
            }
            if (volume[i]<=bv){
                result=result+value[i];
                cout<<"被装入的物品编号为："<<i+1<<endl;
            }
            bv=bv-volume[i];
        }
    }
    cout<<"结果为："<<result<<endl;
}

//
int max(int a, int b)
{
    if (a >= b)
        return a;
    else return b;
}
int DynamicProgramming()
{
    int i, j;
    for (i = 0; i <= num; i++)
        V[i][0] = 0;
    for (j = 0; j <= BagVolume; j++)
        V[0][j] = 0;
    for (i = 0; i < num; i++){
        for (j = 0; j < BagVolume+1; j++){
            if (j<volume[i])
                V[i][j] = V[i - 1][j];
            else
                V[i][j] = max(V[i - 1][j], V[i - 1][j - volume[i]] + value[i]);
        }
    }
    j = BagVolume;
    for (i = num - 1; i >= 0; i--)
    {
        if (V[i][j]>V[i - 1][j])
        {
            item[i] = 1;
            j = j - volume[i];
        }
        else
            item[i] = 0;
    }
    printf("选中的物品是:\n");
    for (i = 0; i<num; i++)
        printf("%d ", item[i]);
    printf("\n");
    for (int i = 0; i < num; i++){
        for (int j = 0; j < BagVolume+1; j++){
            printf("%d\t ", V[i][j]);
            if (j == BagVolume){
                printf("\n");
            }
        }
    }
    printf("背包装在最大价值为%d\n", V[num - 1][BagVolume]);
    //system("pause");
    return 0 ;
}
//回溯函数
void backtrack(int i)
{
    double bound(int i);
    if(i>num)
    {
        bestp = BagVolume;
        return;
    }
    if(bagnow+volume[i]<=BagVolume)
    {
        bagnow+=volume[i];
        bagvalue+=value[i];
        put[i]=1;
        backtrack(i+1);
        bagnow-=volume[i];
        bagvalue-=value[i];
    }
    if(bound(i+1)>bestp)//符合条件搜索右子数
        backtrack(i+1);
}

//计算上界函数
double bound(int i)
{
    double leftw= BagVolume-bagnow;
    double b = bagvalue;
    while(i<=num&&volume[i]<=leftw)
    {
        leftw-=volume[i];
        b+=value[i];
        i++;
    }
    if(i<=num)
        b+=value[i]/volume[i]*leftw;
    return b;

}


int FCLZ(){
    ofstream outfile("out.txt", ios::trunc);//向文件导出；
    //将数据输出至out.txt文件中
    for (int i = 0; i < 2; i++)
    {
        outfile  << Used << "    " << BagVolume << "    "<< endl;
    };
    outfile.close();
    return 0;;
}

int main(){
    int i = 1;
    
    printf("文件装入\n");
    FOP();
    VoDiVa();
    PopSort();
    printf("1.贪心算法 2.动态规划算法 3.回溯法(输入-1退出程序）\n");
    
    
    while(i>0){
        printf("请选择要使用的算法：");
        cin>>i;
        switch (i) {
            case 1:
                startTime = clock();
                Greed();
                startTime = clock();
                cout<<"程序运行时间："<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
                break;
            case 2:
                startTime = clock();
                DynamicProgramming();
                startTime = clock();
                cout<<"程序运行时间："<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
                
                break;
                //();
            case 3:
               startTime = clock();
                backtrack(1);
                printf("最有价值为：%lf\n",bestp);
                printf("需要装入的物品编号是：");
                for(i=1;i<=num;i++)
                {
                    if(put[i]==1)
                        printf("%d ",order[i]);
                }
                cout<<endl;
                startTime = clock();
                cout<<"程序运行时间："<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<endl;
                
                break;
            default:
                break;
        }
    }
   
    printf("将文件导出至out.txt中\n");
     FCLZ();
    return 0;
   
}
