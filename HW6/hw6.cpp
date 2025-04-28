#include <iostream>
#include <conio.h>
#include <limits>
#include <vector>

/*define the martix*/
typedef std::vector<std::vector<int>> Matrix;

/*
 * Function Name:	inputLogicalValue
 * Function:		input a logical value from user
 * Input Parameters:char FalseValue = '0'
 *					char TrueValue = '1'
 * Return Value:	int: 0 for False, 1 for True
 */
int inputLogicalValue(char FalseValue = '0', char TrueValue = '1')
{
	while (true) {
		char InputChar = _getch();
		if (InputChar == 0 || InputChar == -32)
			InputChar = _getch();
		else if (InputChar == FalseValue || InputChar == TrueValue) {
			std::cout << InputChar;
			return InputChar == TrueValue;
		}
	}
}

/*
 * Function Name:	logicalPlus
 * Function:		calculate the logical OR operation
 * Input Parameters:const int a
 *					const int b
 * Return Value:	int: 0 for False, 1 for True
 */
int logicalPlus(const int relation1, const int relation2) {
	return static_cast<int>(relation1 || relation2);
}


/*
 * Function Name:	inputMartixInfo
 * Function:		input a logical matrix from user
 * Input Parameters:Matrix &matrix
 * Return Value:	void
 */
void inputMatrixInfo(Matrix& matrix) {
	std::cout << std::endl;
	std::cout << ">>> 请输入关系矩阵[0/1]" << std::endl << std::endl;
	std::cout << "Martix = [ ";
	for (size_t row = 0; row < matrix.size(); row++) {
		for (size_t col = 0; col < matrix[row].size(); col++) {
			/*input a logical value*/
			matrix[row][col] = inputLogicalValue();
			if (row != matrix.size() - 1 || col != matrix[row].size() - 1)
				std::cout << ",";
		}
		if (row == matrix.size() - 1) {
			std::cout << " ]" << std::endl;
			break;
		}
		std::cout << std::endl << "           ";
	}
	std::cout << std::endl;
}

/*
 * Function Name:	inputMatrixCount
 * Function:		input a matrix count from user
 * Input Parameters:const int minCount
 *					const int maxCount
 *					const char* prompt
 * Return Value:	int: the matrix count
 */
int inputMatrixCount(const int minCount, const int maxCount, const char* prompt) {
	double count;
	while (true) {
		std::cout << "请输入" << prompt << "的大小[整数范围" << minCount << "-" << maxCount << "]：";
		std::cin >> count;
		if (std::cin.fail() || count != static_cast<int>(count)) {
			std::cout << "输入的值不是整数,请重新输入!" << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else if (count < minCount || count > maxCount) {
			std::cout << "输入的值超出范围,请重新输入!" << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else
			break;
	}
	return count;
}

/*
 * Function Name:	warShall
 * Function:		calculate the logical AND operation
 * Input Parameters:Matrix &matrix
 * Return Value:	void
 */
void WarShall(Matrix& martix) {
	for (size_t col = 0; col < martix.size(); col++) {
		for (size_t row = 0; row < martix.size(); row++) {
			if (martix[row][col] == 1) {
				for (size_t i = 0; i < martix.size(); i++) {
					martix[row][i] = martix[row][i] | martix[col][i];
				}
			}
		}
	}
}

/*
 * Function Name:	outputMatrix
 * Function:		output a logical matrix
 * Input Parameters:const Matrix matrix
 *					const char* prompt
 * Return Value:	void
 */
void outputMatrix(const Matrix matrix, const char* prompt) {
	std::cout << ">>> " << prompt << std::endl << std::endl;
	std::cout << "Martix = [ ";
	for (size_t row = 0; row < matrix.size(); row++) {
		for (size_t col = 0; col < matrix[row].size(); col++) {
			std::cout << matrix[row][col];
			if (row != matrix.size() - 1 || col != matrix[row].size() - 1)
				std::cout << ",";
		}
		if (row == matrix.size() - 1) {
			std::cout << " ]" << std::endl;
			break;
		}
		std::cout << std::endl << "           ";
	}
	std::cout << std::endl;
}

/*
 * Function Name:	outputLogicalRelationship
 * Function:		output the logical relationship of the matrix
 * Input Parameters:const Matrix matrix
 * Return Value:	void
 */
void outputLogicalRelationship(const Matrix matrix) {
	std::cout << ">>> 逻辑关系:{";
	for (size_t row = 0; row < matrix.size(); row++) {
		for (size_t col = 0; col < matrix[row].size(); col++) {
			if (matrix[row][col] == 1) {
				std::cout << "<" << static_cast<char>(row + 'a') << "," << static_cast<char>(col + 'a') << "> ";
			}
		}
	}
	std::cout << "}" << std::endl << std::endl;
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
		std::cout << "+----------------------------------------------------+" << std::endl;
		std::cout << "|           利用Warshall算法求解传递闭包             |" << std::endl;
		std::cout << "| Solving Passing Closures with Warshall's Algorithm |" << std::endl;
		std::cout << "+----------------------------------------------------+" << std::endl << std::endl;

		/*input the information of the matrix*/
		unsigned int row = inputMatrixCount(2, 10, "关系矩阵大小");
		unsigned int col = row;
		Matrix matrix(row, std::vector<int>(col, 0));
		inputMatrixInfo(matrix);

		/*calculate the passing closure*/
		WarShall(matrix);

		/*output the result*/
		outputMatrix(matrix, "传递闭包");
		outputLogicalRelationship(matrix);

		std::cout << "是否退出程序? [y/n]:";
	} while (!inputLogicalValue('n', 'y'));
	return 0;
}
