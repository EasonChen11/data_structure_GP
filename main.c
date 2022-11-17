#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define filenameLong 20

typedef char dType;
enum appointment_book_item{
    who,what,when,where,repeat
};

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

void StorageAppBookInformation(appBook *, FILE *);

void StorageVocabulary(vocab **, FILE *);

void PrintAppBook(appBook *);

void PrintAppBookOneData(appBook *);

void PrintOneVocabulary(vocab *);

void PrintEnterRecord(appBook*);

int main(){
    AppointmentBook();
    return 0;
}

void AppointmentBook(void){
    lead * appointmentBook = ReadFromFile();
    rewind(stdin);
    EnterRecord(appointmentBook);
    PrintAppBook(appointmentBook->listFirstNode);
    //Menu();
}


/*void Menu(lead*leader) {
    int quit = 0;
    while ( !quit ) {
        int choice = ChoiceMenu();  // get a choice
        switch (choice) { // process according to the choice
            case 1:
                EnterRecord(leader);
                break;
            case 2:
                ViewDay(leader);
                break;
            case 3:
                ViewWeek(leader);
                break;
            case 4:
                Modify(leader);
                break;
            case 5:
                Delete(leader);
                break;
            case 6: // Search(leader, count);
                printf("Search --- record at %d\n", Search(appBook));
                break;
            case 9:
                Quit(leader);
                quit = 1;
                break;
            default:
                printf("Please enter a choice 1-6 or 9 to quit\n");
        }
    }
}*/

void EnterRecord(lead*leader){

    appBook *newAppBookNode=CreateNewAppBookNode();
    PrintEnterRecord(newAppBookNode);

    ConnectAppBookList(&(leader->listFirstNode), newAppBookNode);

}
 void PrintEnterRecord(appBook*newAppBookNode){


    printf("\nEnterRecord -- to enter the who/what/when/where\n");
    printf("Please enter WHOM you have an appointment with:");
    StorageVocabulary(&(newAppBookNode->who),stdin);
    printf("Please enter WHAT the event is: ");
    StorageVocabulary(&(newAppBookNode->what),stdin);
    printf("Please enter WHEN (yymmddhhmm): ");
    StorageVocabulary(&(newAppBookNode->when),stdin);
    printf("Please enter WHERE you have an appointment at: ");
    StorageVocabulary(&(newAppBookNode->where),stdin);

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
        appBook * newDataNode = CreateNewAppBookNode();//create a new appoint_book which isn't connect to the list
        ConnectVocabularyChar(&(newDataNode->who), inputCharacter);//must do it.Because this word is gotten avoid lost this word.
        StorageAppBookInformation(newDataNode, inputFile);//one AppBook node
        ++(newLead->howMuchNodeInTheList);
        ConnectAppBookList(&(newLead->listFirstNode), newDataNode);//let created node link to lead node
    }
    fclose(inputFile);
    return newLead;
}

void StorageAppBookInformation(appBook * AppBookData, FILE * inputFile) {
    enum appointment_book_item selectItem=who;
    vocab ** vocabularyFirstChar;
    while (selectItem!=repeat) {//who->what->when->where finish one appoint_book node
        switch (selectItem) {
            case who:vocabularyFirstChar=&(AppBookData->who);
                break;
            case what:vocabularyFirstChar=&(AppBookData->what);
                break;
            case when:vocabularyFirstChar=&(AppBookData->when);
                break;
            case where:vocabularyFirstChar=&(AppBookData->where);
                break;
            default:
                break;
        }
        StorageVocabulary(vocabularyFirstChar,inputFile);
        ++selectItem;//to next item
    }//one AppBook node
}

void StorageVocabulary(vocab ** vocabularyFirstChar, FILE * inputFile) {
    dType inputCharacter;
    while ( (inputCharacter= (dType)fgetc(inputFile)) != '\n' ) {//until at the string least
        ConnectVocabularyChar(vocabularyFirstChar, inputCharacter);
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

void PrintAppBook(appBook * appointmentBook) {
    int index=1;
    while (appointmentBook!=NULL){
        printf("%d:\n",index++);
        PrintAppBookOneData(appointmentBook);
        putchar('\n');
        appointmentBook=appointmentBook->next;
    }
}

void PrintAppBookOneData(appBook * appointmentBookOneData) {
    printf("Who:");
    PrintOneVocabulary(appointmentBookOneData->who);
    printf("What:");
    PrintOneVocabulary(appointmentBookOneData->what);
    printf("When:");
    PrintOneVocabulary(appointmentBookOneData->when);
    printf("Where:");
    PrintOneVocabulary(appointmentBookOneData->where);
}

void PrintOneVocabulary(vocab * character) {
    while (character!=NULL){
        putchar(character->word);
        character=character->nextWord;
    }
    putchar('\n');
}

void Modify(lead* leader){//change the AppBook one node data
    int modifyDataIndex;
    while (1){
        printf("Modify which data?");
        scanf("%d",&modifyDataIndex);
        if(modifyDataIndex<=leader->howMuchNodeInTheList)break;//index is legal
        printf("Over index.\nPlease enter again.\n");
    }
    appBook * modifyDataNode=leader->listFirstNode;
    while (--modifyDataIndex)modifyDataNode=modifyDataNode->next;//go to the index node
    PrintEnterRecord(modifyDataNode);
}
