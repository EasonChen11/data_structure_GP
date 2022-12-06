//finish read file function, enter record function, modify function, clear function, quit function, output file function

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
    struct lab_title *firstTitle;
    struct appointment_book *next;
};
struct lab_title{
    struct storage_character *titleFirstChar;
    struct storage_character *titleStorageData;
    struct lab_title *nextTitle;
};
struct storage_character{
    dType word;
    struct storage_character *nextWord;
};

typedef enum appointment_book_item appBook_item;
typedef struct link_list_lead lead;
typedef struct appointment_book appBook;
typedef struct lab_title title;
typedef struct storage_character vocab;

void AppointmentBook(void);
int ChoiceMenu();
void Menu(lead*leader);
void EnterRecord(lead*appBook);
void ViewDay(lead*appBook);
void ViewWeek(lead*appBook);
void Modify(lead*appBook);
void Delete(lead*appBook);
void Search(appBook * firstNode);
void Quit(lead*appBook);

lead * ReadFromFile(void);

lead * CreateNewLeadNode(void);

appBook * CreateNewAppBookNode(void);

vocab * CreateNewCharNode(void);

void StorageVocabularyChar(vocab ** vocabularyChar, dType inputChar);

void ConnectAppBookList(appBook **, appBook *);


void StorageVocabulary(vocab ** vocabularyFirstChar, FILE * inputFile);

void PrintAppBook(appBook * appointmentBook, FILE * outputFile);

void PrintAppBookOneData(title * appointmentBookOneData, FILE * outputFile);

void PrintOneVocabulary(vocab * character, FILE * outputFile);

void FreeLead(lead *leader);

void FreeAppBookList(appBook *listFirstNode);

void FreeAppBook(appBook *listFirstNode);

void FreeVocab(vocab * word);

void PrintEnterRecord(appBook*);

void OutputFile(appBook *appointmentBook);

void SearchUserInput(appBook * keyPoint, appBook_item selectItem);

int StringCompare(vocab*,vocab*);

appBook_item SearchManu();

void RemoveChoiceAppBookNode(appBook ** keyPoint, int removeIndex);

title * CreateNewTitle();

void StorageVocabularyOfTitle(vocab ** vocabularyFirstChar, FILE * inputFile);

void ConnectTitleList(title ** firstTitle, title * newTitle);

//main program
int main(){
    AppointmentBook();
    return 0;
}
void AppointmentBook(void){
    lead * appointmentBook = ReadFromFile(); //rad the input file
    PrintAppBook(appointmentBook->listFirstNode, stdout);
    rewind(stdin);
    EnterRecord(appointmentBook);
    PrintAppBook(appointmentBook->listFirstNode, stdout);
    Quit(appointmentBook);
    //Menu(appointmentBook); //choose what to do next
}

/*
void Menu(lead*leader) {
    int quit = 0;
    while ( !quit ) {
        int choice = ChoiceMenu();  // get a choice
        switch (choice) { // process according to the choice
            case 1:
                EnterRecord(leader);
                break;
            case 2:
                Modify(leader);
                break;
            case 3:
                Delete(leader);
                break;
            case 4:
                Search(leader->listFirstNode);
                break;
            case 5:
                PrintAppBook(leader->listFirstNode);
                break;
            case 9:
                Quit(leader);
                quit = 1;
                break;
            default:
                printf("Please enter a choice 1-4 or 9 to quit\n");
        }
    }
}*/

//enter record
void EnterRecord(lead*leader){

    appBook *newAppBookNode=CreateNewAppBookNode(); //create a new node
    PrintEnterRecord(newAppBookNode); //print and scanf the data

    ConnectAppBookList(&(leader->listFirstNode), newAppBookNode); //Link data entered to the list
    ++(leader->howMuchNodeInTheList);
}
 void PrintEnterRecord(appBook *newAppBookNode){ //ask user to enter the data
    printf("\nEnterRecord -- to enter the title and the thing which you wont to storage\n");
    printf("Please enter title :");
    title *newTitle=CreateNewTitle();
    StorageVocabulary(&(newTitle->titleFirstChar),stdin);
     StorageVocabularyChar(&(newTitle->titleFirstChar),':');
    printf("Please enter the thing which you wont to storage :");
    StorageVocabulary(&(newTitle->titleStorageData),stdin);
    ConnectTitleList(&(newAppBookNode->firstTitle),newTitle);
 }

 //read file
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

    while ((inputCharacter = (dType)fgetc(inputFile))!=EOF){//avoid file is empty
        appBook * newDataNode = CreateNewAppBookNode();//create a new appoint_book which isn't connect to the list

        do  {//title read \n  or EOF cancel
            title * newTitle=CreateNewTitle();
            StorageVocabularyChar(&(newTitle->titleFirstChar),
                                  inputCharacter);//must do it.Because this word is gotten avoid lost this word.
            StorageVocabularyOfTitle(&(newTitle->titleFirstChar),inputFile);
            StorageVocabulary(&(newTitle->titleStorageData),inputFile);
            ConnectTitleList(&(newDataNode->firstTitle),newTitle);
            inputCharacter = (dType)fgetc(inputFile);
        }while(inputCharacter!='\n' && inputCharacter!=EOF);//the end of one node or end of file
        ++(newLead->howMuchNodeInTheList);
        ConnectAppBookList(&(newLead->listFirstNode), newDataNode);//let created node link to lead node
    }
    fclose(inputFile);
    return newLead;
}

//link the data together
void ConnectTitleList(title ** firstTitle, title * newTitle) {
    if((*firstTitle)==NULL){//first is NULL
        (*firstTitle)=newTitle;
        return;
    }
    title * nowTitleNode=*firstTitle;
    while(nowTitleNode->nextTitle!=NULL) nowTitleNode= nowTitleNode->nextTitle;//find the least node
    nowTitleNode->nextTitle=newTitle;
}
void StorageVocabularyOfTitle(vocab ** vocabularyFirstChar, FILE * inputFile) {
    dType inputCharacter;
    while ( (inputCharacter= (dType)fgetc(inputFile)) != ':' ) {//until at the string least
        StorageVocabularyChar(vocabularyFirstChar, inputCharacter);
    }
    StorageVocabularyChar(vocabularyFirstChar, inputCharacter);
}
void StorageVocabulary(vocab ** vocabularyFirstChar, FILE * inputFile) {
    dType inputCharacter;
    while ( (inputCharacter= (dType)fgetc(inputFile)) != '\n' ) {//until at the string least
        StorageVocabularyChar(vocabularyFirstChar, inputCharacter);
    }
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
void StorageVocabularyChar(vocab ** vocabularyChar, dType inputChar) {
    vocab * newChar = CreateNewCharNode();//create a node save the character
    newChar->word=inputChar;
    if((*vocabularyChar)==NULL){//first is NULL
        (*vocabularyChar)=newChar;
        return;
    }
    vocab * nowChar=*vocabularyChar;
    while(nowChar->nextWord!=NULL) nowChar= nowChar->nextWord;//find the least node
    nowChar->nextWord=newChar;
}

//create new node
vocab * CreateNewCharNode(void) {//initial CharNode data
    vocab *new_node = (vocab *) malloc(sizeof (vocab));
    new_node->word='\0';
    new_node->nextWord=NULL;
    return new_node;
}
title * CreateNewTitle() {
    title *newTile=(title*) malloc(sizeof (title));
    newTile->titleFirstChar=NULL;
    newTile->titleStorageData=NULL;
    newTile->nextTitle=NULL;
    return newTile;
}
appBook * CreateNewAppBookNode(void) {//initial AppBook data
    appBook *new_node = (appBook *) malloc(sizeof (appBook));
    new_node->firstTitle=NULL;
    new_node->next=NULL;
    return new_node;
}
lead * CreateNewLeadNode(void) {//initial Lead node data
    lead *new_node = (lead*) malloc(sizeof (lead));
    new_node->howMuchNodeInTheList=0;
    new_node->listFirstNode=NULL;
    return new_node;
}

//print function
void PrintAppBook(appBook * appointmentBook, FILE * outputFile)
{
    if(appointmentBook==NULL){
        printf("appoint book is empty\n");
        return;
    }
    int index=1;
    while (appointmentBook!=NULL){
        if(outputFile==stdout)printf("%d:\n",index++);
        PrintAppBookOneData(appointmentBook->firstTitle, outputFile);
        putc('\n',outputFile);
        appointmentBook=appointmentBook->next;
    }
}
void PrintAppBookOneData(title * appointmentBookOneData, FILE * outputFile) {
    while(appointmentBookOneData!=NULL){
        PrintOneVocabulary(appointmentBookOneData->titleFirstChar, outputFile);
        PrintOneVocabulary(appointmentBookOneData->titleStorageData, outputFile);
        putc('\n',outputFile);
        appointmentBookOneData=appointmentBookOneData->nextTitle;
    }
}
void PrintOneVocabulary(vocab * character, FILE * outputFile) {
    while (character!=NULL){
        putc(character->word,outputFile);
        character=character->nextWord;
    }
}

/*
int ChoiceMenu(){
    printf("*************************************\n");
    printf("*      Appointment Book Services    *\n");
    printf("*      -------------------------    *\n");
    printf("*   1. Enter Record     3. Delete   *\n");
    printf("*   2. Modify           4. Search   *\n");
    printf("*   5. Print Appoint Book           *\n");
    printf("*   9. Quit                         *\n");
    printf("*************************************\n");
    printf("Please enter a choice:");
    int choice;
    scanf("%d",&choice);
    rewind(stdin);
    return choice;
}*/

//modify
/*
void Modify(lead* leader){//change the AppBook one node data
    int modifyDataIndex;
    while (1){
        printf("Modify which data(index) or send -1 to cancel modify operation:");
        scanf("%d",&modifyDataIndex);
        rewind(stdin);
        if(modifyDataIndex==-1){ printf("rollback to manu\n"); return; }
        if(modifyDataIndex<=leader->howMuchNodeInTheList && modifyDataIndex>0)break;//index is legal
        printf("Over index.\nPlease enter again.\n");
    }
    appBook * modifyDataNode=leader->listFirstNode;
    while (--modifyDataIndex)modifyDataNode=modifyDataNode->next;//go to the index node
    FreeAppBook(modifyDataNode);//clear modify node data
    PrintEnterRecord(modifyDataNode);//read new input information
}*/

//free
/*
void FreeLead(lead *leader){//free leader
    FreeAppBookList(leader->listFirstNode);
    free(leader);
}

void FreeAppBookList(appBook *listFirstNode){//free appBook's node
    if(listFirstNode==NULL){//check if it's the last node
        return;
    }
        FreeAppBookList(listFirstNode->next);
        FreeAppBook(listFirstNode);
        free(listFirstNode);

}

void FreeAppBook(appBook *listFirstNode){//free who/what/when/where
    FreeVocab(listFirstNode->who);
    listFirstNode->who=NULL;
    FreeVocab(listFirstNode->what);
    listFirstNode->what=NULL;
    FreeVocab(listFirstNode->when);
    listFirstNode->when=NULL;
    FreeVocab(listFirstNode->where);
    listFirstNode->where=NULL;
}

void FreeVocab(vocab * word) {//free word's linked list
    if (word == NULL) {
        return;
    }
    FreeVocab(word->nextWord);
    free(word);
}*/

//quit
void Quit(lead*appBook){
    OutputFile(appBook->listFirstNode);//open a file to print final data
    //FreeLead(appBook);//free data
}
void OutputFile(appBook *appointmentBook){
    dType fileName[filenameLong];
    //output filename
    printf("Please enter an output file:");
    scanf("%s",fileName);
    FILE*fp=fopen(fileName,"w");
    PrintAppBook(appointmentBook,fp);
    fclose(fp);
}


//search
/*
void Search(appBook* firstNode){
    appBook_item selectItem;
    while (1){
        selectItem=SearchManu();
        if(selectItem==repeat) { printf("rollback to manu\n"); return; }
        if(selectItem>=who && selectItem<repeat)break;
        else printf("choice 1~4\n");
    }
    SearchUserInput(firstNode,selectItem);
}

appBook_item SearchManu() {
    printf("**************************************\n");
    printf("*    Which key you want to search    *\n");
    printf("*    ----------------------------    *\n");
    printf("*     1. who           3. when       *\n");
    printf("*     2. what          4. where      *\n");
    printf("*     5. show manu                   *\n");
    printf("**************************************\n");
    printf("Please enter a choice:");
    int choice;
    scanf("%d",&choice);
    rewind(stdin);
    return choice-1;
}

void SearchUserInput(appBook * keyPoint, appBook_item selectItem) {
    vocab *userInputVocab=NULL;
    printf("Please enter string which you want to search:");
    StorageVocabulary(&userInputVocab,stdin);
    int recordData=0;
    while(keyPoint!=NULL){
            if(StringCompare(*SelectADifferentRecordItem(keyPoint,selectItem),userInputVocab)){
                printf("%d:\n",++recordData);
                PrintAppBookOneData(keyPoint);
                putchar('\n');
            }
                keyPoint=keyPoint->next;
    }
    FreeVocab(userInputVocab);//free memory of user input sting which use link list
    if(recordData==0)
        printf("could not find it\n");
}

int StringCompare(vocab*key,vocab*inputData)
{
    while(key!=NULL && inputData!=NULL){
            if(key->word==inputData->word){
                key=key->nextWord;
                inputData=inputData->nextWord;
            }
            else break;
        }
        if(key==NULL && inputData==NULL)
            return 1;
        else return 0;
}*/

//delete
/*
void Delete(lead* leader){
    printf("Your Appoint Book\n");
    PrintAppBook(leader->listFirstNode);
    printf("which data you wont to remove (input index) or send -1 to cancel the delete operation:");
    int removeIndex;
    while(1) {
        scanf("%d", &removeIndex);
        if(removeIndex==-1)return;
        if(removeIndex>0 && removeIndex<=leader->howMuchNodeInTheList)break;
        else printf("choice 1~%d\n",leader->howMuchNodeInTheList);
    }
    leader->howMuchNodeInTheList--;
    RemoveChoiceAppBookNode(&(leader->listFirstNode), removeIndex);
    printf("\nremove finish~\n");
}

void RemoveChoiceAppBookNode(appBook ** keyPoint, int removeIndex) {
    int index=1;
    appBook *frontNode,*nowNode=*(keyPoint);
    while (index++ < removeIndex) {
        frontNode=nowNode;
        nowNode = nowNode->next;
    }
    if(removeIndex==1) *keyPoint=nowNode->next;
    else frontNode->next=nowNode->next;
    FreeAppBook(nowNode);
    free(nowNode);
}
*/