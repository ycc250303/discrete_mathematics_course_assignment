#include<iostream>
#include<cmath>

/*
 * Function Name:	main
 * Function:		main function
 * Return Value:	0
 */
int main()
{
	std::cout << "+-----------------------------------+" << std::endl;
	std::cout << "|            �����߼�����           |" << std::endl;
	std::cout << "|  Propositional Logical Inference  |" << std::endl;
	std::cout << "+-----------------------------------+" << std::endl<< std::endl;

	std::cout << "��������" << std::endl;
	std::cout << "����1:ӪҵԱA��B͵���ֱ�" << std::endl;
	std::cout << "����2:��A����������������Ӫҵʱ��" << std::endl;
	std::cout << "����3:��B�ṩ��֤����ȷ�������δ����" << std::endl;
	std::cout << "����4:��B�ṩ��֤�ݲ���ȷ��������������Ӫҵʱ��" << std::endl;
	std::cout << "����5:����������" << std::endl<< std::endl;

	std::cout << "�����Ԫ����" << std::endl;
	std::cout << "����A:ӪҵԱA͵���ֱ�" << std::endl;
	std::cout << "����B:ӪҵԱB͵���ֱ�" << std::endl;
	std::cout << "����C:��������Ӫҵʱ��" << std::endl;
	std::cout << "����D:B�ṩ��֤����ȷ" << std::endl;
	std::cout << "����E:����δ����" << std::endl<< std::endl;

	bool A, B, C, D, E;
	for (int i = 0; i < pow(2, 5); i++) {
		A = i & 0b1 ;
		B = i & 0b10 ;
		C = i & 0b100 ;
		D = i & 0b1000 ;
		E = i & 0b10000 ;
		if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E) {
			std::cout << "�����߼�������:" << std::endl;
			std::cout << "A = " << (A ? "1" : "0") << " B = " << (B ? "1" : "0") << std::endl;
			std::cout << "������" << (A ? "A" : "B") << "͵���ֱ�" << std::endl<< std::endl;
		}
	}

	std::cout << "�����߼��������" << std::endl;
	system("pause");
	return 0;
}