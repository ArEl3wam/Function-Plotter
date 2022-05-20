#pragma once
#include <string>
#include <math.h>
#include <queue>
#include <stack>


bool isOperand(std::string c){

    if(c=="+" || c=="-" || c=="*" || c=="/" || c== "^"){
        return true;
    }
    return false;
}


double evaluator(std::string num1 , std::string num2 ,std::string operand){
    double a = stod(num1);
    double b = stod(num2);
    if(operand== "+"){
        return a + b;
    }
    if(operand== "-"){
        return a - b;
    }
    if(operand== "/"){
        return a / b;
    }
    if(operand== "*"){
        return a * b;
    }
    if(operand== "^"){
        return pow(a,b);
    }

}

bool higherPrio(char op1 , char op2){

    if((op1 == '+') && ((op2== '+') || (op2== '-') || (op2== '*') || (op2== '/') || (op2== '^'))){
        return true;
    }
    if((op1 == '-') && ((op2== '+') || (op2== '-') || (op2== '*') || (op2== '/') || (op2== '^'))){
        return true;
    }
    if ( (op1== '*') && ( (op2 == '*') || (op2 == '/') || (op2 == '^') )){
        return true;
    }
    if ( (op1== '/') && ( (op2 == '*') || (op2 == '/') || (op2 == '^') )){
        return true;
    }
    return false;

}

std::queue<std::string> postfix (std::string equation){

    std::queue<std::string> postfix;
    std::string number="";
    std::stack<char> operandStack;
    for(int i=0; i<equation.size(); i++){
        // operand
        if(isOperand(std::string(1,equation[i]))){
            //fake operand
            if((i==0) || (i==equation.size()-1)){
                if(equation[i]=='-' && i==0){
                    number+=equation[i];
                }
                continue;
            }
            if(number.size()>0){
                postfix.push(number);
            }

            number="";


            //detecting redundant operands and -ve sign

            if(isOperand(std::string(1,equation[i-1]))){
                if((equation[i]=='-') && !isOperand(std::string(1,equation[i+1]))){
                    number+=equation[i];
                }
                continue;
            }


            //stack is empty
            if(operandStack.empty()){
                operandStack.push(equation[i]);
            }
            //stack not stable
            else if(higherPrio(equation[i],operandStack.top())){
                while(!operandStack.empty() && higherPrio(equation[i],operandStack.top())){
                    postfix.push(std::string(1,operandStack.top()));
                    operandStack.pop();
                }
                operandStack.push(equation[i]);

            }
            //stack is stable
            else{
                operandStack.push(equation[i]);
            }
        }
        // number
        else{
            number+=equation[i];
        }
    }
    postfix.push(number);
    while(!operandStack.empty()){
        postfix.push(std::string(1,operandStack.top()));
        operandStack.pop();
    }
    return postfix;

}

double equationSolver(std::queue<std::string> postFix){

    std::stack<std::string> temp;
    while(!postFix.empty()){
        //number
        if(!isOperand(postFix.front())){
            temp.push(postFix.front());
            postFix.pop();
        }
        //operand
        else{

            std::string num2=temp.top();
            temp.pop();
            std::string num1=temp.top();
            temp.pop();
            temp.push(std::to_string(evaluator(num1,num2,postFix.front())));
            postFix.pop();
        }
    }
    return (stod(temp.top()));

}
std::string replacer(std::string equation, std::string maxmin){

    std::string newEquation=equation;

    for(int i=0; i<newEquation.size(); i++){
        if(newEquation[i]=='x' || newEquation[i]=='X'){
            newEquation.replace(i,1,maxmin);
        }
    }
    return newEquation;
}
