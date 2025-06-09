#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <direct.h>

#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 75
#define ARROW_LEFT 77
#define W 119
#define S 115
#define A 97
#define D 100
#define SPACE 32
#define Q 113
#define ESC 27
#define ENTER 13
#define P 112
#define H 25 
#define G 50 

char credits[57][30]={
        {"CREDITS                      "},
        {"                             "},
        {"                             "},
        {"                             "},
        {"A GAME BY:                   "},
        {"                             "},
        {"PAVLOS DRATZIDIS             "},
        {"LEONIS PESHKOY               "},
        {"                             "},
        {"                             "},
        {"                             "},
        {"PRODUCERS-DESIGNERS:         "},
        {"                             "},
        {"PAVLOS DRATZIDIS             "},
        {"LEONIS PESHKOY               "},
        {"                             "},
        {"                             "},
        {"                             "},
        {"PROGRAMMERS:                 "},
        {"                             "},
        {"PAVLOS DRATZIDIS             "},
        {"LEONIS PESHKOY               "},
        {"                             "},
        {"                             "},
        {"                             "},
        {"ARTITS:                      "},
        {"                             "},
        {"PAVLOS DRATZIDIS             "},
        {"LEONIS PESHKOY               "},
        {"                             "},
        {"                             "},
        {"                             "},
        {"SOUND DESIGNRES:             "},
        {"                             "},
        {"PAVLOS DRATZIDIS             "},
        {"LEONIS PESHKOY               "},
        {"                             "},
        {"                             "},
        {"                             "},
        {"CAST:                        "},
        {"                             "},
        {"SNAKE                        "},
        {"APPLE                        "},
        {"GREEN GRASS                  "},
        {"LESS GREEN GRASS             "},
        {"ALL 150 WALLS                "},
        {"                             "},
        {"                             "},
        {"                             "},
        {"SPECIAL THANKS TO:           "},
        {"                             "},
        {"STOUS KATHIGITES THS         "},
        {"PARASKEYIS POU MAS           "},
        {"AFHNOUN NA FTHAJOUME         "},
        {"GAMES!                       "},
        {"                             "},
        {"STIS MANADES MAS KAI STHN C! "},
};


typedef struct Snake Snake;
typedef struct Body Body;

struct Snake {
	Body* head;
};

struct Body{
	int x;
	int y;
	Body* next;
};

void CreaditsUpdateMAp(char map[25][50], char credits[57][30], int k);
void Menu(char map[H][G],int choise,int o);
void PrintSnake(Body* body);
void MoveSnake(Body* body,int temp[2]);
void deleteLast(Body* head, char map[H][G]);
void GrowSnake(Body* body);
void draw(char map[H][G],int applecount);
void mapreset(char map[H][G]);
void Apple(char map[H][G],Body* head,int apple[2]);
void Gameover(char map[H][G],int applecount,int choise,int o);
void updateMap(Body* head, char map[H][G]);
int CheckColision(Body* body,int temp[2],char map[H][G]);
void ClearScreen();
void destroy(Body **head);

int main(){
    Snake snake;
    
    bool restart=false;
    start:
    snake.head = (Body*)malloc(sizeof(Body));

	snake.head->x=12;
	snake.head->y=25;
    snake.head->next=NULL;

    char map[H][G];
    int applecount=1,apple[2];
    int dir=1,pspeed=1;
    bool gameover=true;
    int temp[2] = {};
    int tempDir = 1;
    int o=0,choise = 1;
    if (restart){
        restart= false;
        goto Restart;
    }
    srand(time(NULL));
    mapreset(map);
    system("cls");
    while (true){
        if (_kbhit()){
            switch (_getch()){
                case ARROW_UP:
                    if (choise!=1){
                       choise-=1;
                    }
                    break;
                case ARROW_DOWN:
                    if (choise<3){
                       choise+=1;
                    }
                    break;
                case ENTER:
                    goto endMenu;
                    break;
            }
        }else{
            if (o==60){
                o=0;         
            }else{
                o+=1;
            }
            
            Menu(map,choise,o);
            draw(map,applecount);
            ClearScreen();
        }
    }
    endMenu:
    system("cls");
    switch (choise)
    {
    case 1:
        break;
    case 2:
        ClearScreen();
        mapreset(map);
        for(int k=-25; k<75; k++){
            CreaditsUpdateMAp(map,credits,k);
            draw(map,applecount);
            ClearScreen();
        }
        goto start;
        break;
    
    case 3:
        ClearScreen();
        gameover = false;
        goto stop;
        break;
    }
    Restart:
    mapreset(map);
    Apple(map,snake.head,apple);
    Beep(750, 50);
    system("cls");
    while (gameover){
        temp[0] = snake.head->x;
        temp[1] = snake.head->y;
        if (_kbhit()){
            switch (_getch()){
                case ARROW_UP:
                    dir=1;
                    break;
                case ARROW_DOWN:
                    dir=-1;
                    break;
                case ARROW_RIGHT:
                    dir=2;
                    break;
                case ARROW_LEFT:
                    dir=-2;
                    break;
                case W:
                    dir=1;
                    break;
                case S:
                    dir=-1;
                    break;
                case A:
                    dir=2;
                    break;
                case D:
                    dir=-2;
                    break;
                case Q:
                    gameover=0;
                    break;
                case ESC:
                    gameover=0;
                    break;
                case P:
                    draw(map,applecount);
                    getch();
                     ClearScreen();
                    break;
            }
        if(tempDir != (dir*(-1))){
            tempDir = dir;
        }
        }else{
            switch(tempDir){
                case 1:
                    temp[0] -= pspeed;
                    break;
                case -1:
                    temp[0] += pspeed;
                    break;
                case 2:
                    temp[1] -= pspeed;
                    break;
                case -2:
                    temp[1] += pspeed;
                    break;
            }
            if (temp[0]==apple[0] && temp[1]==apple[1]){
                Beep(250, 50);
                Apple(map,snake.head,apple);
                GrowSnake(snake.head);
                applecount++;
            }
            deleteLast(snake.head, map);

            if(!CheckColision(snake.head,temp,map)){
                break;
            }
            MoveSnake(snake.head,temp);

            updateMap(snake.head,map);
            draw(map,applecount);
            ClearScreen();
        }
    }
    system("cls");
    Beep(500, 50);
    choise=1;
    while (true){
        if (_kbhit()){
            switch (_getch()){
                case ARROW_UP:
                    if (choise!=1){
                       choise-=1;
                    }
                    break;
                case ARROW_DOWN:
                    if (choise<3){
                       choise+=1;
                    }
                    break;
                case ENTER:
                    goto endGameover;
                    break;
            }
        }else{
            if (o==60){
                o=0;         
            }else{
                o+=1;
            }
            Gameover(map,applecount,choise,o);
            draw(map,applecount);
            printf("GAMEOVER!\n SCORE: %d",applecount-1);
            ClearScreen();
        }
    }
    endGameover:
    switch (choise)
    {
    case 1:
        restart=true;
        destroy(&snake.head);
        snake.head=NULL;
        system("cls");
        goto start;
        break;
    case 2:
        destroy(&snake.head);
        snake.head=NULL;
        system("cls");
        goto start;
        break;
    case 3:
        system("cls");
        break;
    }
    stop:
    printf("\nGOODBYE!!!");
    return 0;
}
void draw(char map[H][G], int applecount){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < H; i++){
        for (int j = 0; j < G; j++){
            if(map[i][j] == '\xB2'){
                SetConsoleTextAttribute(hConsole,85);//snake
                printf("%c",map[i][j]);
            }else if (map[i][j] == '\xFF'){
                SetConsoleTextAttribute(hConsole,69);//apple
                printf("%c",map[i][j]);
            }
            else if(map[i][j] == '\xDC' || map[i][j] == '\xDB' || map[i][j] == '\xDF'){
                SetConsoleTextAttribute(hConsole,8);//wall
                printf("%c",map[i][j]);
            }else{
                if((i+j)%2 == 0){
                    SetConsoleTextAttribute(hConsole, 32);
                    printf("%c",map[i][j]);
                }
                else{
                    SetConsoleTextAttribute(hConsole, 160);
                    printf("%c",map[i][j]);
                }
            }
            SetConsoleTextAttribute(hConsole,15);
        }
        printf("\n");
    }
    printf("Score(apples): %d\n",applecount-1);
    Sleep(170);
}
void PrintSnake(Body* body){
	if(body == NULL){
		return;
	}
	else{
		printf("playerx: %d, playery: %d \n", body->x, body->y);

		PrintSnake(body->next);
	}
}
void mapreset(char map[H][G]){
    for (int i = 0; i < H; i++){
        for (int j = 0; j < G; j++){
            if(i==12 && j==25){
                map[i][j]='\xB2';
            }else if (i==0){
                map[i][j]='\xDC';
            }else if (i==24){
                map[i][j]='\xDF';
            }else if (j==0 || j==49){
                map[i][j]='\xDB';
            }else{
                map[i][j]=' ';
            }
        }
    }
}
void Apple(char map[H][G],Body* head,int apple[2]){
    do{
        apple[0]=rand()%24+1;
    }while (apple[0]==head->x || apple[0]==0 || apple[0]==24);
    do{
        apple[1]=rand()%49+1;
    }while (apple[1]==head->y || apple[1]==0 || apple[1]==49);
    map[apple[0]][apple[1]]='\xFF';
}

void Menu(char map[H][G],int choise,int o){
    char Tite0[37] = {"_ _ _ ____ _    ____ ____ _  _ ____  "};
    char Tite1[37] = {"| | | |___ |    |    |  | |\\/| |___  "};
    char Tite2[37] = {"|_|_| |___ |___ |___ |__| |  | |___  "};
    char Tite3[37] = {"___ ____    ____ _  _ ____ _  _ ____ "}; 
    char Tite4[37] = {" |  |  |    [__  |\\ | |__| |_/  |___ "}; 
    char Tite5[37] = {" |  |__|    ___] | \\| |  | | \\_ |___ "};
    for(int i=0;i<37;i++){
        map[5][i+7]=Tite0[i];
        map[6][i+7]=Tite1[i];
        map[7][i+7]=Tite2[i];
        map[8][i+8]=Tite3[i];
        map[9][i+8]=Tite4[i];
        map[10][i+8]=Tite5[i];
    }
    char Title_6[11]={"   START   "};
    char Title_8[11]={"  CREDITS  "};
    char Title_7[11]={"   LEAVE   "};
    if (choise==1){
        if (o%2){
         Title_6[2]=' ';
         Title_6[8]=' ';
        }else{
         Title_6[2]='>';
         Title_6[8]='<';
        }
        
    }else if (choise==2){
        if (o%2){
         Title_8[1]=' ';
         Title_8[9]=' ';
        }else{
         Title_8[1]='>';
         Title_8[9]='<';
        }
        
    }
    else if (choise==3){
        if (o%2){
         Title_7[2]=' ';
         Title_7[8]=' ';
        }else{
         Title_7[2]='>';
         Title_7[8]='<';
        }
        
    }
    for(int i=0;i<11;i++){
        map[13][i+20]=Title_6[i];
        map[14][i+20]=Title_8[i];
        map[15][i+20]=Title_7[i];
    }
}

void Gameover(char map[H][G],int applecount,int choise,int o){
    char T1[12]={"GAMEOVER! :C"};
    for(int i=0;i<12;i++){
        map[9][i+20]=T1[i];
    }
    char T2[8];
    sprintf(T2,"SCORE: %d",applecount-1);
    int len = strlen(T2);
    for(int i=0;i<len;i++){
        map[10][i+22]=T2[i];
    }
    char Titl_1[11]={"  RESTART  "};
    char Titl_2[11]={"   START   "};
    char Titl_3[11]={"   LEAVE   "};
    if (choise==1){
        if (o%2){
         Titl_1[1]=' ';
         Titl_1[9]=' ';
        }else{
         Titl_1[1]='>';
         Titl_1[9]='<';
        }
        
    }else if (choise==2){
        if (o%2){
         Titl_2[2]=' ';
         Titl_2[8]=' ';
        }else{
         Titl_2[2]='>';
         Titl_2[8]='<';
        }
        
    }else if (choise==3){
        if (o%2){
         Titl_3[2]=' ';
         Titl_3[8]=' ';
        }else{
         Titl_3[2]='>';
         Titl_3[8]='<';
        }
        
    }
    for(int i=0;i<11;i++){
        map[12][i+20]=Titl_1[i];
        map[13][i+20]=Titl_2[i];
        map[14][i+20]=Titl_3[i];
    }
}

void GrowSnake(Body* body){
	if(body->next != NULL){
		GrowSnake(body->next);
	}
	else{
		body->next = (Body*)malloc(sizeof(Body));
		body->next->x = body->x+1;
		body->next->y = body->y+1;
		body->next->next = NULL;
	}
}

void updateMap(Body* head, char map[H][G]){
    map[head->x][head->y] = '\xB2';
    if(head->next != NULL){
        updateMap(head->next,map);
    }
}
void deleteLast(Body* head, char map[H][G]){
    if(head->next != NULL){
        deleteLast(head->next,map);
    }
    else{
        map[head->x][head->y] = ' ';
    }
}
void MoveSnake(Body* body,int temp[2]){
    int temp2[2];
	temp2[0]=body->x;
	temp2[1]=body->y;
	body->x = temp[0];
	body->y = temp[1];

	if(body->next != NULL){
		MoveSnake(body->next,temp2);
	}
}
int CheckColision(Body* body,int temp[2],char map[H][G]){

    if (map[temp[0]][temp[1]] == '\xDC' || map[temp[0]][temp[1]] == '\xDB' || map[temp[0]][temp[1]] == '\xDF'){
        return 0;
    }

    Body *current = body;
    Body *next;

    while (current != NULL)
    {
       next = current->next;
       if (current->x==temp[0] && current->y==temp[1]){
            return 0;
        }
       current = next;
    }

    return 1;
}
 void ClearScreen(){
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void destroy(Body **head){
    Body *current = *head;
    Body *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void CreaditsUpdateMAp(char map[25][50], char credits[57][30], int k){
    for(int i=1; i<24; i++){
        for(int j=0; j<30; j++){
            if((i+k)>=0 && (i+k)<57){
                map[i][j+19] = credits[i+k][j];
            }
            else
            {
                map[i][j+19] = ' ';
            }
        }
    }
}