#include <stdio.h>
#include <stdlib.h>

struct PairNode{
    int key;
    int value;
    struct PairNode *next;
};
struct HashNode{
    int index;
    struct PairNode *pair;
    struct HashNode *next;
};

void PrintMenu();
void PrintHashFunction();
void PrintCollisionHandling();
void PrintHashTable();

struct PairNode *CreateNewPairNode(int key, int value);
struct HashNode *CreateNewHashNode(int index);
struct HashNode *GetHashNodeAtIndex(int index);

int MidSquare(int key, int tableSize);
int Division(int key, int tableSize);
int Folding(int key, int tableSize);
int DigitExtraction(int key, int tableSize);
int Rotation(int key, int tableSize);

int LinearProbing(int index, int key, int value);
void Chaining(int index, int key, int value);
void Rehashing(int index, int key, int value);

int i = 0;
int hashTableSize = 0;
struct HashNode *hashTable = NULL;
struct HashNode *hashTableTail = NULL;

int main(){
    // Create initial hash table
    printf("Initial hash table size : ");
    scanf("%d", &hashTableSize);
    for(i = 0; i < hashTableSize; i++){
        if(hashTable == NULL){
            hashTable = CreateNewHashNode(i);
            hashTableTail = hashTable;
        }
        else{
            struct HashNode *newHashNode = CreateNewHashNode(i);
            hashTableTail->next = newHashNode;
            hashTableTail = newHashNode;
        }
    }
    printf("\n\n\n");

    // Run menu loop
    int isRunning = 1;
    while(isRunning){
        PrintMenu();
        int choiceInput = 0;
        printf("Choice : ");
        scanf("%d", &choiceInput);
        printf("\n");
        switch(choiceInput){
            // Input new key-value
            case(1):{
                PrintHashFunction();
                int hashFunctionChoice = 0;
                printf("Choice : ");
                scanf("%d", &hashFunctionChoice);
                PrintCollisionHandling();
                int collisionHandlingChoice = 0;
                printf("Choice : ");
                scanf("%d", &collisionHandlingChoice);
                printf("==================Input data=================\n");
                int keyInput = 0;
                printf("Key : ");
                scanf("%d", &keyInput);
                int valueInput = 0;
                printf("Value : ");
                scanf("%d", &valueInput);
                int index = 0;
                switch(hashFunctionChoice){
                    case(1):{
                        index = MidSquare(keyInput, hashTableSize);
                        index = Division(index, hashTableSize);
                        break;
                    }
                    case(2):{
                        index = Division(keyInput, hashTableSize);
                        break;
                    }
                    case(3):{
                        index = Folding(keyInput, hashTableSize);
                        index = Division(index, hashTableSize);
                        break;
                    }
                    case(4):{
                        index = DigitExtraction(keyInput, hashTableSize);
                        index = Division(index, hashTableSize);
                        break;
                    }
                    case(5):{
                        index = Rotation(keyInput, hashTableSize);
                        index = Division(index, hashTableSize);
                        break;
                    }
                }
                switch(collisionHandlingChoice){
                    case(1):{
                        int isDataInsertSuccess = LinearProbing(index, keyInput, valueInput);
                        if(isDataInsertSuccess){
                            printf("\n#### Data insert success! ####\n");
                        }
                        else{
                            printf("\n#### ERROR: Data insert failed! Hash table full! ####\n");
                        }
                        break;
                    }
                    case(2):{
                        Chaining(index, keyInput, valueInput);
                        printf("\n#### Data insert success! ####\n");
                        break;
                    }
                    case(3):{
                        Rehashing(index, keyInput, valueInput);
                        printf("\n#### Data insert success! ####\n");
                        break;
                    }
                }
                break;
            }
            // Print hash table
            case(2):{
                printf("==================Hash Tabel=================\n");
            	PrintHashTable();
                break;
            }
            // Exit the loop
            case(3):{
                isRunning = 0;
                break;
            }
        }
        printf("\n\n\n\n\n");
    }
}

void PrintMenu(){
    printf("=====================Menu====================\n");
    printf("1. Insert new value\n");
    printf("2. Show hash table\n");
    printf("3. Exit\n");
}
void PrintHashFunction(){
    printf("=============Choose Hash Funtion=============\n");
    printf("1. Mid Square\n");
    printf("2. Division\n");
    printf("3. Folding\n");
    printf("4. Digit Extraction\n");
    printf("5. Rotation\n");
}
void PrintCollisionHandling(){
    printf("==========Choose Collision Handling==========\n");
    printf("1. Linear Probing\n");
    printf("2. Chaining\n");
    printf("3. Rehashing\n");
}

void PrintHashTable(){
    struct HashNode *iterateNode = hashTable;
    while(iterateNode != NULL){
        if(iterateNode->pair != NULL){
            printf("Index %d :", iterateNode->index);
            struct PairNode *iteratePairNode = iterateNode->pair;
            while(iteratePairNode != NULL){
                printf(" (Key %d | Value %d)", iteratePairNode->key, iteratePairNode->value);
                iteratePairNode = iteratePairNode->next;
            }
            printf("\n");
        }
        else{
            printf("Index %d : Empty\n", iterateNode->index);
        }
        iterateNode = iterateNode->next;
    }
}

struct PairNode *CreateNewPairNode(int key, int value){
    struct PairNode *newNode = (struct PairNode *)malloc(sizeof(struct PairNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}
struct HashNode *CreateNewHashNode(int index){
    struct HashNode *newNode = (struct HashNode *)malloc(sizeof(struct HashNode));
    newNode->index = index;
    newNode->pair = NULL;
    newNode->next = NULL;
    return newNode;
}
struct HashNode *GetHashNodeAtIndex(int index){
    struct HashNode *iterateNode = hashTable;
    while(iterateNode != NULL){
        if(iterateNode->index == index){
            return iterateNode;
        }
        else{
            iterateNode = iterateNode->next;
        }
    }
    return NULL;
}

int MidSquare(int key, int tableSize){
    long long squaredKey = key * key;
    int keyZeros = 0;
    int currentKey = key;
    while(currentKey > 0){
        currentKey /= 10;
        keyZeros++;
    }
    int squaredKeyZeros = 0;
    int currentSquaredKey = squaredKey;
    while(currentSquaredKey > 0){
        currentSquaredKey /= 10;
        squaredKeyZeros++;
    }
    int eraseAmount = (squaredKeyZeros - keyZeros) / 2;
    for(i = 0; i < eraseAmount; i++){
        squaredKey /= 10;
    }
    int newKey = 0;
    int newKeyDivider = 1;
    for(i = 0; i < keyZeros; i++){
        int extractedDigit = squaredKey % 10;
        squaredKey /= 10;
        newKey += extractedDigit * newKeyDivider;
        newKeyDivider *= 10;
    }
    return newKey;
}

int Division(int key, int tableSize){
    return key % tableSize;
}
int Folding(int key, int tableSize){
    int divider = 1;
    int currentTableSize = tableSize;
    while(currentTableSize >= 10){
        currentTableSize /= 10;
        divider *= 10;
    }
    int sum = 0;
    int currentKey = key;
    int currentDivider = divider;
    while(currentKey > 0){
        int extractedNumber = currentKey % currentDivider;
        sum += extractedNumber;
        currentKey /= divider;
    }
    return sum;
}
int DigitExtraction(int key, int tableSize){
    int tableSizeZeros = 0;
    int currentTableSize = tableSize;
    while(currentTableSize > 0){
        currentTableSize /= 10;
        tableSizeZeros++;
    }
    int newKey = 0;
    int newKeyDivider = 1;
    for(i = 0; i < tableSizeZeros; i++){
        int extractedDigit = key % 10;
        key /= 100;
        newKey += extractedDigit * newKeyDivider;
        newKeyDivider *= 10;
        if(key == 0){
            break;
        }
    }
    return newKey;
}
int Rotation(int key, int tableSize){
    int newKey = key;
    int keyDivider = 1;
    while(key >= 10){
        key /= 10;
        keyDivider *= 10;
    }
    while(tableSize > 0){
        int rotatedDigit = newKey % 10;
        newKey /= 10;
        rotatedDigit *= keyDivider;
        newKey += rotatedDigit;
        tableSize /= 10;
    }
    return newKey;
}

int LinearProbing(int index, int key, int value){
    struct HashNode *currentHashNode = GetHashNodeAtIndex(index);
    if(currentHashNode->pair == NULL){
        currentHashNode->pair = CreateNewPairNode(key, value);
        return 1;
    }
    else{
        struct HashNode *iterateNode = currentHashNode;
        do{
            iterateNode = iterateNode->next;
            if(iterateNode == NULL){
                iterateNode = hashTable;
            }
            if(iterateNode->pair == NULL){
                iterateNode->pair = CreateNewPairNode(key, value);
                return 1;
            }
        }while(iterateNode != currentHashNode);
        return 0;
    }
}
void Chaining(int index, int key, int value){
    struct HashNode *currentHashNode = GetHashNodeAtIndex(index);
    if(currentHashNode->pair == NULL){
        currentHashNode->pair = CreateNewPairNode(key, value);
    }
    else{
        struct PairNode *iterateNode = currentHashNode->pair;
        while(iterateNode->next != NULL){
            iterateNode = iterateNode->next;
        }
        iterateNode->next = CreateNewPairNode(key, value);
    }
}
void Rehashing(int index, int key, int value){
    struct HashNode *currentHashNode = GetHashNodeAtIndex(index);
    if(currentHashNode->pair == NULL){
        currentHashNode->pair = CreateNewPairNode(key, value);
    }
    else{
        if(hashTableSize == 0){
            struct HashNode *newHashNode = CreateNewHashNode(hashTableSize);
            hashTable = newHashNode;
            hashTableTail = hashTable;
        }
        else{
            struct HashNode *newHashNode = CreateNewHashNode(hashTableSize);
            hashTableTail->next = newHashNode;
            hashTableTail = newHashNode;
            hashTableSize++;
            newHashNode->pair = CreateNewPairNode(key, value);
        }
    }
}
