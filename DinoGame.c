//Dino Game version 1.2.7
//Press Space To Jump
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define canvas 50
void display(char floor[],int lowerlimit,int upperlimit){
    int i;
    for(i = lowerlimit;i<upperlimit;i++){
        printf("%c",floor[i]);
    }
}

void gameOver(int *matchEnd,int score){
    printf("\n\n\n\n Game Over !\n\tYou collided with the barrier :(");
    printf("\n\tYour Final Score : %d",score);
    *matchEnd = 1;
}

void insertBarrier(char *floor){
    int upperlimit = canvas;
    int lowerlimit = canvas - 15;
    floor[rand() % (upperlimit - lowerlimit + 1) + lowerlimit] = 'X';
}

void shiftLeft(char *floor){
    int i = 0;
    for(i = 0;i<canvas-1;i++){
        floor[i] = floor[i+1];
        floor[i+1] = '_';
    }
}

void main(){
    int runtime = 0,matchEnd = 0,i,score=0;
    int currentFloor = 1;
    int jumpDelay = 3;
    int sleepTime;
    int playerDisplayPos = 6;
    char floor1[canvas],floor2[canvas];

    //Initing Game Floors
    for(i = 0;i<canvas;i++){
        floor1[i] = '_';
        floor2[i] = ' ';
    }
    
    //Generating Random Seeds
    srand(time(0));

    //Main Game Loop
    for(runtime = 0;matchEnd != 1;runtime++,score++){
        //Detecting Spacebar Input & Shifting Floors For Player     && notInAir == 1
        if(kbhit() && getch() == 32 && currentFloor == 1){
            currentFloor = 2;
            runtime = 0;
        }
        
        if(runtime > jumpDelay && currentFloor == 2){
            currentFloor = 1;
        }

        //Shifting Barrier To Left
        shiftLeft(floor1);

        //Displaying Match Canvas & 
        //Player Position Of Floor
        printf("\n\n\n\t");
        //Second Floor Printing
        display(floor2,0,playerDisplayPos);
        if(currentFloor == 2){
            printf("O");
        }
        display(floor2,playerDisplayPos,canvas);

        printf("\n\t");
        //First Floor Printing
        display(floor1,0,playerDisplayPos);
        if(currentFloor == 1){
            printf("O");
        }else{
            printf("%c",floor1[playerDisplayPos]);
        }
        display(floor1,playerDisplayPos+1,canvas);
        printf("\n\tScore : %d",score);

        //Inserting Barriers At Random Position On Interval Of 10
        if(score%10==0){
            insertBarrier(floor1);
        }

        //Barrier Collision Checking
        if(floor1[playerDisplayPos] == 'X' && currentFloor == 1){
            gameOver(&matchEnd,score);
            getch();
            getch(); /*Second getch() is for people that presses Space bar multiple
            times without realizing that game is over because fps is faster on higher score*/
        }
        
        //FPS Settings
        if(score < 100){
            sleepTime = 150;
        }else if(score > 100 && score < 200){
            sleepTime = 120;
        }else if(score > 200 && score < 300){
            sleepTime = 100;
        }else if(score > 300 && score < 500){
            sleepTime = 80;
        }else if(score > 500 && score < 700){
            sleepTime = 60;
        }else if(score > 700 && score < 1000){
            sleepTime = 40;
        }else if(score > 1000 & score < 2000){
            sleepTime = 10;
        }else{
            sleepTime = 1;
        }
        Sleep(sleepTime);

        
        //Clearing Screen First
        /*not using clrscr() because i'm using gcc compiler and command prompt
        to running this game*/
        system("cls");
    }
}