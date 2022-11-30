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

typedef enum appointment_book_item appBook_item;
typedef struct link_list_lead lead;
typedef struct appointment_book appBook;
typedef struct storage_character vocab;

void AppointmentBook(void);
int ChoiceMenu();
void Menu(lead*leader);
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

void FreeLead(lead *leader);

void FreeAppBookList(appBook *listFirstNode);

void FreeAppBook(appBook *listFirstNode);

void FreeVocab(vocab * word);

void PrintEnterRecord(appBook*);

void OutputFile(appBook *appointmentBook);

void FprintOneVocabulary(FILE* fp,vocab * character);

void SearchName(appBook*);

int StringCompare(vocab*,vocab*);

vocab ** SelectADifferentRecordItem(appBook * keyPoint, appBook_item bookItem);

int main(){
    AppointmentBook();
    return 0;
}

void AppointmentBook(void){
    lead * appointmentBook = ReadFromFile(); //rad the input file
    PrintAppBook(appointmentBook->listFirstNode);
    rewind(stdin);
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
                //Delete(leader);
                break;
            case 4:
                SearchName(leader->listFirstNode);

                //Search(leader);
                //printf("Search --- record at %d\n", Search(leader));
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

void EnterRecord(lead*leader){

    appBook *newAppBookNode=CreateNewAppBookNode(); //create a new node
    PrintEnterRecord(newAppBookNode); //print and scanf the data

    ConnectAppBookList(&(leader->listFirstNode), newAppBookNode); //Link data entered to the list
    ++(leader->howMuchNodeInTheList);
}

 void PrintEnterRecord(appBook*newAppBookNode){ //ask user to enter the data


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
    appBook_item selectItem=who;
    vocab ** vocabularyFirstChar;
    while (selectItem!=repeat) {//who->what->when->where finish one appoint_book node
        vocabularyFirstChar=SelectADifferentRecordItem(AppBookData,selectItem++);//to next Item
        StorageVocabulary(vocabularyFirstChar,inputFile);
        ++selectItem;//to next item
    }//one AppBook node
}

vocab ** SelectADifferentRecordItem(appBook * keyPoint, appBook_item bookItem) {
    switch (bookItem) {
        case who:   return &(keyPoint->who);
        case what:  return &(keyPoint->who);
        case when:  return &(keyPoint->who);
        case where: return &(keyPoint->who);
        default:    return NULL;
    }
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
    rewind(stdin);
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
        rewind(stdin);
        if(modifyDataIndex<=leader->howMuchNodeInTheList && modifyDataIndex>0)break;//index is legal
        printf("Over index.\nPlease enter again.\n");
    }
    appBook * modifyDataNode=leader->listFirstNode;
    while (--modifyDataIndex)modifyDataNode=modifyDataNode->next;//go to the index node
    FreeAppBook(modifyDataNode);//clear modify node data
    PrintEnterRecord(modifyDataNode);//read new input information
}

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
}

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

    while (appointmentBook!=NULL){//print until the last node
        //print who,what,when,where
        FprintOneVocabulary(fp,appointmentBook->who);
        FprintOneVocabulary(fp,appointmentBook->what);
        FprintOneVocabulary(fp,appointmentBook->when);
        FprintOneVocabulary(fp,appointmentBook->where);
        appointmentBook=appointmentBook->next;
    }
    fclose(fp);
}
void FprintOneVocabulary(FILE* fp,vocab * character) {//print string on output file
    while (character!=NULL){
        fprintf(fp,"%c",character->word);
        character=character->nextWord;
    }
    fprintf(fp,"\n");
}

void SearchInformationOfUserInput(appBook * keyPoint, appBook_item selectItem) {
    vocab *userInputVocab=NULL;
    printf("Please enter string which you want to search:");
    rewind(stdin);
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
}
