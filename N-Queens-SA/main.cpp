#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 8
#define swap(a,b) {int t = a; a = b; b = t;}

int s[SIZE]={0};
//int row[1000]={0};//row[i]表示第i行有几个皇后
int row[SIZE]={0};
int col[SIZE]={0};//col[i]表示第i列有几个皇后
//pdiag[i]表示第i根主对角线（principal diagonal）皇后个数（从左上到右下的线）
int pdiag[SIZE*2-1]={0};
//pdiag[i]表示第i根副对角线（counter diagonal）皇后个数（从右上到左下的线）
int cdiag[SIZE*2-1]={0};

//打印棋盘
void  print(int s[])
{
    printf("\n");
    for(int i=0;i<SIZE;i++) {
        for (int j = 0; j < SIZE; j++)
            if(s[i]==j) printf("● ");
            else printf("□ ");
        printf("\n");
    }
}
//随机产生一个从start到end（不包括end）的数，x是随机因素
int myRandom(int start=0,int end=100,int x=0)
{
    srand((unsigned)time(NULL)+x);
    return rand()%(end-start);
}

//随机生成皇后,这样生成的冲突值比较小，x可以生成不同的种子
void randomQueen(int s[],unsigned x=0)
{
    for(int i=0;i<SIZE;i++)
        s[i]=myRandom(0,SIZE,i+x);
}

int  heuristic(int s[])
{
    //重新对列、主、副对角线置0
    memset(row,0,sizeof(col));
    memset(col,0,sizeof(col));
    memset(pdiag,0,sizeof(pdiag));
    memset(cdiag,0,sizeof(cdiag));
    int h=0;
    int s2=2*SIZE;
    for(int i=0;i<SIZE;i++)
    {
        col[s[i]]++;
        // row[i]++;
        //主(副)对角线条数是2*size,size为皇后总个数
        //主对角线编号：最右上角为0，最左下角为2*size-1
        //可以证明对角线上的下面p值都是一样，且为上面定义的编号
        //int p=i - s[i] + SIZE - 1;
        pdiag[i - s[i] + SIZE - 1]++;
        //p为副对角线编号
        //p=i+s[i];
        cdiag[i+s[i]]++;
    }
    for(int i=0;i<s2;i++)
    {
        if(i<SIZE)
        {
            h+=(col[i]-1)*col[i]*0.5;
            //h+=(row[i]-1)*row[i]*0.5;
        }
        h+=pdiag[i]*(pdiag[i]-1)*0.5;
        h+=cdiag[i]*(cdiag[i]-1)*0.5;
    }
    return  h;
}

//将第row1行中的现有皇后调整到第col1列，然后计算其评估值
//h为现有评估值
int adjust(int s[],int row1,int col1,int h)
{
    //列上增加值
    int nowCol=s[row1];//现在第row1行皇后所在列位置
    h+=(col[col1]-col[nowCol]+1);
    //主对角线上增加值
    h+=(pdiag[row1-col1+SIZE-1]-pdiag[row1-nowCol+SIZE-1]+1);
    //副对角线上增加值
    h+=(cdiag[row1+col1]-cdiag[row1+nowCol]+1);
    return h;
}


//接受第row1行的皇后移动到col1列
void accept(int s[],int row1,int col1) {
    col[s[row1]]--;
    pdiag[row1 - s[row1] + SIZE - 1]--;
    cdiag[row1 + s[row1]]--;
    s[row1] = col1;
    col[col1]++;
    pdiag[row1 - col1 + SIZE - 1]++;
    cdiag[row1 + col1]++;
}

int findTwo(int s[])
{
    int col0,col2,flag=0;
    int row0,row2;
    for(int i=0;i<SIZE;i++)
    {
        //为0表示某列没有皇后
        if(col[i]==0) {col0=i;flag++;}
        //为2表示某列有2个皇后
        if(col[i]==2) {col2=i;flag++;}
        if(flag==2) break;
    }
    flag=0;
    for(int i=0;i<SIZE;i++)
        if(s[i]==col2)
        {
            flag++;
            //试着将2个皇后的其中一个皇后调整到没有皇后的列（col0）
            //将其临时调整到第i行，col0列,如果对角线有1个皇后显然不行
            if(pdiag[i-col0+SIZE-1]==0 && cdiag[i+col0]==0)
            {
                s[i]=col0;
                printf("\n成功！\n");
                return 1;
            }
            if(flag==2) return 0;
        }
    return 0;
}

void exchange(int s[],int c)
{
    int r1,r2,r3,r4,k1=0,k2=1;
    do
    {
        srand((unsigned)time(NULL)+k1);
        r1=rand()%(SIZE);
        r2=rand()%(SIZE);
        k1++;
    }while(r1==r2);
    swap(s[r1],r2);
    do
    {
        srand((unsigned)time(NULL)+c+k2);
        r3=rand()%(SIZE);
        r4=rand()%(SIZE);
        k2++;
    }while(r3==r4);
    swap(s[r3],r4);
}

int hillClimbing(int s[])
{
    int h=heuristic(s);
    int curr=h;//当前评估代价
    int min=h;//最小代价
    int lastMin=h;//上一轮最小代价
    //下面这几个都是计数器
    //int counter=0;//最初想随机选择一个优于当前的状态的后继
    int c=0;//迭代轮次
    int cc=0;//交换次数
    int k=0;//没大用
    while (1)
    {
        //counter=0;
        c++;
        int flag=0;
        int minValue=s[0],minLine=0;//分别为：代价最小时的皇后的列号、行号
        for(int i=0;i<SIZE;i++) //第i行
        {
            for(int j=0;j<SIZE;j++)//第i行皇后放第j列上
            {
                if(j!=s[i]) //s[i]为第i行皇后的列号
                {
                    //临时调整：将第i行的皇后放在第j列上，计算评估值
                    h=adjust(s,i,j,curr);
                    //counter++;
                    if(h<=min)
                    {
                        minLine=i;
                        minValue=j;
                        accept(s,i,j);
                        min=h;
                    }
                    if(h==0 || h==1) //特殊处理
                    {
                        flag=1;
                        break;
                    }
                }
            }
            if(flag==1) break;
        }
        //printf("%d ",min);
        if(min==0)  //代价为0，表示已找到一种N皇后的排列
        {
            printf("\n迭代次数：%d\n",c);
            printf("\n随机交换次数：%d\n",cc);
            s[minLine]=minValue;
            return c;
        }
        else if(min==1) //用findTwo函数手工调整
        {
            accept(s,minLine,minValue);
            if(findTwo(s))
            {
                printf("\n迭代次数：%d\n",c);
                printf("\n随机交换次数：%d\n",cc);
                return c;
            }
            else //调整失败，还是用随机交换大法，管用
            {
                cc++;
                exchange(s,c);
                curr=heuristic(s);
                lastMin=curr;
                min=curr;
            }
        }
        else if(min==lastMin) //到达局部山峰，无法前进，只好随机交换大法
        {
            s[minLine]=minValue;
            if(k==1) //计数器
            {
                cc++;
                exchange(s,c);
                curr=heuristic(s);
                lastMin=curr;
                min=curr;
                k=0;
            }
            k++;
        }
        else
        {
            accept(s,minLine,minValue);
            curr=min;
            lastMin=min;
        }
    }
}

int simulatedAnnealing(int s[])
{
    int h=heuristic(s);//评估函数见前一博文
    if(h==0) return 0;
    int curr=h;//改变状态后的评估值
    int last=h;//上一次评估值
    int c=0;//迭代轮次计数器
    double T=SIZE*SIZE*1000;//初始温度
    double rate=0.999; //温度下降速率
    double minT=0.00001;
    int k1=0,k2=0;//两个计数器而已
    while (1)
    {
        int counter=0;
        c++;
        for(int i=0;i<SIZE;i++) //第i行
        {
            for(int j=0;j<SIZE;j++)//第i行皇后放第j列上
            {
                if(j!=s[i]) //s[i]为第i行皇后的现在列号
                {
                    //临时调整：将第i行的皇后放在第j列上，计算评估值
                    curr=adjust(s,i,j,last);
                    counter++;
                    if(curr==0)
                    {
                        printf("\n迭代次数：%d\n",c);
                        printf("\n执行次数=%d,未执行次数=%d\n",k1,k2);
                        accept(s,i,j);
                        return c;
                    }
                    int dE=curr-last;
                    int p=(int) 1000*exp(1.0*dE/T);//计算概率
                    //下面myRandom函数见前一博文
                    int ss=myRandom(0,1000,counter);
                    if(dE<=0 )
                    {
                        accept(s,i,j);
                        last=curr;
                        break;
                    }
                        //执行概率大于生成的概率：执行
                    else if(p>=ss) //可以和上面的合并，主要看有多少没执行或执行
                    {
                        accept(s,i,j);
                        last=curr;
                        k1++;
                        break;
                    }
                    else k2++;//printf("没执行\n");
                }
            }
        }
        T*=rate;//温度下降
        if(T<minT)
        {
            printf("没有找到!\n");
            printf("\n迭代次数：%d\n",c);
            printf("\n执行次数=%d,未执行次数=%d\n",k1,k2);
            return c;
        }
    }
}

int main(int argc,char *argv[]) {
    //int s[SIZE]={4,5,6,3,4,5,6,5};
    //int s[SIZE]={2,0,6,3,1,4,7,5};
    randomQueen(s,SIZE);
    printf("开始大小:%d\n",heuristic(s));
    printf("\n次数：%d\n",hillClimbing(s));
//    printf("\n次数：%d\n",simulatedAnnealing(s));
    printf("结束大小：%d\n",heuristic(s));
    return 0;
}