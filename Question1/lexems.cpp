#include <iostream>
#include <string>
#include <cstring>
#include <streambuf>
#include <fstream>
#include <list>

using namespace std;

bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || 
        ch == '/' || ch == ',' || ch == ';' || ch == '>' || 
        ch == '<' || ch == '=' || ch == '(' || ch == ')' || 
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isSpecialSymbolLogical(char* ch)
{
    if ( !strcmp(ch, "&&") || 
        !strcmp(ch, "||") || !strcmp(ch, "!"))
        return (true);
    return (false);
}

bool isSpecialSymbol(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || 
        ch == '/' || ch == '>' || ch == '<' || 
        ch == '='|| ch == '%' || ch == '{' || 
        ch == '}' ||ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' )
        return (true);
    return (false);
}


// bool isOperator(char ch)
// {
//     if (ch == '+' || ch == '-' || ch == '*' || 
//         ch == '/' || ch == '>' || ch == '<' || 
//         ch == '=')
//         return (true);
//     return (false);
// }

bool isType(char* str)
{
    if (!strcmp(str, "int") || !strcmp(str, "float") 
        || !strcmp(str, "string") || !strcmp(str, "char")
        || !strcmp(str, "void"))
        return (true);
    return (false);
}


bool isInteger(char* str)
{
    int i, len = strlen(str);
  
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

bool isStringLiteral(char* str)
{
    int i, len = strlen(str);
    bool hasQuote = false;
  
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if(str[0] == '\"')
            hasQuote = true;
        // if (str[i] != '0' && str[i] != '1' && str[i] != '2'
        //     && str[i] != '3' && str[i] != '4' && str[i] != '5'
        //     && str[i] != '6' && str[i] != '7' && str[i] != '8'
        //     && str[i] != '9' && str[i] != '\"' || (str[i] == '-' && i > 0))
        //     return (false);
    }
    return (hasQuote);
}

bool isCharLiteral(char* str)
{
    int i, len = strlen(str);
    bool hasSingQuote = false;
  
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if(str[0] == '\'')
            hasSingQuote = true;
        // if (str[i] != '0' && str[i] != '1' && str[i] != '2'
        //     && str[i] != '3' && str[i] != '4' && str[i] != '5'
        //     && str[i] != '6' && str[i] != '7' && str[i] != '8'
        //     && str[i] != '9' && str[i] != '\"' || (str[i] == '-' && i > 0))
        //     return (false);
    }
    return (hasSingQuote);
}


bool isRealNumber(char* str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;
  
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' || 
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

bool validIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' || 
        str[0] == '6' || str[0] == '7' || str[0] == '8' || 
        str[0] == '9' ||(isDelimiter(str[0]) == true && 
        isType(str) == false))
        return (false);
    return (true);
}

char* subString(char* str, int left, int right)
{
    int i;
    char* subStr = (char*)malloc(
                  sizeof(char) * (right - left + 2));
  
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

void parse(char* str)
{
    int left = 0, right = 0;
    int len = strlen(str);
  
    while (right <= len && left <= right) {
        if (isDelimiter(str[right]) == false)
            right++;
  
        if (isDelimiter(str[right]) == true && left == right) {
            if (isSpecialSymbol(str[right]) == true)
                printf("'%c' IS AN OPERATOR AND SPECIAL SYMBOL\n", str[right]);
            
            right++;
            left = right;
        } else if (isDelimiter(str[right]) == true && left != right
                   || (right == len && left != right)) {
            char* subStr = subString(str, left, right - 1);
  
            if (isType(subStr) == true && validIdentifier(subStr) == true)
                printf("'%s' IS A KEYWORD\n", subStr);
  
            else if (isInteger(subStr) == true)
                printf("'%s' IS AN INTEGER\n", subStr);

            else if(isStringLiteral(subStr) == true)
                printf("'%s' IS A STRING LITERAL\n", subStr);

            else if(isCharLiteral(subStr) == true)
                printf("'%s' IS A CHAR LITERAL\n", subStr);
        
             else if (isSpecialSymbolLogical(subStr) == true)
                printf("'%s' IS A SPECIAL LOGIC SYMBOL\n", subStr);    
  
            else if (isRealNumber(subStr) == true)
                printf("'%s' IS A REAL NUMBER\n", subStr);
  
            else if (validIdentifier(subStr) == true
                     && isDelimiter(str[right - 1]) == false && isType(subStr) == false && isStringLiteral(subStr) == false)
                printf("'%s' IS A VALID IDENTIFIER\n", subStr);
  
            else if (validIdentifier(subStr) == false
                     && isDelimiter(str[right - 1]) == false && isType(subStr) == true )
                printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
            left = right;
        }
    }

    return;
}


int main(){
    ifstream file("./Perl_ident.txt");
    string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    contents.c_str();
    //string ctnArray[] = {contents.c_str()};
    int len = contents.length();

    char holder[len];
    char arr[len];
    if(file.is_open()){
        for(int i = 0; i <= len; i++){
           holder[i] = contents[i]; 
        }   
    }
        parse(holder);
        // identifier(holder, len);
    return 0;
}