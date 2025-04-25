#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

// Функция задания приоритетов операторов
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функция проверки, является ли символ оператором
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Преобразование инфиксного выражения в постфиксное (ОПЗ)
string infixToPostfix(const string& infix) {
    stack<char> operators;
    string postfix;

    for (char token : infix) {
        if (isalnum(token)) {
            postfix += token; // Добавляем операнд
        }
        else if (token == '(') {
            operators.push(token);
        }
        else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop(); // Удаляем '('
        }
        else if (isOperator(token)) {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(token)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Вычисление выражения в ОПЗ
double evaluatePostfix(const string& postfix, const map<char, double>& variables) {
    stack<double> values;

    for (char token : postfix) {
        if (isalnum(token)) {
            if (isdigit(token)) {
                values.push(token - '0'); // Для чисел
            }
            else if (variables.count(token)) {
                values.push(variables.at(token)); // Для переменных
            }
            else {
                cerr << "Ошибка: неопределённая переменная " << token << "." << endl;
                exit(1); // Завершаем программу
            }
        }
        else if (isOperator(token)) {
            if (values.size() < 2) {
                cerr << "Ошибка: недостаточно операндов для операции." << endl;
                exit(1);
            }

            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            if (token == '/' && b == 0) {
                cerr << "Ошибка: деление на ноль." << endl;
                exit(1);
            }
            switch (token) {
            case '+': values.push(a + b); break;
            case '-': values.push(a - b); break;
            case '*': values.push(a * b); break;
            case '/': values.push(a / b); break;
            }
        }
    }

    if (values.size() != 1) {
        cerr << "Ошибка: неверное выражение." << endl;
        exit(1);
    }

    return values.top();
}

int main() {
    setlocale(LC_ALL, "RUS");
    string infix;
    map<char, double> variables;

    // Ввод выражения
    cout << "Введите математическое выражение: ";
    cin >> infix;

    // Ввод значений переменных
    cout << "Введите значения переменных (например, a=10.5 b=5.3 c=2.8 d=3.1 e=4.0): ";
    string input;
    getline(cin >> ws, input);
    stringstream ss(input);
    char var;
    double value;

    while (ss >> var) {
        if (ss.peek() == '=') {  // Проверяем наличие знака '='
            ss.ignore();  // Игнорируем '='
            if (ss >> value) {
                variables[var] = value;
            }
            else {
                cerr << "Ошибка: некорректное значение для переменной " << var << "." << endl;
                exit(1);
            }
        }
    }

    // Проверка всех переменных
    for (char token : infix) {
        if (isalpha(token) && variables.count(token) == 0) {
            cerr << "Ошибка: значение переменной " << token << " не задано." << endl;
            exit(1);
        }
    }

    // Преобразование в ОПЗ
    string postfix = infixToPostfix(infix);
    cout << "Обратная польская запись: " << postfix << endl;

    // Вычисление результата
    double result = evaluatePostfix(postfix, variables);
    cout << fixed << setprecision(2); // Форматируем вывод результата
    cout << "Результат: " << result << endl;

    return 0;
}
