#include <iostream>
#include "interpreter.h"
int main()
{
	if (!interpretMnimocode()) {
		std::cout << "Ошибка при интерпретации мнимокода\n";
		return 1;
	}    
	//std::cout << "Интерпретация мнимокода завершена успешно\n";
	return 0;
}
