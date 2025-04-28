#include <iostream>
#include <conio.h>
using namespace std;

/*
 * Function Name:	inputLogicalValue
 * Function:		input a logical value from user
 * Input Parameters:char FalseValue = '0'
 *					char TrueValue = '1'
 * Return Value:	true / false
 */
bool inputLogicalValue(char FalseValue = '0', char TrueValue = '1')
{
    while (true) {
        char InputChar = _getch();
        if (InputChar == 0 || InputChar == -32)
            InputChar = _getch();
        else if (InputChar == FalseValue || InputChar == TrueValue) {
            cout << InputChar <<endl << endl;
            return InputChar == TrueValue;
        }
    }
}

/*
 * Function Name:	main
 * Function:		main function
 * Return Value:	0
 */
int main()
{
    do {
        system("cls");
        cout << "+------------------------------------+" << endl;
        cout << "|           �����߼����Ӵ�           |" << endl;
        cout << "|   propositional logic connective   |" << endl;
        cout << "+------------------------------------+" << endl << endl;

        cout << "������ P ��ֵ [0/1]: ";
        bool p = inputLogicalValue();
        cout << "������ Q ��ֵ [0/1]: ";
        bool q = inputLogicalValue();

        cout << ">>> ��ȡ: P��Q = " << (p && q) << endl << endl;
        cout << ">>> ��ȡ: P��Q = " << (p || q) << endl << endl;
        cout << ">>> ����: P��Q = " << (!p || q) << endl << endl;
        cout << ">>> ˫������: P����Q = " << ((!p || q) && (!q || p)) << endl << endl;

        cout << "�Ƿ��˳����� [y/n]: ";
    } while (!inputLogicalValue('n', 'y'));
    return 0;
}