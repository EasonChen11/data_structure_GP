#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fileapi.h>

#define fileLong 20
enum appointment_book_item{
    who,when,what,where,repeat
};
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

lead * ReadFromFile(void);

lead * CreateNewLeadNode(void);

appBook * CreateNewDataNode();

int main(){
    AppointmentBook();
}

void AppointmentBook(void){
    lead * appBook = ReadFromFile();
}

lead * ReadFromFile(void){
    char fileName[fileLong],inputCharacter;
    printf("input file name:");
    scanf("%s",fileName);
    FILE * inputFile = fopen(fileName,"r");
    if(inputFile==NULL){
        printf("%s can't open\n",fileName);
        return NULL;
    }
    lead * newLead = CreateNewLeadNode();
    appBook * firstDataNode=NULL;
    enum appointment_book_item selectItem = who;
    while (1){
        inputCharacter = getchar();
        if (inputCharacter == EOF) break;
        appBook * newDataNode = CreateNewDataNode();
        if(!firstDataNode) firstDataNode=newDataNode;
        while(inputCharacter!='\n'){

        }

    }
    fclose(inputFile);
    newLead->listFirstNode=firstDataNode;
    return newLead;
}

appBook * CreateNewDataNode() {
    appBook *new_node = (appBook *) malloc(sizeof (appBook));
    new_node->who=NULL;
    new_node->when=NULL;
    new_node->what=NULL;
    new_node->where=NULL;
    return new_node;
}

lead * CreateNewLeadNode() {
    lead *new_node = (lead*) malloc(sizeof (lead));
    new_node->howMuchNodeInTheList=0;
    new_node->listFirstNode=NULL;
    return new_node;
}