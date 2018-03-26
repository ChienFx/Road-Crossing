#include <iostream>
#include <Windows.h>
#include <conio.h>
// Hàm tô màu.
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void main(){

	/*for (int i = 1; i <= 256; i++){
		textcolor(i);
		std::cout << "Text Color: "<< i << std::endl;
		
	}*/
	int c = -1;
	while (c != 'l')
	{
		c = _getch();
		std::cout << int(c)<<std::endl;
	}
	
}