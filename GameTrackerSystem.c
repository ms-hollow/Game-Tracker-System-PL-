#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#define MAX 256
#define KEY 29 // encryption key

typedef struct game{

  char gamename[31], genre[20], release_date[15], upcoming_parts[50];
  char DLC[31], developer[31], status[30];
  int playtime;

} GAME;

typedef struct list{

  GAME records;
  struct node* next;

} LIST;

LIST *head;
char statusChoices[][50] = {"Currently Playing", "Planning to Play Next", "Planning to Replay", "Completed", "Not Played", "Stopped Playing", "Unreleased"};
int chars[MAX];
int code, size =0;

void makenull(){
  head = NULL;
}

void add(GAME info){

  LIST *prev, *curr, *newnode;
  prev=curr=head;
  newnode = (GAME*)(malloc(sizeof(GAME)));
  newnode->records = info;

  while(prev!=NULL && strcmp(prev->records.gamename, info.gamename)){
    curr = prev;
    prev = prev->next;
  }

  if(head==prev){
    head = newnode;
  }
  else{
    curr->next = newnode;
  }
  newnode->next = prev;
}

void del(char g[31]){

  LIST *prev, *curr;
  prev=curr=head;

  if(prev==NULL){
    printf("\nError Record Not Found.");
  }

  while(prev!=NULL && strcmp(prev->records.gamename,g)!=0){
    curr=prev;
    prev=prev->next;
  }
  if(head==prev){
    head=prev->next;
  }
  else{
    curr->next=prev->next;
    free(prev);
  }
  printf("\nRecord Successfully Deleted.");
}

void update(char g[31]){

    LIST *prev, *curr;

    if(head==NULL){
      printf("\nError Record Not Found.");
      return;
    }

    prev = NULL;
    curr = head;

    while(curr!=NULL && strcmp(curr->records.gamename,g)!=0){
      prev = curr;
      curr = curr->next;
    }

    if(curr==NULL){
      printf("\nError Record Not Found.");
      return;
    }

    int ch;

    printf("[1] GAME NAME\n");
    printf("[2] GAME GENRE\n");
    printf("[3] GAME RELEASE DATE\n");
    printf("[4] UPCOMING PARTS\n");
    printf("[5] DLC\n");
    printf("[6] DEVELOPER\n");
    printf("[7] STATUS\n");
    printf("[8] PLAYTIME\n");
    printf("SELECT THE NUMBER YOU WANT TO UPDATE: ");
    scanf("%d", &ch);

    switch(ch){
      case 1: system("cls");
              printf("Enter New Game Name: ");
              scanf(" %[^\n]", curr->records.gamename);
              break;
      case 2: system("cls");
              printf("Enter New Game Genre: ");
              scanf(" %[^\n]", curr->records.genre);
              break;
      case 3: system("cls");
              printf("Enter New Release Date: ");
              scanf(" %[^\n]", curr->records.release_date);
              break;
      case 4: system("cls");
              printf("Enter New Upcoming Parts: ");
              scanf(" %[^\n]", curr->records.upcoming_parts);
              break;
      case 5: system("cls");
              printf("Enter New DLC: ");
              scanf(" %[^\n]", curr->records.DLC);
              break;
      case 6: system("cls");
              printf("Enter New Developer: ");
              scanf(" %[^\n]", curr->records.developer);
              break;
      case 7: system("cls");
              printf("Please Select A Number To Change Status: \n");
              int choice;
                for (int i = 0; i < 7; i++) {
                    printf("%d. %s\n", i+1, statusChoices[i]);
                }
                printf("Enter the number of your choice: ");
                scanf("%d", &choice);
                    if (choice >= 1 && choice <= 7) {
                        strcpy(curr->records.status, statusChoices[choice-1]); // Copy the selected name into p1.name
                        printf("You selected %s\n", curr->records.status);
                    }
                    else {
                        printf("Invalid choice\n");
                    }
                break;
      case 8: system("cls");
              printf("Enter New Play Time: ");
              scanf("%d", curr->records.playtime);
              break;
    }
    printf("Record Successfully Updated.\n");
}

int menu(){
  int op;
  system("cls");
  printf("GAME TRACKER SYSTEM\n\n");
  printf("1. Add Record\n");
  printf("2. Update Record\n");
  printf("3. Delete Record\n");
  printf("4. Display Record\n");
  printf("5. Exit\n");
  printf("Select (1-5): ");
  scanf("%d",&op);
  return(op);
}

void display(){

  LIST *prev;
  prev = head;
  int i=1;

  printf("GAME TRACKER SYSTEM\n\n");

  while(prev!=NULL){
    printf("=======================================\n");
    printf("RECORD ENTRY: %d\n\n",i++);
    printf("Game Name: %s\n", prev->records.gamename);
    printf("Genre: %s\n", prev->records.genre);
    printf("Release Date: %s\n", prev->records.release_date);
    printf("Upcoming Parts: %s\n", prev->records.upcoming_parts);
    printf("DLC: %s\n", prev->records.DLC);
    printf("Developer: %s\n", prev->records.developer);
    printf("Status: %s\n", prev->records.status);
    printf("Play Time: %d hr(s)\n", prev->records.playtime);
    printf("=======================================\n");
    prev = prev->next;
  }
}


void encrypt(char* text) {
    for (int i = 0; i < strlen(text); i++) {
        text[i] += KEY;
    }
}

void decrypt(char* text) {
    for (int i = 0; i < strlen(text); i++) {
        text[i] -= KEY;
    }
}

void save() {
    FILE* fp = fopen("GTSystem_record.txt", "wb");
    if (fp == NULL) {
        printf("Error: File Does Not Exist.\n");
        return;
    }
    GAME g;
    LIST* prev = head;
    while (prev != NULL) {
        g = prev->records;
        encrypt(g.gamename);
        encrypt(g.genre);
        encrypt(g.release_date);
        encrypt(g.upcoming_parts);
        encrypt(g.DLC);
        encrypt(g.developer);
        encrypt(g.status);
        fwrite(&g, sizeof(GAME), 1, fp);
        decrypt(g.gamename);
        decrypt(g.genre);
        decrypt(g.release_date);
        decrypt(g.upcoming_parts);
        decrypt(g.DLC);
        decrypt(g.developer);
        decrypt(g.status);
        prev = prev->next;
    }
    printf("Record Successfully Saved!\n");
    fclose(fp);
}

void retrieve() {
    FILE* fp = fopen("GTSystem_record.txt", "rb");
    if (fp == NULL) {
        printf("Error: File Does Not Exist.\n");
        return;
    }
    GAME g;
    while (fread(&g, sizeof(GAME), 1, fp) == 1) {
        decrypt(g.gamename);
        decrypt(g.genre);
        decrypt(g.release_date);
        decrypt(g.upcoming_parts);
        decrypt(g.DLC);
        decrypt(g.developer);
        decrypt(g.status);
        add(g);
    }
    fclose(fp);
}

int main(){

  GAME op;
  makenull();
  retrieve();
  while(1){
        switch(menu()){
            case 1: system("cls");
                    printf("GAME INFORMATION\n\n");
                    printf("Enter Game Name: ");  scanf(" %[^\n]", op.gamename);
                    printf("Enter Game Genre: ");  scanf(" %[^\n]", op.genre);
                    printf("Enter Game Release Date: "); scanf(" %[^\n]", op.release_date);
                    printf("Enter Upcoming Parts: ");  scanf(" %[^\n]", op.upcoming_parts);
                    printf("Enter Game DLC: ");  scanf(" %[^\n]", op.DLC);
                    printf("Enter Game Developer: "); scanf(" %[^\n]", op.developer);
                    printf("Enter Game Status: \n");
                    int choice;
                    for (int i = 0; i < 7; i++) {
                        printf("%d. %s\n", i+1, statusChoices[i]);
                    }
                    printf("Enter the number of your choice: ");
                    scanf("%d", &choice);
                        if (choice >= 1 && choice <= 7) {
                            strcpy(op.status, statusChoices[choice-1]); // Copy the selected name into p1.name
                            printf("You selected %s\n", op.status);
                        }
                        else {
                            printf("Invalid choice\n");
                        }
                    printf("Enter Game Play Time: ");
                    scanf("%d", &op.playtime);
                    add(op); break;
            case 2: system("cls"); printf("UPDATE RECORD\n"); printf("Enter Name: "); scanf(" %[^\n]", op.gamename); update(op.gamename); system("pause"); break;
            case 3: system("cls"); printf("DELETE RECORD\n"); printf("Enter Name: "); scanf(" %[^\n]", op.gamename); del(op.gamename); break;
            case 4: system("cls"); display(); system("pause"); break;
            case 5: save(); exit(0);
        }
    }
}

