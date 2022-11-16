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
int ChoiceMenu();
void Menu();
void EnterRecord(lead*appBook);
void ViewDay(lead*appBook);
void ViewWeek(lead*appBook);
void Modify(lead*appBook);
void Delete(lead*appBook);
int Search(lead*appBook);
void Quit(lead*appBook);

lead * ReadFromFile(void);

lead * CreateNewLeadNode(void);

appBook * CreateNewAppBookNode(void);

vocab * CreateNewCharNode(void);

void ConnectVocabularyChar(vocab **, dType);

void ConnectAppBookList(appBook **, appBook *);

int main(){
    AppointmentBook();
    return 0;
}

void AppointmentBook(void){
    lead * appBook = ReadFromFile();
    Menu();
}

void Menu(lead*appBook) {
    int quit = 0;
    while ( !quit ) {
        int choice = ChoiceMenu();  // get a choice
        switch (choice) { // process according to the choice
            case 1:
                EnterRecord(appBook);
                break;
            case 2:
                ViewDay(appBook);
                break;
            case 3:
                ViewWeek(appBook);
                break;
            case 4:
                Modify(appBook);
                break;
            case 5:
                Delete(appBook);
                break;
            case 6: // Search(appBook, count);
                printf("Search --- record at %d\n", Search(appBook));
                break;
            case 9:
                Quit(appBook);
                quit = 1;
                break;
            default:
                printf("Please enter a choice 1-6 or 9 to quit\n");
        }
    }
}

lead * ReadFromFile(void){
    lead * newLead = CreateNewLeadNode();
    dType fileName[filenameLong],inputCharacter;
    printf("input file name:");//ask user open file name
    scanf("%s",fileName);
    FILE * inputFile = fopen(fileName,"r");//open file
    if(inputFile==NULL){//check file can open
        printf("%s can't open\n",fileName);
        return newLead;
    }

    while ((inputCharacter = (dType)fgetc(inputFile))!=EOF){//check whether read end of file
        selectItem=who;//initial to who_item
        appBook * newDataNode = CreateNewAppBookNode();//create a new appoint_book which isn't connect to the list
        while (selectItem!=repeat) {//who->what->when->where finish one appoint_book node
            vocab ** vocabularyFirstChar;
            switch (selectItem) {
                case who:vocabularyFirstChar=&(newDataNode->who);
                    ConnectVocabularyChar(vocabularyFirstChar, inputCharacter);//must do it.Because this word is gotten avoid lost this word.
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
            while ( (inputCharacter= (dType)fgetc(inputFile)) != '\n' ) {//until at the string least
                ConnectVocabularyChar(vocabularyFirstChar, inputCharacter);
            }
            ++selectItem;//to next item
        }//one AppBook node

        ++(newLead->howMuchNodeInTheList);
        ConnectAppBookList(&(newLead->listFirstNode), newDataNode);//let created node link to lead node
    }
    fclose(inputFile);
    return newLead;
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

void ConnectAppBookList(appBook ** firstNode, appBook * newData) {
    if((*firstNode)==NULL){//first is NULL
        (*firstNode)=newData;
        return;
    }
    appBook * nowAppBookNode=*firstNode;
    while(nowAppBookNode->next!=NULL) nowAppBookNode= nowAppBookNode->next;//find the least node
    nowAppBookNode->next=newData;
}

void ConnectVocabularyChar(vocab ** vocabularyChar, dType character) {
    vocab * newChar = CreateNewCharNode();//create a node save the character
    newChar->word=character;
    if((*vocabularyChar)==NULL){//first is NULL
        (*vocabularyChar)=newChar;
        return;
    }
    vocab * nowChar=*vocabularyChar;
    while(nowChar->nextWord!=NULL) nowChar= nowChar->nextWord;//find the least node
    nowChar->nextWord=newChar;
}

vocab * CreateNewCharNode(void) {//initial CharNode data
    vocab *new_node = (vocab *) malloc(sizeof (vocab));
    new_node->word='\0';
    new_node->nextWord=NULL;
    return new_node;
}

appBook * CreateNewAppBookNode(void) {//initial AppBook data
    appBook *new_node = (appBook *) malloc(sizeof (appBook));
    new_node->who=NULL;
    new_node->when=NULL;
    new_node->what=NULL;
    new_node->where=NULL;
    new_node->next=NULL;
    return new_node;
}

lead * CreateNewLeadNode(void) {//initial Lead node data
    lead *new_node = (lead*) malloc(sizeof (lead));
    new_node->howMuchNodeInTheList=0;
    new_node->listFirstNode=NULL;
    return new_node;
}