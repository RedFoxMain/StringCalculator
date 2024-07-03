#include <iostream>
#include <string>
#include <cctype>

char *curr_char;

float Factor(){
    std::string str;
    while(isdigit(*curr_char)){
        str += *curr_char;
        *curr_char++;
        if (*curr_char == '.') {
        	str += curr_char;
            *curr_char++;
            while ((*curr_char != '\0') && (std::isdigit(*curr_char))) {
            	str += curr_char;
                *curr_char++;
            }
    	}
    }
    return stof(str);
}

float Term(char* expr){
    float res = Factor();
    while(*curr_char == '*' || *curr_char == '/'){
        char op = *curr_char++;
        if(op == '*'){ res *= Factor(); }
        else{ res /= Factor(); }
    }
   return res;
}

float Expr(char* expr){
    float res = Term(expr);
    while(*curr_char == '+' || *curr_char == '-'){
        char op = *curr_char++;
        if(op == '+'){ res += Term(expr); }
        else{ res -= Term(expr); }
    }
    return res;
}

int main(){
    for(;;){
        char expr[50] = "";
        printf(">> ");
        curr_char = expr;
        scanf("%s", &expr);
        std::cout << Expr(curr_char) << std::endl;
    }
}