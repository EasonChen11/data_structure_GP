//finish read file function, enter record function, modify function, clear function, quit function, output file function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define minMatchSearch 5
#define filenameLong 20
#define max(a,b) a>b?a:b

typedef char dType;
enum appointment_book_item{
    titleName=1,content,all,showManu
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
void Modify(lead*leader);
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

void FreeTitleOfAppBook(title * titleFirstNode);

void FreeVocab(vocab * word);

int PrintEnterRecord(appBook * newAppBookNode);

void OutputFile(appBook *appointmentBook);

void SearchUserInput(appBook * keyPoint, appBook_item selectItem);

int StringCompare(vocab * originKey, vocab * inputData);

appBook_item SearchManu();

void RemoveChoiceAppBookNode(appBook ** keyPoint, int removeIndex);

title * CreateNewTitle();

void StorageVocabularyOfTitle(vocab ** vocabularyFirstChar, FILE * inputFile);

void ConnectTitleList(title ** firstTitle, title * newTitle);

appBook_item ModifyManu();

void ModifyUserNeedAppBook(appBook * modifyDataNode, appBook_item selectItem);

title * ModifyUserNeedTitleOrContent(title * firstTitle);

void VocabChange(vocab * modifyTitleName);

int PrintTitleWithIndexAndBackSize(title * pTitle);

//main program
int main(){
    AppointmentBook();
    return 0;
}
void AppointmentBook(void){
    lead * appointmentBook = ReadFromFile(); //rad the input file
    rewind(stdin);
    PrintAppBook(appointmentBook->listFirstNode, stdout);
    Menu(appointmentBook); //choose what to do next
}

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
                PrintAppBook(leader->listFirstNode,stdout);
                break;
            case 9:
                Quit(leader);
                quit = 1;
                break;
            default:
                printf("Please enter a choice 1-4 or 9 to quit\n");
        }
    }
}
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
}

//enter record
void EnterRecord(lead*leader){
    appBook * newAppBookNode = CreateNewAppBookNode(); //create a new node
    int runEnterRecord=1;
    while (runEnterRecord==1) {
        runEnterRecord=PrintEnterRecord(newAppBookNode); //print and scanf the data
    }
        ConnectAppBookList(&(leader->listFirstNode), newAppBookNode); //Link data entered to the list
        ++(leader->howMuchNodeInTheList);

}
 int PrintEnterRecord(appBook *newAppBookNode){ //ask user to enter the data
    printf("\nEnterRecord -- to enter the title and the content which you want to storage\n");
    printf("Please enter title :(ex. who,what,when,where......)\n");
    title *newTitle=CreateNewTitle();
    StorageVocabulary(&(newTitle->titleFirstChar),stdin);
    printf("Please enter any content of the title that you want to store :\n");
    StorageVocabulary(&(newTitle->titleStorageData),stdin);
    ConnectTitleList(&(newAppBookNode->firstTitle),newTitle);
    printf("enter more information?(1:Yes other:No) :");
    int choice;
    scanf("%d",&choice);
    getchar();
    return choice;
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
                                  inputCharacter);//must do it.Save the word in order to store each letter(of this word)to linked list
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

//create new structure
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
        if(outputFile==stdout)printf("#%d\n",index++);
        PrintAppBookOneData(appointmentBook->firstTitle, outputFile);
        putc('\n',outputFile);
        appointmentBook=appointmentBook->next;
    }
}
void PrintAppBookOneData(title * appointmentBookOneData, FILE * outputFile) {
    while(appointmentBookOneData!=NULL){
        PrintOneVocabulary(appointmentBookOneData->titleFirstChar, outputFile);
        putc(':',outputFile);
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

//modify
void Modify(lead* leader){//change one node data of the AppBook
    PrintAppBook(leader->listFirstNode,stdout);
    int modifyDataIndex;
    while (1){//choice node
        printf("Please enter which data to modify(index) --input 0 (to cancel modify operation) or the number(the data you want to modify):");
        scanf("%d",&modifyDataIndex);
        rewind(stdin);
        if(modifyDataIndex==0){ printf("rollback to menu\n"); return; }
        if(modifyDataIndex==-1) { Search(leader->listFirstNode); continue; }

        if(modifyDataIndex<=leader->howMuchNodeInTheList && modifyDataIndex>0)break;//index is legal
        printf("Over index.\nPlease enter again.\n");
    }
    appBook * modifyDataNode=leader->listFirstNode;
    while (--modifyDataIndex)modifyDataNode=modifyDataNode->next;//go to the index node
    appBook_item selectItem;
    while (1){//choice title, content, all
        selectItem= ModifyManu();
        if(selectItem>=titleName && selectItem<showManu)break;
        printf("choice 1~3\n");
    }
    ModifyUserNeedAppBook(modifyDataNode, selectItem);
}
appBook_item ModifyManu() {
    while (1){
        printf("********************************************************\n");
        printf("*             Which key you want to modify             *\n");
        printf("*------------------------------------------------------*\n");
        printf("*     1. title(who,what,when,ect)    2. content        *\n");
        printf("*     3. all                                           *\n");
        printf("********************************************************\n");
        printf("Please enter a choice:");
        int choice;
        scanf("%d",&choice);
        rewind(stdin);
        return choice;
    }
}
void ModifyUserNeedAppBook(appBook * modifyDataNode, appBook_item selectItem) {
    title *modifyTitle;
    switch (selectItem) {
        case all:
        case titleName:
            modifyTitle=ModifyUserNeedTitleOrContent(modifyDataNode->firstTitle);
            VocabChange(modifyTitle->titleFirstChar);
            if (selectItem==titleName)break;
        case content:
            modifyTitle=ModifyUserNeedTitleOrContent(modifyDataNode->firstTitle);
            VocabChange(modifyTitle->titleStorageData);
    }
}
title * ModifyUserNeedTitleOrContent(title * firstTitle) {
    title *nowTitle=firstTitle,*modifyTitle=firstTitle;
    int totalTitle,modifyTitleIndex;
    totalTitle=PrintTitleWithIndexAndBackSize(nowTitle);
    while (1){//choice which title to modify
        printf("Modify which title:");
        scanf("%d",&modifyTitleIndex);
        rewind(stdin);
        if(modifyTitleIndex<=totalTitle && modifyTitleIndex>0)break;//index is legal
        printf("Over index.\nPlease enter again.\n");
    }
    while (--modifyTitleIndex)modifyTitle=modifyTitle->nextTitle;//go to the index node
    return modifyTitle;
}
int PrintTitleWithIndexAndBackSize(title * pTitle) {
    int totalTitle=1;
    while (pTitle!=NULL){//show index and title
        printf("%d. ",totalTitle++);
        PrintOneVocabulary(pTitle->titleFirstChar,stdout);
        putchar(':');
        PrintOneVocabulary(pTitle->titleStorageData,stdout);
        putchar('\n');
        pTitle=pTitle->nextTitle;
    }
    return totalTitle-1;
}
void VocabChange(vocab * modifyTitleName) {
    vocab *userInputVocab=NULL,*beforeModifyTitleChar=modifyTitleName;//before storage before node
    printf("Please enter string for title you want to become:");
    StorageVocabulary(&userInputVocab,stdin);//user input
    while (userInputVocab != NULL){
        if(modifyTitleName!=NULL){
            modifyTitleName->word= userInputVocab->word;
        }else{
            StorageVocabularyChar(&(beforeModifyTitleChar),userInputVocab->word);
            modifyTitleName=beforeModifyTitleChar->nextWord;//go to next data which have been stored
        }
        beforeModifyTitleChar=modifyTitleName;
        modifyTitleName=modifyTitleName->nextWord;
        userInputVocab=userInputVocab->nextWord;
    }
    if(modifyTitleName!=NULL){
        FreeVocab(modifyTitleName);
        beforeModifyTitleChar->nextWord=NULL;//after free variable will carry itself located
    }
    FreeVocab(userInputVocab);//free memory of user input string which is stored by linked list
}

//free
void FreeLead(lead *leader){//free leader
    FreeAppBookList(leader->listFirstNode);
    free(leader);
}
void FreeAppBookList(appBook *listFirstNode){//free appBook's node
    if(listFirstNode==NULL){//check if it's the last node
        return;
    }
    FreeAppBookList(listFirstNode->next);
    FreeTitleOfAppBook(listFirstNode->firstTitle);
    free(listFirstNode);
}
void FreeTitleOfAppBook(title * titleFirstNode){//free who/what/when/where
    if(titleFirstNode==NULL)
        return;
    FreeTitleOfAppBook(titleFirstNode->nextTitle);
    FreeVocab(titleFirstNode->titleStorageData);
    FreeVocab(titleFirstNode->titleFirstChar);
    free(titleFirstNode);
}
void FreeVocab(vocab * word) {//free word's linked list
    if (word == NULL) {
        return;
    }
    FreeVocab(word->nextWord);
    free(word);
}

//quit
void Quit(lead*appBook){
    OutputFile(appBook->listFirstNode);//open a file to print final data
    FreeLead(appBook);//free data
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
void Search(appBook* firstNode){
    appBook_item selectItem;
    while (1){
        selectItem=SearchManu();
        if(selectItem==showManu) { printf("rollback\n"); return; }
        if(selectItem>=titleName && selectItem<showManu)break;
        else printf("choice 1~4\n");
    }
    SearchUserInput(firstNode,selectItem);
}
appBook_item SearchManu() {
    printf("**************************************\n");
    printf("*    Which key you want to search    *\n");
    printf("*    ----------------------------    *\n");
    printf("*     1. title        2. content     *\n");
    printf("*     3. all          4. back to menu*\n");
    printf("**************************************\n");
    printf("Please enter a choice:");
    int choice;
    scanf("%d",&choice);
    rewind(stdin);
    return choice;
}
void SearchUserInput(appBook * keyPoint, appBook_item selectItem) {
    vocab *userInputVocab=NULL;
    printf("Please enter string which you want to search:");
    StorageVocabulary(&userInputVocab,stdin);//user input

    int recordData=0,indexOfAppBook=1;
    while(keyPoint!=NULL){
        title *nowKeyPointTitle=keyPoint->firstTitle;
        int find=0;
        while(nowKeyPointTitle!=NULL) {
            if (selectItem != content)//selectItem==titleName && all
                find+=StringCompare(nowKeyPointTitle->titleFirstChar, userInputVocab);
            if (selectItem != titleName) //selectItem==content && all
                find+=StringCompare(nowKeyPointTitle->titleStorageData, userInputVocab);
            if(find){//if find
                recordData++;//find matching
                printf("#%d\n",indexOfAppBook);
                PrintAppBookOneData(keyPoint->firstTitle, stdout);
                putchar('\n');
                break;
            }
            find=0;
            nowKeyPointTitle=nowKeyPointTitle->nextTitle;
        }
        keyPoint=keyPoint->next;
        indexOfAppBook++;
    }
    FreeVocab(userInputVocab);//free memory of user input sting which use link list
    if(recordData==0)
        printf("could not find it\n");
    else
        printf("find %d matching information.\n",recordData);
}
int StringCompare(vocab*originKey, vocab*inputData)
{
    vocab *inputFirstChar=inputData;
    int matchSum=0,maxMatch=0;
    while( inputData != NULL && originKey!=NULL){
            if(originKey->word == inputData->word){
                originKey=originKey->nextWord;
                inputData=inputData->nextWord;
                matchSum++;
            }else {
                originKey = originKey->nextWord;
                maxMatch= max(maxMatch,matchSum);
                matchSum=0;
                inputData=inputFirstChar;
            }
        }
        if(inputData == NULL) {
            printf("Find all match data.\n");
            return 1;
        }else if(maxMatch>minMatchSearch){
            printf("The input string is compared from the beginning matching %d words.\n",maxMatch);
            return 1;
        }else return 0;
}

//delete
void Delete(lead* leader){
    printf("Your Appoint Book\n");
    PrintAppBook(leader->listFirstNode,stdout);
    printf("which data you want to remove (input index) or send -1 to cancel the delete operation:");
    int removeIndex;
    while(1) {
        scanf("%d", &removeIndex);
        if(removeIndex==-1)return; //back to menu
        if(removeIndex>0 && removeIndex<=leader->howMuchNodeInTheList)break; //delete the data you choose
        else printf("choice 1~%d\n",leader->howMuchNodeInTheList);
    }
    leader->howMuchNodeInTheList--;
    RemoveChoiceAppBookNode(&(leader->listFirstNode), removeIndex);
    printf("\nremove finish~\n");
}
void RemoveChoiceAppBookNode(appBook ** keyPoint, int removeIndex) {
    int index=1;
    appBook *frontNode,*nowNode=*(keyPoint);
    while (index++ < removeIndex) {//find the node you want to delete
        frontNode=nowNode;
        nowNode = nowNode->next;
    }
    if(removeIndex==1) *keyPoint=nowNode->next; //only have one data
    else frontNode->next=nowNode->next;
    FreeTitleOfAppBook(nowNode->firstTitle);
    free(nowNode);
}

