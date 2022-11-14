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
    struct storage_individual_character *who;
    struct storage_individual_character *when;
    struct storage_individual_character *what;
    struct storage_individual_character *where;
    struct appointment_book *next;
};

struct storage_individual_character{
    struct storage_character *first;
    struct storage_individual_character *nextIndividualCharacter;
};

struct storage_character{
    char word;
    struct character_node *nextWord;
};

void AppointmentBook(void);

int main(){
    AppointmentBook();
}

void AppointmentBook(void){

}