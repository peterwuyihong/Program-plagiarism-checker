#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <cstring>

using namespace std;  //
#define N 3 //ͣ����park
#define M 4 //ͨ��line

//����
typedef struct Car{
    int num;
    int time;
}Car;

//ջ
typedef struct stack{
    Car *base;
    Car *top;
    int curlen;
}Park,Tmp;

Park park; //ͣ����(ջ)
Tmp tmp; //��ʱ��·��(ջ)

//�����н��:������Ϊ����
typedef struct Qnode{
    Car car;
    struct Qnode *next;
}Qnode, *queuePtr;

//������
typedef struct queue{
    queuePtr front;
    queuePtr rear;
    int curlen;
}Line;

Line line; //ͨ��(������)

//��ʼ��ͣ����park(ջ)
void Initpark(){
    park.base=new Car [N];
    park.top=park.base;
    park.curlen=0;
}

//��ʼ����ʱ��·��tmp(ջ)
void Inittmp(){
    tmp.base=new Car [N];
    tmp.top=tmp.base;
    tmp.curlen=0;
}

//��ʼ��ͨ��line(������)
void Initline(){
    line.front =line.rear=new Qnode;
    line.front->next=NULL;
    line.curlen=0;
}

//���ӽ�ͣ����park(ջ)
void Inpark(Car e){
    *(park.top)=e;
    park.top++;
    park.curlen++;
    cout<<"����"<<e.num<<"ͣ����ͣ������"<<park.curlen<<"��λ��."<<endl;
}

//���ӽ�ͨ��line(������)
void Inline(Car e){
    Qnode *s = new Qnode ;
    s->car=e;
    s->next=NULL;
    line.rear->next=s;
    line.rear=s;
    line.curlen++;
    cout<<"����"<<e.num<<"ͣ����ͨ����"<<line.curlen<<"��λ��."<<endl;
}

//���ӽ�ȥ��ʱ��·��tmp(ջ)
void Intmp(Car e){
    *(tmp.top)=e;
    tmp.top++;
    tmp.curlen++;
}

//��ջ����
void Outstack(stack *s){
    s->top--;
    s->curlen--;
}

//ͨ��line(������)�ĵ�һ��������ͷԪ��
Car Outline(){
    Qnode *firstqnode=line.front->next;
    Car firstcar=firstqnode->car;
    line.front->next=firstqnode->next;
    line.curlen--;
    return firstcar;
}

//���ӳ�ͣ����park
void Outpark(Car e){
    int num=e.num;
    int outtime=e.time; //�뿪ʱ��
    Car *c=park.top-1; //ջ��Ԫ��
    while(c->num!=num&&park.top>park.base){
        Intmp(*c); //ջ��Ԫ��(����)����ʱ��·��
        Outstack(&park); //ջ��Ԫ��(����)��ʱ����ȥ
        c--;
    }
    if(park.top==park.base) {
        cout<<"ͣ�����޴˳�."<<endl;
    }
    else{
        int spendtime=outtime-(c->time);
        cout<<"ͣ��ʱ�䣺"<<spendtime<<endl;
        cout<<"�շѣ�"<<spendtime*2<<endl;
        Outstack(&park); //���ӳ�ͣ����
    }

    //��������ʱ��·����ĳ��ӳ�tmpջ,����parkջ
    while(tmp.curlen>0){
        Outstack(&tmp);
        Inpark(*(tmp.top));
    }

    //��ͨ��line��Ķ�ͷԪ��(����)��ͣ����park
    while(park.curlen<N&&line.curlen>0){
        Car linefirstcar=Outline();
        linefirstcar.time=e.time;
        Inpark(linefirstcar);
    }
}

void Dispark(){
    cout<<"ͣ����:"<<endl;
    Car *p=park.base;
    while(p!=park.top){
        cout<<"����"<<p->num<<"����ʱ�䣺"<<p->time<<endl;
        p++;
    }
}
void Disline(){
    cout<<"ͨ��:"<<endl;
    Qnode *p=line.front->next;
    while(p){
        cout<<"����"<<(p->car).num<<"����ʱ�䣺"<<(p->car).time<<endl;
        p=p->next;
    }
}

int main (){
    Initpark();
    Inittmp();
    Initline();
    char a[5];
    cout<<"����������� ���ƺţ� ʱ�䣺"<<endl;
    while (cin >> a){
        if ( !strcmp (a,"A")){
            Car car;
            cin>>car.num>>car.time;
            if(park.curlen<N)
                Inpark(car);
            else if(line.curlen<M)
                Inline(car);
            else
                cout<<"������˼,�޿յ�!"<<endl;
        }
        else if (!strcmp (a,"D")){
            Car car;
            cin>>car.num>>car.time;
            Outpark(car);
        }
        else if (!strcmp (a,"P")){
            Dispark();
        }
        else if (!strcmp (a,"W")){
            Disline();
        }
        else if (!strcmp (a,"E")){
            break;
        }
    }
}
