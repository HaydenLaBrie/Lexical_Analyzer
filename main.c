//Hayden Labrie
//hcl180001
//Lexical Analyzer as defined in assignment tokens
//Maps lexemes to tokens
//Mapping is displayed as Lexeme -> Token
#include <stdio.h>
int isReserved(char* ptr, char* reserved){ //0 is false and 1 is true for bool
    int i = 0;
    while (ptr[i] != '\0') {
        if (ptr[i] == reserved[i]) {
            i++;
        } else
            return 0;
    }
    if(reserved[i] != '\0')
        return 0;
    return 1;
}
int isTAGS(char* ptr){
    char* arr = "TAGS";
    return isReserved(ptr, arr);
}
int isBEGIN(char* ptr){
    char* arr = "BEGIN";
    return isReserved(ptr, arr);
}

int isSEQUENCE(char* ptr){
    char* arr = "SEQUENCE";
    return isReserved(ptr, arr);
}
int isINTEGER(char* ptr){
    char* arr = "INTEGER";
    return isReserved(ptr, arr);
}
int isDATE(char* ptr){
    char* arr = "DATE";
    return isReserved(ptr, arr);
}
int isEND(char* ptr){
    char* arr = "END";
    return isReserved(ptr, arr);
}
int isTypeReference(char* ptr){ //0 is false and 1 is true
    int i = 0;
    int previous = -1; //Used to check if char before was a hyphen
    //No need to instantiate a letter counter due to if statement of capital letter guaranteeing at least 1
    if(ptr[i] >= 'A' && ptr[i] <= 'Z'){ //If first char is (A-Z)
        i++; // go to second char in array
        while(ptr[i] != '\0'){ //While char array is not at the null terminator
            if(ptr[i] >= '0' && ptr[i] <= '9'){ //If array at position i is (0-9) then true

            }
            else if(ptr[i] == '-'){ //If array at position i is hyphen (-) then true
                previous = i - 1;
                if(ptr[previous] == '-'){ //If the previous char was a hyphen then -- exists which is against the definition
                  return 0; //Make false
                }
            }
            else if(ptr[i] >= 'A' && ptr[i] <= 'z'){ //If A-Z or a-z then true
                //Do nothing and continue to next char
            }
            else{
                return 0;
            }
            i++; //go to next char
        }
    }
    else{
        return 0; //If ptr[0] != then return 0 for false
    }
    i--; //to check for last position and see if it was a hyphen
    if(ptr[i] == '-'){ //If there are no digits or hyphens in array then true
        return 0;
    }
    //Artificial else statement
    return 1; //If the loop holds the whole time through the if statements then return 1 for true
}
int isIdentifier(char* ptr){ //0 is false and 1 is true
    int i = 0;
    int previous = -1; //Used to check if char before was a hyphen
    //No need to instantiate a letter counter due to if statement of capital letter guaranteeing at least 1
    if(ptr[i] >= 'a' && ptr[i] <= 'z'){ //If first char is (a-z)
        i++; // go to second char in array
        while(ptr[i] != '\0'){ //While char array is not at the null terminator
            if(ptr[i] >= '0' && ptr[i] <= '9'){ //If array at position i is (0-9) then true

            }
            else if(ptr[i] == '-'){ //If array at position i is hyphen (-) then true
                previous = i - 1;
                if(ptr[previous] == '-'){ //If the previous char was a hyphen then -- exists which is against the definition
                    return 0; //Make false
                }
            }
            else if(ptr[i] >= 'A' && ptr[i] <= 'z'){ //If A-Z or a-z then true
                //Do nothing and continue to next char
            }
            else{
                return 0;
            }
            i++; //go to next char
        }
    }
    else{
        return 0; //If ptr[0] != then return 0 for false
    }
    i--; //to check for last position and see if it was a hyphen
    if(ptr[i] == '-'){ //If there are no digits or hyphens in array then true
        return 0;
    }
    //Artificial else statement
    return 1; //If the loop holds the whole time through the if statements then return 1 for true
}
int isNumber(char* ptr){
    int i = 0;
    int number = 0;
    while(ptr[i] != '\0'){
        if(ptr[i] >= '0' && ptr[i] <= '9'){
            number++;
        }
        else{
            return 0;
        }
        i++;
    }
    if(number > 1){
        if(ptr[0] == '0'){ //If the char is 0 then return false
            return 0;
        }
        //do nothing
    }
    return 1; //True
}
int isAssignment(char* ptr){
    int i = 0;
    while(ptr[i] != '\0'){
        if(ptr[i] == ':'){ //If first char is :
            i++; //Go to next char
            if(ptr[i] == ':'){ //If second char is :
                i++; //Go to next char
                if(ptr[i] == '='){ //If the third char is =
                    i++; //go to 4th char to make sure there is nothing afterwards
                }
                else{ //If the third char is not = then return 0 for false
                    return 0;
                }
            }
            else{ //If the second char is not : then return 0 for false
                return 0;
            }
        }
        else{ //If the first char is not : then return 0 for false
            return 0;
        }
    }
    return 1; //If it passes the loop statement then true
}
int isRangeSeparator(char* ptr){
    int i = 0;
    while(ptr[i] != '\0'){
        if(ptr[i] == '.'){ //If first char is a .
            i++; //go to next char
            if(ptr[i] == '.'){ //If second char is a .
                i++; //go to third char to make sure there is nothing left
            }
            else{ //If second char is not a . then return 0 for false
                return 0;
            }
        }
        else{ //If first char is not a . then return 0 for false
            return 0;
        }
    }
    if(i >= 3){ //Prevents repeating range seperators like ....
        return 0;
    }
    //artificial else
    return 1; //If it passes the loop statement then true
}
int isLcurly(char* ptr){
    int i = 0;
    while(ptr[i] != '\0'){
        if(ptr[i] == '{'){
            i++; //see if its a null terminator or if there is more
        }
        else{ //if first position is not { then return 0 for false
            return 0;
        }
    }
    if(i > 1){ //Prevents repeating Lcurly like {{
        return 0;
    }
    return 1; //If it passes the loop statement then true
}
int isRcurly(char* ptr){
    int i = 0;
    while(ptr[i] != '\0'){
        if(ptr[i] == '}'){
            i++; //see if its a null terminator or if there is more
        }
        else{ //if first position is not } then return 0 for false
            return 0;
        }
    }
    if(i > 1){ //Prevents repeating Rcurly like }}
        return 0;
    }
    return 1; //If it passes the loop statement then true
}
int isComma(char* ptr){
    int i = 0;
    while(ptr[i] != '\0'){
        if(ptr[i] == ','){
            i++; //see if its a null terminator or if there is more
        }
        else{ //if first position is not , then return 0 for false
            return 0;
        }
    }
    if(i > 1){ //Prevents repeating comma like ,,
        return 0;
    }
    return 1; //If it passes the loop statement then true
}
int isLparen(char* ptr){
    int i = 0;
    while(ptr[i] != '\0'){
        if(ptr[i] == '('){
            i++; //see if its a null terminator or if there is more
        }
        else{ //if first position is not { then return 0 for false
            return 0;
        }
    }
    if(i > 1){ //Prevents repeating Lcurly like {{
        return 0;
    }
    return 1; //If it passes the loop statement then true
}
int isRparen(char* ptr){
    int i = 0;
    while(ptr[i] != '\0'){
        if(ptr[i] == ')'){
            i++; //see if its a null terminator or if there is more
        }
        else{ //if first position is not { then return 0 for false
            return 0;
        }
    }
    if(i > 1){ //Prevents repeating Lcurly like {{
        return 0;
    }
    return 1; //If it passes the loop statement then true
}
int LastComma(char* ptr){
    int i = 0;
    while(ptr[i] != '\0'){ //find where the end of the char array is
        i++;
    }
    i--; //go back one to see the last char
    if(ptr[i] != ','){
        return 0; //If the last char is not a comma then return false
    }
    return i; //it will return i which must be 1 or greater => true if the last char is a comma
}
int LastParen(char* ptr){
    int i = 0;
    while(ptr[i] != '\0'){ //Find where the end of the char array is
        i++;
    }
    i--; //go back one to see the last char
    if(ptr[i] != ')'){
        return 0; //If the last char is not ) then return false
    }
    return i; //it will return i to show the position of the close comma
}
int FirstParen(char* ptr){
    if(ptr[0] == '('){
        //do nothing
    }
    else{
        return 0; //If not ( then return false
    }
    return 1; //Passed if statement, return true
}
int mapLexemes(char* buff){

    if(isTAGS(buff)){
        printf("%s -> TAGS\n", buff);
    }
    else if(isBEGIN(buff)){
        printf("%s -> BEGIN\n", buff);
    }
    else if(isSEQUENCE(buff)){
        printf("%s -> SEQUENCE\n", buff);
    }
    else if(isINTEGER(buff)){
        printf("%s -> INTEGER\n", buff);
    }
    else if(isDATE(buff)){
        printf("%s -> DATE\n", buff);
    }
    else if(isEND(buff)){
        printf("%s -> END\n", buff);
    }
    else if(isTypeReference(buff)){
        printf("%s -> TypeReference\n", buff);
    }
    else if(isIdentifier(buff)){
        printf("%s -> Identifier\n", buff);
    }
    else if(isNumber(buff)){
        printf("%s -> Number\n", buff);
    }
    else if(isAssignment(buff)){
        printf("%s -> Assignment\n", buff);
    }
    else if(isRangeSeparator(buff)){
        printf("%s -> Range Separator\n", buff);
    }
    else if(isLcurly(buff)){
        printf("%s -> Left Curly\n", buff);
    }
    else if(isRcurly(buff)){
        printf("%s -> Right Curly\n", buff);
    }
    else if(isComma(buff)){
        printf("%s -> Comma\n", buff);
    }
    else if(isLparen(buff)){
        printf("%s -> Left Parenthesis\n", buff);
    }
    else if(isRparen(buff)){
        printf("%s -> Right Parenthesis\n", buff);
    }
    else if(LastComma(buff)){
        int i = - 1;
        i = LastComma(buff);
        printf(", -> Comma\n");
        buff[i] = '\0';
        mapLexemes(buff); //Recursive call
    }
    else if(LastParen(buff)){
        int i = -1;
        i = LastParen(buff);
        printf(") -> Right Parenthesis\n");
        buff[i] = '\0';
        mapLexemes(buff); //Recursive call
    }
    else if(FirstParen(buff)){
        printf("( -> Left Parenthesis\n");
    }
    return 0;
}
int main() {
    FILE *fp;
    char buff[255];
    fp = fopen("/Users/haydenlabrie/CLionProjects/LexicalAnalyzer/input.txt", "r");
    while(!feof(fp)){
        fscanf(fp,"%s", buff);
        mapLexemes(buff);
    }
    return 0;
}