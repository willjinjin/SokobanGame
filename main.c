#include <stdio.h>
#include <string.h>

int ROWS = 6;
int COLS = 6;


void MakeBox(char *design, int width, int height) {
    int k = 0; 

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                design[k] = '#';
            } else {
                design[k] = ' '; 
            }
            k++;
             
            
        }
        design[k] = '\n';
        k++;
    }
    design[k] = '\0';
    if (width > 2 && height > 2) {
        if (width % 2 != 0 && height % 2 != 0) {
            design[(width+1)*height/2 - 1] = 'X';
        }
        if (width % 2 == 0 && height%2 !=0) {
            design[(width+1)*height/2] = 'X';
            design[(width+1)*height/2 - 1] = 'X';
        }
        if (width % 2 != 0 && height % 2 == 0) {
            design[(width+1)*(height/2 - 1) + width/2  ] = 'X';
            design[(width+1)*(height/2) + width/2 ] = 'X';
        }
        if (width % 2 == 0 && height % 2 == 0) {
            design[(width+1)*(height/2 -1) + width/2] = 'X';
            design[(width+1)*height/2 + width/2] = 'X';
            design[(width+1)*(height/2 -1) + width/2 -1] = 'X';
            design[(width+1)*height/2 + width/2 - 1] = 'X';
        }
    }
}


void LocatePerson(int room[ROWS][COLS], int *row, int *col) {
    for (int i = 0; i<ROWS; i++) {
        for (int j = 0; j<COLS; j++) {
            if (room[i][j] == 5 || room[i][j] == 6) {
                *row = i;
                *col = j;
            }
        }
    }
}


void PrintRoom(int room[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (room[i][j] == 0) {
                printf("%c", ' ');
            }
            else if (room[i][j] == 1) {
                printf("%c", '#');
            }
             else if (room[i][j] == 2) {
                 printf("%c", '*');
             }
             else if (room[i][j] == 3) {
                 printf("%c", 'O');
             }
             else if (room[i][j] == 4) {
                 printf("%c", '@');
             }
             else if (room[i][j] == 5 || room[i][j] == 6) {
                 printf("%c", 'X');
             }
        }
        printf("\n");
    }
}


void InitialiseRoom(int room[ROWS][COLS], char *layout) {
    int k = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (layout[k] == '\0' ) {
                room[i][j] = 1;
            }
            else {
                room[i][j] = layout[k] - '0';
                k++;
            }
        }
    }
}

void UndoMove(int room[ROWS][COLS], char *allMoves) {
    char lastmove;
    int m = 0;
    int n = 0;
    int len = strlen(allMoves);
    char x = allMoves[len - 1];
    lastmove = allMoves[len - 2];
    if (len == 0) {
        return;
    }
    
    if (lastmove == 'w') {
        m--;
    }
    else if (lastmove == 's') {
        m++;
    }
    else if (lastmove == 'a') {
        n--;
    }
    else if (lastmove == 'd') {
        n++;
    }
    int rpos, cpos;
    LocatePerson(room, &rpos, &cpos);
    
    if (room[rpos][cpos] == 6) {
        room[rpos][cpos] = 2;
    }
    else {
        room[rpos][cpos] = 0;
    }
    if (room[rpos-m][cpos-n] == 2){
        room[rpos-m][cpos-n] = 6; 
    }
    else {
        room[rpos-m][cpos-n] = 5;
    }
    
    if (x == '1') {
        if (room[rpos+m][cpos+n] == 4) {
            room[rpos+m][cpos+n] = 2;
        }
        else {
            room[rpos+m][cpos+n] = 0;
        }
        if (room[rpos][cpos] == 2) {
            room[rpos][cpos] = 4;
        }
        else {
            room[rpos][cpos] = 3;
        }
    }
    allMoves[len-2] = '\0';
}


void MakeMove(int room[ROWS][COLS], char move, char *allMoves) {
    int m = 0;
    int n = 0;
    if (move == 'w') {
        m--;
    }
    else if (move == 's') {
        m++;
    }
    else if (move == 'a') {
        n--;
    }
    else if (move == 'd') {
        n++;
    }
    else if (move == 'z') {
        UndoMove(room, allMoves);
        return;
    }
    
    
    int rpos, cpos;
    LocatePerson(room, &rpos, &cpos);
    char x='0';
    if (room[rpos+m][cpos+n] != 1)  {
        
        if ((room[rpos+m][cpos+n] == 3 || room[rpos+m][cpos+n] == 4)  && room[rpos+2*m][cpos+2*n] != 0 &&  room[rpos+2*m][cpos+2*n] != 2) {
            return;
        }
        if (room[rpos+m][cpos+n] == 3 || room[rpos+m][cpos+n] == 4) {
            if (room[rpos+2*m][cpos+2*n] == 2) {
                room[rpos+2*m][cpos+2*n] = 4;
            }
            else{
            room[rpos+ 2*m][cpos+ 2*n] = 3;
            }
            x = '1';
        }
        if (room[rpos+m][cpos+n] == 2 || room[rpos+m][cpos+n] == 4) {
            room[rpos+m][cpos+n] = 6;
        }
        else {
            room[rpos+m][cpos+n] = 5; 
        }
        if (room[rpos][cpos] == 6) {
            room[rpos][cpos] = 2;
        }
        else {
            room[rpos][cpos] = 0;
        }
        int len = strlen(allMoves);
        allMoves[len] = move;
        allMoves[len + 1] = x; 
        allMoves[len + 2] = '\0'; 
    }
}

int CheckGameOver(int room[ROWS][COLS]) {
    int count = 0;
    for (int i = 0; i<ROWS; i++) {
        for (int j = 0; j<COLS; j++) {
            if (room[i][j] == 2 || room[i][j] == 6) {
                return 0;
            }
            if (room[i][j] == 4) {
                count++;
            }
            }
        }
    if (count != 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void TestMove(void)
{
char layout[] = "111111105321103001102301100201111111";
 char moves[100] = {0};
 int room[ROWS][COLS];
 InitialiseRoom(room, layout);
 PrintRoom(room);
 MakeMove(room, 's', moves);
 MakeMove(room, 'd', moves);
 MakeMove(room, 's', moves);
 PrintRoom(room);
 printf("Person moved: %s\n\n", moves);
 printf("Undo twice!\n");
 MakeMove(room, 'z', moves);
 MakeMove(room, 'z', moves);
 PrintRoom(room);
 printf("Person moved: %s\n\n", moves); 

} 

void TestInitialiseRoom(void)
{
 char layout[] = "1010100101010";
 int room[ROWS][COLS];
 InitialiseRoom(room, layout);
 PrintRoom(room);
} 

void TestGameOver(void)
{
 char layoutA[] = "111111105001103001100301100001111111";
 char layoutB[] = "111111100001100001104501100401111111";
 char layoutC[] = "111111100001100001136001100401111111";
 int roomA[ROWS][COLS];
 int roomB[ROWS][COLS];
 int roomC[ROWS][COLS];
 int gameOver;
 InitialiseRoom(roomA, layoutA);
 InitialiseRoom(roomB, layoutB);
 InitialiseRoom(roomC, layoutC);
 PrintRoom(roomA);
 PrintRoom(roomB);
 PrintRoom(roomC);
 gameOver = CheckGameOver(roomA);
 printf("Game A is over: %d\n", gameOver);
 gameOver = CheckGameOver(roomB);
 printf("Game B is over: %d\n", gameOver);
 gameOver = CheckGameOver(roomC);
 printf("Game C is over: %d\n", gameOver);
} 

void main(){
    TestMove();
}

