#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Type{
    NONE,
    OPERATOR,
    NUMBER,
}type;
struct OperatorNode{
    char operator;
    struct OperatorNode *next;
};

void InfixToPostfix(char inputString[], char newString[]);
void InfixToPrefix(char inputString[], char newString[]);

int CanCheckingStringBeProcessed(type currentCheckingType, char currentChar);
type GetType(char charInput);
int GetOperatorPriority(char operator);

struct OperatorNode *CreateNewOperatorNode(char operator);
void PushOperator(char operator);
char PopOperator();

int i = 0;
struct OperatorNode *operatorStackHead = NULL;
struct OperatorNode *operatorStackTail = NULL;

int main(){
    char infixString[101];
    scanf("%[^\n]", infixString);
    getchar();
    char postfixString[strlen(infixString) * 2 + 1];
    char prefixString[strlen(infixString) * 2 + 1];
    strcpy(postfixString, "");
    strcpy(prefixString, "");
    InfixToPostfix(infixString, postfixString);
    InfixToPrefix(infixString, prefixString);
    printf("Postfix :\n%s\n", postfixString);
    printf("Prefix :\n%s\n", prefixString);
}

void InfixToPostfix(char inputString[], char newString[]){
    int inputStringLength = strlen(inputString);
    type checkingType = NONE;
    char checkingString[inputStringLength + 1];
    strcpy(checkingString, "");
    for(i = 0; i < inputStringLength + 1; i++){
        // Check the final checking string
        if(i == inputStringLength){
            if(checkingType == OPERATOR){
                char currentOperator = checkingString[0];
                if(currentOperator == '('){
                    PushOperator(currentOperator);
                }
                else if(currentOperator == ')'){
                    while(operatorStackHead != NULL){
                        char popedOperator = PopOperator();
                        if(popedOperator == '('){
                            break;
                        }
                        else{
                            char operatorString[2] = " ";
                            operatorString[0] = popedOperator;
                            strcat(newString, operatorString);
                            strcat(newString, " ");
                        }
                    }
                    strcat(newString, ") ");
                }
                else{
                    while(operatorStackHead != NULL){
                        if(GetOperatorPriority(operatorStackHead->operator) >= GetOperatorPriority(currentOperator)){
                            char popedOperator = PopOperator();
                            char operatorString[2] = " ";
                            operatorString[0] = popedOperator;
                            strcat(newString, operatorString);
                            strcat(newString, " ");
                        }
                        else{
                            break;
                        }
                    }
                    PushOperator(currentOperator);
                }
            }
            else if(checkingType == NUMBER){
                strcat(newString, checkingString);
                strcat(newString, " ");
            }
        }
        // If char is space / empty
        if(inputString[i] == ' '){
            continue;
        }
        // Process the first char
        else if(checkingType == NONE){
            checkingType = GetType(inputString[i]);
            char singleInputString[2] = " ";
            singleInputString[0] = inputString[i];
            strcat(checkingString, singleInputString);
        }
        // Process the checking string
        else if(CanCheckingStringBeProcessed(checkingType, inputString[i])){
            // If char is an operator
            if(checkingType == OPERATOR){
                char currentOperator = checkingString[0];
                // If operator is open bracket
                if(currentOperator == '('){
                    PushOperator(currentOperator);
                }
                // If operator is close bracket
                else if(currentOperator == ')'){
                    while(operatorStackHead != NULL){
                        char popedOperator = PopOperator();
                        if(popedOperator == '('){
                            break;
                        }
                        else{
                            char operatorString[2] = " ";
                            operatorString[0] = popedOperator;
                            strcat(newString, operatorString);
                            strcat(newString, " ");
                        }
                    }
                }
                // If operator is neither above
                else{
                    while(operatorStackHead != NULL){
                        if(GetOperatorPriority(operatorStackHead->operator) >= GetOperatorPriority(currentOperator)){
                            char popedOperator = PopOperator();
                            char operatorString[2] = " ";
                            operatorString[0] = popedOperator;
                            strcat(newString, operatorString);
                            strcat(newString, " ");
                        }
                        else{
                            break;
                        }
                    }
                    PushOperator(currentOperator);
                }
            }
            // If char is an number
            else if(checkingType == NUMBER){
                strcat(newString, checkingString);
                strcat(newString, " ");
            }
            strcpy(checkingString, "");
            checkingType = GetType(inputString[i]);
            char singleInputString[2] = " ";
            singleInputString[0] = inputString[i];
            strcat(checkingString, singleInputString);
        }
        // Add char to checking string
        else{
            char singleInputString[2] = " ";
            singleInputString[0] = inputString[i];
            strcat(checkingString, singleInputString);
        }
    }
    while(operatorStackHead != NULL){
        char operatorString[2] = " ";
        operatorString[0] = PopOperator();
        strcat(newString, operatorString);
        strcat(newString, " ");
    }
}
void InfixToPrefix(char inputString[], char newString[]){
    int inputStringLength = strlen(inputString);
    strrev(inputString);
    type checkingType = NONE;
    char checkingString[inputStringLength + 1];
    strcpy(checkingString, "");
    for(i = 0; i < inputStringLength + 1; i++){
        // Check the final checking string
        if(i == inputStringLength){
            if(checkingType == OPERATOR){
                char currentOperator = checkingString[0];
                if(currentOperator == '('){
                    PushOperator(currentOperator);
                }
                else if(currentOperator == ')'){
                    while(operatorStackHead != NULL){
                        char popedOperator = PopOperator();
                        if(popedOperator == '('){
                            break;
                        }
                        else{
                            char operatorString[2] = " ";
                            operatorString[0] = popedOperator;
                            strcat(newString, operatorString);
                            strcat(newString, " ");
                        }
                    }
                    strcat(newString, ") ");
                }
                else{
                    while(operatorStackHead != NULL){
                        if(GetOperatorPriority(operatorStackHead->operator) >= GetOperatorPriority(currentOperator)){
                            char popedOperator = PopOperator();
                            char operatorString[2] = " ";
                            operatorString[0] = popedOperator;
                            strcat(newString, operatorString);
                            strcat(newString, " ");
                        }
                        else{
                            break;
                        }
                    }
                    PushOperator(currentOperator);
                }
            }
            else if(checkingType == NUMBER){
                strcat(newString, checkingString);
                strcat(newString, " ");
            }
        }
        // If char is space / empty
        if(inputString[i] == ' '){
            continue;
        }
        // Process the first char
        else if(checkingType == NONE){
            checkingType = GetType(inputString[i]);
            char singleInputString[2] = " ";
            singleInputString[0] = inputString[i];
            strcat(checkingString, singleInputString);
        }
        // Process the checking string
        else if(CanCheckingStringBeProcessed(checkingType, inputString[i])){
            // If char is an operator
            if(checkingType == OPERATOR){
                char currentOperator = checkingString[0];
                // If operator is open bracket
                if(currentOperator == ')'){
                    PushOperator(currentOperator);
                }
                // If operator is close bracket
                else if(currentOperator == '('){
                    while(operatorStackHead != NULL){
                        char popedOperator = PopOperator();
                        if(popedOperator == ')'){
                            break;
                        }
                        else{
                            char operatorString[2] = " ";
                            operatorString[0] = popedOperator;
                            strcat(newString, operatorString);
                            strcat(newString, " ");
                        }
                    }
                }
                // If operator is neither above
                else{
                    while(operatorStackHead != NULL){
                        if(GetOperatorPriority(operatorStackHead->operator) > GetOperatorPriority(currentOperator)){
                            char popedOperator = PopOperator();
                            char operatorString[2] = " ";
                            operatorString[0] = popedOperator;
                            strcat(newString, operatorString);
                            strcat(newString, " ");
                        }
                        else{
                            break;
                        }
                    }
                    PushOperator(currentOperator);
                }
            }
            // If char is an number
            else if(checkingType == NUMBER){
                strcat(newString, checkingString);
                strcat(newString, " ");
            }
            strcpy(checkingString, "");
            checkingType = GetType(inputString[i]);
            char singleInputString[2] = " ";
            singleInputString[0] = inputString[i];
            strcat(checkingString, singleInputString);
        }
        // Add char to checking string
        else{
            char singleInputString[2] = " ";
            singleInputString[0] = inputString[i];
            strcat(checkingString, singleInputString);
        }
    }
    while(operatorStackHead != NULL){
        char operatorString[2] = " ";
        operatorString[0] = PopOperator();
        strcat(newString, operatorString);
        strcat(newString, " ");
    }
    int newStringLenght = strlen(newString);
    newString[newStringLenght - 1] = newString[newStringLenght];
    strrev(newString);
}

int CanCheckingStringBeProcessed(type currentCheckingType, char currentChar){
    if(currentCheckingType == OPERATOR && GetType(currentChar) == OPERATOR){
        return 1;
    }
    else if(currentCheckingType != GetType(currentChar)){
        return 1;
    }
    else{
        return 0;
    }
}
type GetType(char charInput){
    if(charInput == '+' || charInput == '-' || charInput == '*'){
        return OPERATOR;
    }
    if(charInput == '/' || charInput == '^' || charInput == '%'){
        return OPERATOR;
    }
    else if(charInput == '(' || charInput == ')'){
        return OPERATOR;
    }
    else{
        return NUMBER;
    }
}
int GetOperatorPriority(char operator){
    int returnPriority = 0;
    switch(operator){
        case('+'):{
            returnPriority = 1;
            break;
        }
        case('-'):{
            returnPriority = 1;
            break;
        }
        case('*'):{
            returnPriority = 2;
            break;
        }
        case('/'):{
            returnPriority = 2;
            break;
        }
        case('%'):{
            returnPriority = 2;
            break;
        }
        case('^'):{
            returnPriority = 3;
            break;
        }
        case('('):{
            returnPriority = 0;
            break;
        }
        case(')'):{
            returnPriority = 0;
            break;
        }
    }
    return returnPriority;
}

struct OperatorNode *CreateNewOperatorNode(char operator){
    struct OperatorNode *newNode = (struct OperatorNode *)malloc(sizeof(struct OperatorNode));
    newNode->operator = operator;
    newNode->next = NULL;
    return newNode;
}
void PushOperator(char operator){
    struct OperatorNode *newNode = CreateNewOperatorNode(operator);
    newNode->next = operatorStackHead;
    operatorStackHead = newNode;
    if(operatorStackTail == NULL){
        operatorStackTail = newNode;
    }
}
char PopOperator(){
    char returnOperator;
    struct OperatorNode *deleteNode = operatorStackHead;
    if(operatorStackHead == NULL){
        return ' ';
    }
    else if(operatorStackHead == operatorStackTail){
        returnOperator = operatorStackHead->operator;
        operatorStackHead = NULL;
        operatorStackTail = NULL;
        free(deleteNode);
    }
    else{
        returnOperator = deleteNode->operator;
        operatorStackHead = deleteNode->next;
        free(deleteNode);
    }
    return returnOperator;
}

/*
4 + 6 * (5 - 2) / 3
*/
/*
Postfix :
4 6 5 2 - * 3 / +
Prefix :
+ 4 / * 6 - 5 2 3
*/
