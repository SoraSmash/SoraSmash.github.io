#include "stdio.h"
#include <windows.h>
#include "time.h"
#include <string.h>
#include <conio.h>

#define DIM 4
#define MAXLEN 300

typedef struct record{
	char info[MAXCHAR];
	int time;
	struct record *next;
}*Record;

//gotoxy(int x, int y) allows to move the cursor of the terminal to the x y position
void gotoxy(int x, int y){
    COORD coor;
    HANDLE hOutput;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    coor.X = x;
    coor.Y = y;
    SetConsoleCursorPosition(hOutput,coor);
}

//mat_create(int mat[DIM][DIM]) generates the game matrix
void mat_create(int mat[DIM][DIM]){
	int i;
	int j;
	int c = 1;
	for(i = 0; i < DIM; i++){
		for(j = 0; j < DIM; j++){
			mat[i][j] = c;
			c++;
		}
	}
	mat[DIM-1][DIM-1] = 0;
}

//mat_print(int mat[DIM][DIM]) prints the game matrix
void mat_print(int mat[DIM][DIM]){
	int i;
	int j;
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,203,205,205,205,203,205,205,205,203,205,205,205,187);
	for(i = 0; i < DIM; i++){
		for(j = 0; j < DIM; j++){
			printf("%c",186);
			if(mat[i][j] == 0)
				printf("  ");
			else
				printf(" %d", mat[i][j]);
			if(mat[i][j] < 10)
				printf(" ");
			if(j == 3)
				printf("%c",186);
		}
		if(i!=3 && j!=3)
			printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",204,205,205,205,206,205,205,205,206,205,205,205,206,205,205,205,185);
		else
			printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,202,205,205,205,202,205,205,205,202,205,205,205,188);
	}
}

//move_number(int mat[DIM][DIM], char move) allows the player to make a move by pressing the w, a, s or d key
void move_number(int mat[DIM][DIM], char move){
	int i;
	int j;
	int ixy[4]={1,3,5,7};
	int jxy[4]={2,6,10,14};
	switch(move){
		case 'w':
			for(i = 0; i < DIM; i++){
				for(j = 0; j < DIM; j++){
					if(mat[i][j] == 0 && i != 3){
						mat[i][j] = mat[i+1][j];
						mat[i+1][j] = 0;
						gotoxy(jxy[j], ixy[i]);
						printf("%d",mat[i][j]);
						gotoxy(jxy[j], ixy[i+1]);
						printf("  ");
						i = DIM;
						j = DIM;
					}
				}
			}
			break;
		case 'a':
			for(i = 0; i < DIM; i++){
				for(j = 0; j < DIM; j++){
					if(mat[i][j] == 0 && j != 3){
						mat[i][j] = mat[i][j+1];
						mat[i][j+1] = 0;
						gotoxy(jxy[j], ixy[i]);
						printf("%d",mat[i][j]);
						gotoxy(jxy[j+1], ixy[i]);
						printf("  ");
						i = DIM;
						j = DIM;
					}
				}
			}
			break;
		case 's':
			for(i = 0; i < DIM; i++){
				for(j = 0; j < DIM; j++){
					if(mat[i][j] == 0 && i != 0){
						mat[i][j] = mat[i-1][j];
						mat[i-1][j] = 0;
						gotoxy(jxy[j], ixy[i]);
						printf("%d",mat[i][j]);
						gotoxy(jxy[j], ixy[i-1]);
						printf("  ");
						i = DIM;
						j = DIM;
					}
				}
			}
			break;
		case 'd':
			for(i = 0; i < DIM; i++){
				for(j = 0; j < DIM; j++){
					if(mat[i][j] == 0 && j != 0){
						mat[i][j] = mat[i][j-1];
						mat[i][j-1] = 0;
						gotoxy(jxy[j], ixy[i]);
						printf("%d",mat[i][j]);
						gotoxy(jxy[j-1], ixy[i]);
						printf("  ");
						i = DIM;
						j = DIM;
					}
				}
			}
			break;
	}
	gotoxy(0,10);
}

//mat_shuffle(int mat[DIM][DIM]) shuffles the game matrix
void mat_shuffle(int mat[DIM][DIM]){
	int r;
	int i;
	int c = 21;
	char move[DIM] = {'w', 'a', 's', 'd'};
	printf("Shuffling in progress\n");
	for(i = 0; i < 300; i++){
		r = rand()%4;
		move_number(mat,move[r]);
		Sleep(20);
		if(i%5 == 0){
			if(c == 21 || c == 22 || c == 23){
				gotoxy(c,9);
				printf(".");
				c++;
			}
			else{
				gotoxy(21,9);
				printf("   ");
				c = 21;
			}
		}
		gotoxy(24,9);
		printf("%d%%",i/3);
	}
	gotoxy(0,9);
	for(i = 0; i < 38; i++)
		printf(" ");
	gotoxy(0,9);
}

//start_game(int mat[DIM][DIM], int fmat[DIM][DIM]) explains the rules of the game and allows the player to start the game
void start_game(int mat[DIM][DIM], int fmat[DIM][DIM]){
	char start;
	mat_create(mat);
	mat_create(fmat);
	printf("15 Puzzle\n");
	printf("Rules:\n");
	printf("The game consists in ordering the numbers from 1 to 15 by moving the tiles to the empty position.\n");
	printf("The player will win when the game matrix is sorted like this:\n");
	mat_print(fmat);
	printf("Press any button to start the game\n");
	start = getch();
	system("cls");
	mat_print(mat);
}

//end_game(int mat[DIM][DIM], int fmat[DIM][DIM]) check if the player has won
int end_game(int mat[DIM][DIM], int fmat[DIM][DIM]){
	int i;
	int j;
	int f = 1;
	for(i = 0; i < DIM; i++){
		for(j = 0; j < DIM; j++){
			if(mat[i][j] != fmat[i][j])
				f = 0;
		}
	}
	return f;
}

//time_print(clock_t start, int* time_current) update the timer
void time_print(clock_t start, int* time_current){
	if((float)((clock()-start)/CLOCKS_PER_SEC) > *(time_current)){
		gotoxy(0,9);
		printf("Timer: %d",*(time_current));
		(*time_current)++;
		gotoxy(0,10);
	}
}

//record_save(char name[30], int new_record) save the new record in Record.txt
void record_save(char name[30], int new_record){
	char str[MAXLEN];
	char time[20];
	char *str_sup;
	int i;
	int j = 0;
	Record prev;
	Record temp;
	Record head;
	FILE* record = fopen("Record.txt","r");
	if(record){
		if(fgets(str, MAXCHAR, record) != NULL){
			temp = (Record)malloc(sizeof(struct record));
			strcpy(temp->info,str);
			temp->next = NULL;
			for(i = 0; i < strlen(str); i++){
				if(str[i] == ':'){
					i += 2;
					for(i; i < strlen(str); i++){
						time[j] = str[i];
						j++;
					}
				}
			}
			j = 0;
			temp->time = atoi(time);
			for(i = 0; i < 20; i++)
				time[i] = ' ';
		}
		head = temp;
		while (fgets(str, MAXCHAR, record) != NULL){
			Record r = (Record)malloc(sizeof(struct record));
			strcpy(r->info,str);
			r->next = NULL;
			for(i = 0; i < strlen(str); i++){
				if(str[i] == ':'){
					i += 2;
					for(i; i < strlen(str); i++){
						time[j] = str[i];
						j++;
					}
				}
			}
			j = 0;
			r->time = atoi(time);
			for(i = 0; i < 20; i++)
				time[i] = ' ';
			temp->next = r;
			temp = r;
		}
		temp = head;
		prev = head;
		i = 1;
		while(temp && temp->time <= new_record){
			prev = temp;
			temp = temp->next;
			i++;
		}
		Record r = (Record)malloc(sizeof(struct record));
		sprintf(r->info,"%d",i);
		strcat(r->info,") ");
		strcat(r->info,name);
		strcat(r->info,": ");
		sprintf(str,"%d",new_record);
		strcat(r->info,str);
		strcat(r->info,"\n");
		r->time = new_record;
		r->next = temp;
		if(i != 1)
			prev->next = r;
		else
			head = r;
		while(temp){
			i++;
			str_sup = strchr(temp->info,')');
			sprintf(str,"%d",i);
			strcat(str,str_sup);
			strcpy(temp->info,str);
			temp = temp->next;
		}
		temp = head;
		fclose(record);
		fopen("Record.txt","w");
		while(temp){
			fprintf(record,"%s",temp->info);
			temp = temp->next;
		}
		while(head){
			temp = head;
			head = head->next;
			free(temp);
		}
		fclose(record);
	}
	else{
		record = fopen("Record.txt","w");
		fprintf(record,"%s","1) ");
		fprintf(record,"%s",name);
		fprintf(record,"%s",": ");
		fprintf(record,"%d",new_record);
		fprintf(record,"%s","\n");
		fclose(record);
	}
}

//record_load() prints the list of records
void record_load(){
	char str[MAXLEN];
	FILE* record = fopen("Record.txt","r");
	printf("RECORD\n\n");
	while (fgets(str, MAXCHAR, record) != NULL)
    	printf("%s", str);
    fclose(record);
}

int main(){
	int mat[DIM][DIM];
	int fmat[DIM][DIM];
	char move;
	clock_t start;
	char name[30];
	int time_current = 0;
	int f = 0;
	srand(time(NULL));
	start_game(mat,fmat);
	mat_shuffle(mat);
	start = clock();
	time_print(start,&time_current);
	while(f == 0){
		move = ' ';
		if(kbhit())
			move = getch();
		move_number(mat,move);
		time_print(start,&time_current);
		f = end_game(mat,fmat);
	}
	time_current--;
	printf("Well done! You won!\nType your name:\n");
	scanf("%s",name);
	record_save(name,time_current);
	system("cls");
	record_load();
	move = getch();
	return 0;
}
