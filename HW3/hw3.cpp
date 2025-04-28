#include <iostream>
#include <vector>
#include <conio.h>
#include <limits>

/* Define Matrix type */
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
		if (std::cin.fail()||count!=static_cast<int>(count)) {
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
 * Function Name:	calSelfReflexiveClosure
 * Function:		calculate the self-reflexive closure of a matrix
 * Input Parameters:const Matrix matrix
 * Return Value:	Matrix: the self-reflexive closure of the matrix
 */
Matrix calSelfReflexiveClosure(const Matrix matrix) {
	Matrix matrixReflexive = matrix;
	for (size_t count = 0; count < matrix.size(); count++)
		if (matrix[count][count] == 0)
			matrixReflexive[count][count] = 1;
	return matrixReflexive;
}

/*
 * Function Name:	calSymmetryClosure
 * Function:		calculate the symmetry closure of a matrix
 * Input Parameters:const Matrix matrix		
 * Return Value:	Matrix: the symmetry closure of the matrix
 */
Matrix calSymmetryClosure(const Matrix matrix) {
	Matrix matrixSymmetry = matrix;
	for (size_t row = 0; row < matrix.size(); row++) {
		for (size_t col = 0; col < row; col++)
			if (matrixSymmetry[row][col] == 1)
				matrixSymmetry[col][row] = 1;
	}
	return matrixSymmetry;
}

/*
 * Function Name:	multiplyMatrix
 * Function:		multiply two matrices
 * Input Parameters:const Matrix matrix1
 *					const Matrix matrix2
 * Return Value:	Matrix: the result of the multiplication
 */
Matrix multiplyMatrix(const Matrix matrix1, const Matrix matrix2 ) {
	if (matrix1.size() != matrix2[0].size() || matrix1[0].size() != matrix2.size()) {
		std::cerr << "Error: matrix size not match!" << std::endl;
		exit(1);
	}
	Matrix resultMatrix(matrix1.size(), std::vector<int>(matrix2[0].size(), 0));
	for (size_t newRow = 0; newRow < matrix1.size(); newRow++) {
		for (size_t newCol = 0; newCol < matrix2[0].size(); newCol++) {
			for (size_t count = 0; count < matrix1[0].size(); count++) {
				if (resultMatrix[newRow][newCol] == 0)
					resultMatrix[newRow][newCol] += matrix1[newRow][count] * matrix2[count][newCol];
			}
		}
	}
	return resultMatrix;
}

/*
 * Function Name:	calTransferClosure
 * Function:		calculate the transfer closure of a matrix
 * Input Parameters:const Matrix matrix
 * Return Value:	Matrix: the transfer closure of the matrix
 */
Matrix calTransferClosure(const Matrix matrix) {
	/*calculate the nth power of matrix */
	int count = matrix.size();
	std::vector<Matrix> matrixArray(count);
	Matrix transferClosure(matrix.size(), std::vector<int>(matrix.size(), 0));
	matrixArray[0] = matrix;
	for (size_t i = 1; i < matrix.size(); i++) {
		matrixArray[i] = multiplyMatrix(matrixArray[i - 1], matrix);
	}
	/*calculate the transfer closure*/
	for (size_t row = 0; row < matrix.size(); row++) {
		for (size_t col = 0; col < matrix.size(); col++) {
			for(size_t i =0; i < count; i++){
				if(matrixArray[i][row][col] == 1)
					transferClosure[row][col] = 1;
			}
		}
	}
	return transferClosure;
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
 * Function:		the main function
 * Return Value:	int: 0 for success
 */
int main() {
	do {
		system("cls");
		/*print the title*/
		std::cout << "+-----------------------------------------------------------------------------------+" << std::endl;
		std::cout << "|                            求关系的自反、对称和传递闭包                           |" << std::endl;
		std::cout << "| Finding self-inversions, symmetries and transfer closures for relational matrices |" << std::endl;
		std::cout << "+-----------------------------------------------------------------------------------+" << std::endl << std::endl;

		/*input the information of the matrix*/
		unsigned int row = inputMatrixCount(2, 10, "关系矩阵大小");
		unsigned int col = row;
		Matrix matrix(row, std::vector<int>(col, 0));
		inputMatrixInfo(matrix);

		/*calculate the passing closure*/
		Matrix matrixReflexive = calSelfReflexiveClosure(matrix);
		Matrix matrixSymmetry = calSymmetryClosure(matrix);
		Matrix matrixTransfer = calTransferClosure(matrix);

		/*output the result*/
		outputMatrix(matrixReflexive, "自反闭包");
		outputLogicalRelationship(matrixReflexive);

		outputMatrix(matrixSymmetry, "对称闭包");
		outputLogicalRelationship(matrixSymmetry);

		outputMatrix(matrixTransfer, "传递闭包");
		outputLogicalRelationship(matrixTransfer);

		std::cout << "是否退出程序? [y/n]:";
	} while (!inputLogicalValue('n', 'y'));
	return 0;
}