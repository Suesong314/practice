#include<stdio.h>
#include<conio.h>
#include<time.h>
#include"snake.h"

enum direction dire=you;                                       //初始方向设为右

int main(void){

    srand((unsigned)(time(NULL)));                             //用时间产生随机序列起始点

    printborder();
    gotoxy(20, 10);
    printf("按任意键开始游戏！\n");//打印开始界面
    getchar();

    system("cls");
    printborder();

    struct Snake *s, *tail, *head, food;                                      //构造初始蛇，有3个节点  //食物
    int score = 0;                                                            //分数

    tail = (struct Snake*)malloc(sizeof(struct Snake));
    s = tail;
    for(int i=0;i<2;i++){
        s->x = 1+i;
        s->y = 1;
        s->SnakeNext = (struct Snake*)malloc(sizeof(struct Snake));
        s = s->SnakeNext;
    }
    s->x=3;
    s->y=1;
    s->SnakeNext=NULL;
    head = s;
    s=tail;
    while(s!=NULL){
        gotoxy(s->x, s->y);
        printf("@");
        s = s->SnakeNext;
    }
    foodcreat(&food,tail);

    while((!impactborder(head))&&(!impactsnake(head,tail))){                                 //游戏开始
        if(kbhit()){                          
            char c = getch();
            transdire(c, &dire);
        }
        if(ifeatfood(head,food,dire)){
            eatfood(&head, food);
            score++;
            foodcreat(&food, tail);
        }
        else snakemove(tail, dire);
        Sleep(100);
    }

    system("cls");
    printborder();
    gotoxy(20, 10);
    printf("您的得分是：%d分！\n",score);

    return 0;
}