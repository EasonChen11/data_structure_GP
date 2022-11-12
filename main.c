#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fileapi.h>

#define filenameLong 20

typedef char dType;
enum appointment_book_item{
    who,what,when,where,repeat
}selectItem=who;
struct link_list_lead{
    int howMuchNodeInTheList;
    struct appointment_book *listFirstNode;
};
struct appointment_book{
    struct storage_character *who;
    struct storage_character *what;
    struct storage_character *when;
    struct storage_character *where;
    struct appointment_book *next;
};

struct storage_character{
    dType word;
    struct storage_character *nextWord;
};

typedef struct link_list_lead lead;
typedef struct appointment_book appBook;
typedef struct storage_character vocab;

void AppointmentBook(void);

lead * ReadFromFile(void);

lead * CreateNewLeadNode(void);

appBook * CreateNewAppBookNode(void);

vocab * CreateNewCharNode(void);

void ConnectVocabularyChar(vocab **, dType);

void ConnectAppBook(appBook **, appBook *);

int main(){
    AppointmentBook();
    return 0;
}

void AppointmentBook(void){
    lead * appBook = ReadFromFile();
}

lead * ReadFromFile(void){
    lead * newLead = CreateNewLeadNode();
    dType fileName[filenameLong],inputCharacter;
    printf("input file name:");//ask user open file name
    scanf("%s",fileName);
    FILE * inputFile = fopen(fileName,"r");//open file
    if(inputFile==NULL){
        printf("%s can't open\n",fileName);
        return newLead;
    }

    while ((inputCharacter = (dType)fgetc(inputFile))!=EOF){
        selectItem=who;//initial to who_item
        appBook * newDataNode = CreateNewAppBookNode();
        while (selectItem!=repeat) {
            vocab ** vocabularyFirstChar;
            switch (selectItem) {
                case who:vocabularyFirstChar=&(newDataNode->who);
                    ConnectVocabularyChar(vocabularyFirstChar, inputCharacter);
                    break;
                case what:vocabularyFirstChar=&(newDataNode->what);
                    break;
                case when:vocabularyFirstChar=&(newDataNode->when);
                    break;
                case where:vocabularyFirstChar=&(newDataNode->where);
                    break;
                default:
                    break;
            }
            while ( (inputCharacter= (dType)fgetc(inputFile)) != '\n' ) {
                ConnectVocabularyChar(vocabularyFirstChar, inputCharacter);
            }
            ++selectItem;//to next item
        }//one AppBook node

        ++(newLead->howMuchNodeInTheList);
        ConnectAppBook(&(newLead->listFirstNode), newDataNode);
    }
    fclose(inputFile);
    return newLead;
}

void ConnectAppBook(appBook ** firstNode, appBook * newData) {
    if((*firstNode)==NULL){
        (*firstNode)=newData;
        return;
    }
    appBook * nowAppBookNode=*firstNode;
    while(nowAppBookNode->next!=NULL) nowAppBookNode= nowAppBookNode->next;
    nowAppBookNode->next=newData;
}

void ConnectVocabularyChar(vocab ** vocabularyChar, dType character) {
    vocab * newChar = CreateNewCharNode();
    newChar->word=character;
    if((*vocabularyChar)==NULL){
        (*vocabularyChar)=newChar;
        return;
    }
    vocab * nowChar=*vocabularyChar;
    while(nowChar->nextWord!=NULL) nowChar= nowChar->nextWord;
    nowChar->nextWord=newChar;
}

vocab * CreateNewCharNode(void) {
    vocab *new_node = (vocab *) malloc(sizeof (vocab));
    new_node->word='\0';
    new_node->nextWord=NULL;
    return new_node;
}

appBook * CreateNewAppBookNode(void) {
    appBook *new_node = (appBook *) malloc(sizeof (appBook));
    new_node->who=NULL;
    new_node->when=NULL;
    new_node->what=NULL;
    new_node->where=NULL;
    new_node->next=NULL;
    return new_node;
}

lead * CreateNewLeadNode(void) {
    lead *new_node = (lead*) malloc(sizeof (lead));
    new_node->howMuchNodeInTheList=0;
    new_node->listFirstNode=NULL;
    return new_node;
}