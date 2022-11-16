#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fileapi.h>

struct link_list_lead{
    int howMuchNodeInTheList;
    struct appointment_book *listFirstNode;
};
struct appointment_book{
    struct storage_character *who;
    struct storage_character *when;
    struct storage_character *what;
    struct storage_character *where;
    struct appointment_book *next;
};

struct storage_character{
    char word;
    struct storage_character *nextWord;
};

typedef struct link_list_lead lead;
typedef struct appointment_book app_book;
typedef struct storage_character vocab;

void AppointmentBook(void);
int ChoiceMenu();
void Menu();
void EnterRecord(lead*appBook);
void ViewDay(lead*appBook);
void ViewWeek(lead*appBook);
void Modify(lead*appBook);
void Delete(lead*appBook);
void Search(lead*appBook);
void Quit(lead*appBook);

int main(){

}

void Menu(lead*appBook){
    int quit=0;
    while (!quit) {
        int choice =ChoiceMenu() ;  // get a choice
        switch (choice) { // process according to the choice
            case 1: EnterRecord(appBook);
                    break;
            case 2: ViewDay(appBook);
                    break;
            case 3: ViewWeek(appBook);
                    break;
            case 4: Modify(appBook);
                    break;
            case 5: Delete(appBook);
                    break;
            case 6: // Search(appBook, count);
                    printf("Search --- record at %d\n",Search(appBook));
                    break;
            case 9: Quit(appBook);
                    quit = 1;
                    break;
            default: printf("Please enter a choice 1-6 or 9 to quit\n");
        }
    }



}

int ChoiceMenu(){
    printf("***************************************\n");
    printf("*      Appointment Book Services      *\n");
    printf("*      -------------------------      *\n");
    printf("*   1. Enter Record       4. Modify   *\n");
    printf("*   2. View Day           5. Delete   *\n");
    printf("*   3. View Week          6. Search   *\n");
    printf("*   9. Quit                           *\n");
    printf("***************************************\n");
    printf("\nPlease enter a choice:");
    int choice;
    scanf("%d",&choice);
    return choice;
}
