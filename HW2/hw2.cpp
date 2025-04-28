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
	std::cout << "|            命题逻辑推理           |" << std::endl;
	std::cout << "|  Propositional Logical Inference  |" << std::endl;
	std::cout << "+-----------------------------------+" << std::endl<< std::endl;

	std::cout << "命题描述" << std::endl;
	std::cout << "命题1:营业员A或B偷了手表" << std::endl;
	std::cout << "命题2:若A作案，则作案不在营业时间" << std::endl;
	std::cout << "命题3:若B提供的证据正确，则货柜未上锁" << std::endl;
	std::cout << "命题4:若B提供的证据不正确，则作案发生在营业时间" << std::endl;
	std::cout << "命题5:货柜上了锁" << std::endl<< std::endl;

	std::cout << "命题变元描述" << std::endl;
	std::cout << "命题A:营业员A偷了手表" << std::endl;
	std::cout << "命题B:营业员B偷了手表" << std::endl;
	std::cout << "命题C:作案不在营业时间" << std::endl;
	std::cout << "命题D:B提供的证据正确" << std::endl;
	std::cout << "命题E:货柜未上锁" << std::endl<< std::endl;

	bool A, B, C, D, E;
	for (int i = 0; i < pow(2, 5); i++) {
		A = i & 0b1 ;
		B = i & 0b10 ;
		C = i & 0b100 ;
		D = i & 0b1000 ;
		E = i & 0b10000 ;
		if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E) {
			std::cout << "命题逻辑推理结果:" << std::endl;
			std::cout << "A = " << (A ? "1" : "0") << " B = " << (B ? "1" : "0") << std::endl;
			std::cout << "所以是" << (A ? "A" : "B") << "偷了手表" << std::endl<< std::endl;
		}
	}

	std::cout << "命题逻辑推理结束" << std::endl;
	system("pause");
	return 0;
}