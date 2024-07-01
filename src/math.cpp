#include "../include/math.h"
bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/'
           || c == '^';
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

double applyOp(double a, double b, char op)
{
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    default:
        return 0;
    }
}

double evaluateExpression(const string& expression)
{
    stack<char> operators; 
    stack<double> operands; 

    stringstream ss(expression); 

    string token;
    while (getline(
        ss, token,
        ' ')) {
        if (token.empty())
            continue; 
        if (isdigit(token[0])) { 
            double num;
            stringstream(token)
                >> num; 
            operands.push(num); 
        }
        else if (isOperator(token[0])) { 
            char op = token[0];
            while (!operators.empty()
                   && precedence(operators.top())
                          >= precedence(op)) {
                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                operands.push(applyOp(a, b, op));
            }
            operators.push(op);
        }
        else if (token[0] == '(') { 
            operators.push('(');
        }
        else if (token[0] == ')') { 
            while (!operators.empty()
                   && operators.top() != '(') {
                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                operands.push(applyOp(a, b, op));
            }
            operators.pop();
        }
    }

    while (!operators.empty()) {
        double b = operands.top();
        operands.pop();
        double a = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();
        operands.push(applyOp(a, b, op));
    }
    return operands.top();
}

bool isInt(double value)
{
    int casted = (int)value;
    double rem = value - (double)casted;
    if(rem == 0)
    {
        return true;
    }
    return false;
}