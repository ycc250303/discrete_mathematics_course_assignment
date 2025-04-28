#include <iostream>
#include <string>
#include <map>
#include <conio.h>
#include <stack>
#include <set>
#include<vector>

/*
 * Function Name:	checkOperator
 * Function:		check if a character is a logical operator
 * Input Parameters:char c
 * Return Value:	true / false
 */
bool isOperator(char c){
	return (c == '!' || c == '&' || c == '|' || c == '~' || c == '^');
}

/*
 * Function Name:	setPriority
 * Function:		set the priority of a logical operator
 * Input Parameters:char op
 * Return Value:	int
 */
int setPriority(char op) {
	switch (op) {
	case ')':
		return 5;
	case'!':
		return 4;
	case'&':
	case'|':
		return 3;
	case'^':
		return 2;
	case'~':
		return 1;
	case '(':
		return 0;
	default:
		exit(-1);
	}
}

/*
 * Function Name:	calculateExpression
 * Function:		calculate the value of a expression
 * Input Parameters:char op
 *					bool leftValue
 *					bool rightValue
 * Return Value:	true / false
 */
bool calculateVariable(char op, bool leftValue, bool rightValue = false) {
	switch (op) {
	case'!':
		return !leftValue;
	case'&':
		return leftValue && rightValue;
	case'|':
		return leftValue || rightValue;
	case'^':
		return !leftValue || rightValue;
	case'~':
		return leftValue == rightValue;
	default:
		exit(-1);
	}
}


/*
 * Function Name:	replaceLogicalOperators
 * Function:		replace logical operators with their corresponding symbols
 * Input Parameters:std::string expression
 * Return Value:	std::string
 */
std::string replaceLogicalOperators(std::string expression){
	std::map<char, std::string> OperatorMap = {
		{'&', "∧"},
		{'|', "∨"},
		{'~', "←→"},
		{'^', "→"}
	};
	std::string Result = "";
	for (char c : expression)
	{
		if (c!= '!' && isOperator(c))
			Result += OperatorMap[c];
		else
			Result += c;
	}
	return Result;
}

/*
 * Function Name:	infixToPostifx
 * Function:		convert infix expression to postfix expression
 * Input Parameters:std::string expression
 * Return Value:	std::string	
 */
std::string infixToPostifx(std::string expression) {
	std::stack<char> operators;
	std::string postfixExpression = "";
	/*travel the expression from left to right*/
	for (char c : expression)
	{
		if (isalpha(c))
			postfixExpression += c;
		else if (isOperator(c)) {
			if (operators.empty())
				operators.push(c);
			else if (setPriority(c) > setPriority(operators.top()))
				operators.push(c);
			else {
				while (!operators.empty() && setPriority(c) <= setPriority(operators.top())) {
					postfixExpression += operators.top();
					operators.pop();
				}
				operators.push(c);
			}
		}
		else if (c == '(')
			operators.push(c);
		else if (c == ')') {
			while (!operators.empty() && operators.top() != '(') {
				postfixExpression += operators.top();
				operators.pop();
			}
			if (!operators.empty() && operators.top() == '(') {
				operators.pop();
			}
		}
	}
	while (!operators.empty()) {
		postfixExpression += operators.top();
		operators.pop();
	}
	return postfixExpression;
}

/*
 * Function Name:	calculatePostfixExpression
 * Function:		calculate the value of a postfix expression
 * Input Parameters:std::string postfixExpression
 *					std::map<char, bool> variableValues
 * Return Value:	true / false
 */
bool calculatePostfixExpression(std::string postfixExpression, std::map<char, bool> variableValues) {
	std::stack<bool> values;
	for (char c : postfixExpression) {
		if(isalpha(c))
			values.push(variableValues[c]);
		else if (isOperator(c)) {
			if (c == '!') {
				bool value = values.top();
				values.pop();
				values.push(!value);
			}
			else {
				bool rightValue = values.top();
				values.pop();
				bool leftValue = values.top();
				values.pop();
				values.push(calculateVariable(c, leftValue, rightValue));
			}
		}
	}
	return values.top();
}
	
/*
 * Function Name:	countVariables
 * Function:		count the number of variables in a expression
 * Input Parameters:const std::string& expression
 * Return Value:	std::set<char>
 */
std::set<char> countVariables(const std::string expression){
	std::set<char> Variables;
	for (char c : expression)
	{
		if (isalpha(c))
			Variables.insert(c);
	}
	return Variables;
}

/*
 * Function Name:	outputTruthTableAndMasterParadigm
 * Function:		output the truth table and master paradigm of a expression
 * Input Parameters:const std::string expression
 * Return Value:	void
 */
void outputTruthTableAndMasterParadigm(const std::string expression){
	/*tranform the expression to postfix expression*/
	std::string postfixExpression = infixToPostifx(expression);

	/*count the number of variables*/
	std::set<char> variables = countVariables(expression);
	int variableCount = variables.size();
	std::cout << ">>> 该命题公式的变量个数为:" << variableCount << std::endl << std::endl;

	/*store  master paradigm*/
	std::vector<int> conjunctionParadigm, analyticParadigm;


	/*print the header*/
	std::cout << ">>> 输出真值表如下:" << std::endl;
	std::cout << "+";
	for (int count = 0; count < variableCount+1; count++) 
		std::cout << "-------+";
	std::cout << std::endl;
	std::cout << "|";
	for (const auto variable : variables)
		std::cout << "   " << variable << "   |";
	std::cout<<" Value |"<< std::endl;
	std::cout << "+";
	for (int count = 0; count < variableCount + 1; count++)
		std::cout << "-------+";
	std::cout << std::endl;

	/*print the truth table*/
	std::map<char, bool> variableValues;
	for (int i = 0; i < pow(2, variableCount); i++) {
		int nthPower = variableCount-1;
		std::cout << "|";
		/*set the value of variables*/
		for (const auto variable : variables) {
			int temp = static_cast<int>(pow(2, nthPower));
			nthPower--;
			variableValues[variable] = i & temp;
			std::cout << "   " << variableValues[variable] << "   |";
		}
		/*calculate and output the result*/
		bool value = calculatePostfixExpression(postfixExpression, variableValues);
		std::cout << "   " << value << "   |" << std::endl;
		if(value)
			analyticParadigm.push_back(i);
		else
			conjunctionParadigm.push_back(i);

		std::cout << "+";
		for (int count = 0; count < variableCount + 1; count++)
			std::cout << "-------+";
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << ">>> 该命题公式的主合取范式:" << std::endl;
	for (size_t count = 0; count < conjunctionParadigm.size(); count++) {
		std::cout<<"M<"<<conjunctionParadigm[count]<<">";
		if(count!= conjunctionParadigm.size()-1)
			std::cout<<"∨";
	}
	std::cout << std::endl << std::endl;

	std::cout << ">>> 该命题公式的主析取范式:" << std::endl;
	for (size_t count = 0; count < analyticParadigm.size(); count++) {
		std::cout<<"m<"<<analyticParadigm[count]<<">";
		if(count!= analyticParadigm.size()-1)
			std::cout<<"∧";
	}
	std::cout << std::endl << std::endl;
}


/*
 * Function Name:    isValidExpression
 * Function:         Check if a expression is valid
 * Input Parameters: const std::string& expression
 * Return Value:     true / false
 */
bool checkExpression(const std::string &expression){
	if (expression.empty()){
		std::cout << "输入错误：命题公式为空，请重新输入！" << std::endl << std::endl;
		return false;
	}
	std::stack<char> parentheses;
	char prev_char = '\0';
	/*travelling the expression from left to right*/
	for (char c : expression)
	{
		if (!isalpha(c) && (!isOperator(c)) && c != '(' && c != ')')
		{
			std::cout << "输入错误：命题公式中含有非法字符，请重新输入！" << std::endl << std::endl;
			return false;
		}
		if (prev_char == '\0' && (c == '&' || c == '|' || c == '~' || c == '^'))
		{
			std::cout << "输入错误：命题公式中第一个字符不能为二元运算符，请重新输入！" << std::endl << std::endl;
			return false;
		}
		if (prev_char == '(' && c == ')')
		{
			std::cout<<"输入错误，命题公式中不能出现空括号，请重新输入！" << std::endl << std::endl;
			return false;
		}
		if (c == '!' && prev_char == '!')
		{
			std::cout << "输入错误：命题公式中不能连续出现取非操作，请重新输入！" << std::endl << std::endl;
			return false;
		}
		if (c == '!' && isalpha(prev_char))
		{
			std::cout << "输入错误：命题公式中取非操作后面必须接变量，请重新输入！" << std::endl << std::endl;
			return false;
		}
		if ((prev_char == ')' && isalpha(c)) || c == '(' && isalpha(prev_char))
		{
			std::cout<<"输入错误，命题公式中括号和变量的连接不正确，请重新输入！" << std::endl << std::endl;
			return false;
		}
		if (c == '(')
			parentheses.push(c);
		else if (c == ')')
		{
			if (parentheses.empty())
			{
				std::cout << "输入错误：命题公式中括号不匹配，请重新输入！" << std::endl << std::endl;
				return false;
			}
			parentheses.pop();
		}
		if (isalpha(c) && isalpha(prev_char))
		{
			std::cout << "输入错误：命题公式中变量不能连续出现，请重新输入！" << std::endl << std::endl;
			return false;
		}
		if ((c == '&' || c == '|' || c == '~' || c == '^') && (!isalpha(prev_char) && prev_char!= ')')) {
			std::cout << "输入错误：命题公式中每个二元运算符前后必须连接变量，请重新输入！" << std::endl << std::endl;
			return false;
		}
		prev_char = c;
	}
	if (isOperator(prev_char))
	{
		std::cout << "输入错误：命题公式不能以运算符结尾，请重新输入！" << std::endl << std::endl;
		return false;
	}
	if (!parentheses.empty())
	{
		std::cout << "输入错误：命题公式中括号不匹配，请重新输入！" << std::endl << std::endl;
		return false;
	}
	return true;
}

/*
 * Function Name:	inputLogicalValue
 * Function:		input a logical value from user
 * Input Parameters:char FalseValue = '0'
 *					char TrueValue = '1'
 * Return Value:	true / false
 */
bool inputLogicalValue(char FalseValue = '0', char TrueValue = '1'){
	while (true) {
		char InputChar = _getch();
		if (InputChar == 0 || InputChar == -32)
			InputChar = _getch();
		else if (InputChar == FalseValue || InputChar == TrueValue) {
			std::cout << InputChar << std::endl << std::endl;
			return InputChar == TrueValue;
		}
	}
}


/*
 * Function Name:	main
 * Function:		main function
 * Return Value:	0
 */
int main() {
	do {
		system("cls");
		/*print the title*/
		std::cout << "+--------------------------------------+" << std::endl;
		std::cout << "|            真值表、主范式            |" << std::endl;
		std::cout << "|    Truth table and Master paradigm   |" << std::endl;
		std::cout << "+--------------------------------------+" << std::endl << std::endl;

		/*output the requirement of input*/
		std::cout << ">>> 命题公式输入要求:" << std::endl;
		std::cout << "[1] 字符 '!' 表示非" << std::endl;
		std::cout << "[2] 字符 '&' 表示与" << std::endl;
		std::cout << "[3] 字符 '|' 表示或" << std::endl;
		std::cout << "[4] 字符 '^' 表示蕴含" << std::endl;
		std::cout << "[5] 字符 '~' 表示等值" << std::endl;
		std::cout << "[6] 命题公式中只能输入大小写字母、括号和以上五种运算符，空格后的内容将被截断" << std::endl;
		std::cout << "[7] 命题公式中的括号嵌套匹配" << std::endl;
		std::cout << "[8] 命题公式中的变量均为单字符" << std::endl;
		std::cout << "[9] 命题公式中每个运算符前后都必须连接变量" << std::endl<< std::endl;

		/*input the formula*/
		std::string Formula;
		do {
			std::cout << "请输入命题公式:" ;
			std::cin >> Formula;
		} while (!checkExpression(Formula));
		std::cout << std::endl;
		/*output the formula and truth table*/
		std::cout << ">>>命题公式:" <<replaceLogicalOperators(Formula) << std::endl<< std::endl;
		outputTruthTableAndMasterParadigm(Formula);

		std::cout << "是否退出程序?(y/n)" ;
	} while (!inputLogicalValue('n', 'y'));
	std::cout << "欢迎下次再次使用!" << std::endl;
	return 0;
}