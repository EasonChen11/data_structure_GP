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
typedef struct appointment_book appBook;
typedef struct storage_character vocab;

void AppointmentBook(void);

int main(){
    AppointmentBook();
}

void AppointmentBook(void){

}