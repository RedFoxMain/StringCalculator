#include <iostream>
#include <string>
#include <cctype>

float Factor(std::string::iterator &curr_char){
    std::string str;
    while(isdigit(*curr_char)){ // get int
        str += *curr_char;
        curr_char++;
        if (*curr_char == '.') { // get float
        	str += *curr_char;
            curr_char++;
            while ((*curr_char != '\0') && (std::isdigit(*curr_char))) {
            	str += *curr_char;
                curr_char++;
            }
    	}else{ std::runtime_error("Ошибка в выражении!"); }
    }
    return stof(str);
}

// If we have * or / parse they first
float Term(std::string::iterator &curr_char){
    float res = Factor(curr_char);
    while(*curr_char == '*' || *curr_char == '/'){
        char op = *(curr_char++);
        if(op == '*'){ res *= Factor(curr_char); }
        else{ res /= Factor(curr_char); }
    }
    return res;
}

// // If we have - or + parse they second
float Expr(std::string::iterator &curr_char){
    float res = Term(curr_char);
    while(*curr_char == '+' || *curr_char == '-'){
        char op = *(curr_char++);
        if(op == '+'){ res += Term(curr_char); }
        else{ res -= Term(curr_char); }
    }
    return res;
}

int main(){
    std::string expr = "5.8+6.29";
    std::string::iterator it = expr.begin();
    std::cout << Expr(it) << std::endl;
}