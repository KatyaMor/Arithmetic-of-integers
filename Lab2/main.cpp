#include "LongNum.h"
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
	LongNum A = LongNum("1017727583");//prime
	LongNum B = LongNum("234645654647");
	LongNum C;
	LongNum D = LongNum("238805354965344028201");
	cout << "\t\t --Karatsuba--\n\n";
	A.write(); cout << " * "; B.write(); cout << " = ";
	C = A.karatsuba(B);
	D = D - C;
	C.write();
	cout << endl;
	cout << "Wolfram Alpha - My Karatsuba = ";
	D.write();
	cout << endl;

	LongNum F = LongNum("182521213001");//prime
	LongNum G = LongNum("34567897654324567");
	cout << "\n\t\t --ToomCook--\n\n";
	F.write(); cout << " * "; G.write(); cout << " = ";
	C = F.Toom3(G);
	D = LongNum("6309374610761742562194095567");
	D = D - C;
	C.write();
	cout << endl;
	cout << "Wolfram Alpha - My ToomCook = ";
	D.write();
	cout << endl;

	B = LongNum("3456786543766");
	G = LongNum("77746402334");
	//D = LongNum("268752717414388735549844");
	cout << "\n\t\t --Strassen--\n\n";
	B.write(); cout << " * "; G.write(); cout << " = ";
	C = B.Strassen(G);
	//D = D - C;
	C.write();
	/*cout << endl;
	cout << "Wolfram Alpha - My Strassen = ";
	D.write();*/
	cout << endl;

	B = LongNum("3456786543766");
	G = LongNum("77746402334");
	//D = LongNum("13717146803833333196161865295");
	cout << "\n\t\t --Shoenhage--\n\n";
	B.write(); cout << " * "; G.write(); cout << " = ";
	D = B.Shoenhage(G);
	D.write();
	D = D - C;
	cout << endl;
	cout << "Strassen - My Shoenhage = ";
	D.write();
	cout << endl;

	/*std::string s;
	cout << "\n\t\t --RabinMiller-- \n";
	if (A.prime_RabinMiller())
		s = " is prime.";
	else s = " isn/'t prime.";
	cout << "Number ";
	A.write();
	cout << s << endl;

	cout << "\n\t\t --Lemman-- \n";
	if (F.prime_Lemman())
		s = " is prime.";
	else s = " isn/'t prime.";
	cout << "Number ";
	F.write();
	cout << s << endl;*/

	system("pause");
	return 0;
}