//Сделано: RedFoxMain
//Github https://github.com/RedFoxMain

//По умолчанию мод отладки отключён
//#define DEBUGMOD

#include <iostream>
#include <stack>


struct SymbolType
{
	char type;
	float value;
};

//приоритет операторов
int priority(char symbol)
{
	if (symbol == '-' || symbol == '+')
	{
		return 1;
	}
	if (symbol == '*' || symbol == '/')
	{
		return 2;
	}
	if (symbol == '^')
	{
		return 3;
	}
	else
	{
		return 0;
	}
}

// логика операторов
bool Compute(std::stack<SymbolType> &num_stack, std::stack<SymbolType> &oper_stack, SymbolType &symbolType)
{
	float firstN, secondN, result;
	char operation;
	firstN = num_stack.top().value;
	num_stack.pop();
	operation = oper_stack.top().type;
	switch (operation)
	{
	case '+':
		secondN = num_stack.top().value;
		num_stack.pop();
		result = firstN + secondN;
		symbolType.type = '0';
		symbolType.value = result;
		num_stack.push(symbolType);

		break;

	case '-':
		secondN = num_stack.top().value;
		num_stack.pop();
		result = secondN - firstN;
		symbolType.type = '0';
		symbolType.value = result;
		num_stack.push(symbolType);
		break;

	case '/':
		secondN = num_stack.top().value;
		if (firstN == 0)
		{
			std::cout << "На 0 делить нельщя!" << std::endl;
			return false;
		}
		else
		{
			num_stack.pop();
			result = secondN / firstN;
			symbolType.type = '0';
			symbolType.value = result;
			num_stack.push(symbolType);
			break;
		}

	case '*':
		secondN = num_stack.top().value;
		num_stack.pop();
		result = firstN * secondN;
		symbolType.type = '0';
		symbolType.value = result;
		num_stack.push(symbolType);
		break;

	case '^':
		secondN = num_stack.top().value;
		num_stack.pop();
		result = pow(secondN, firstN);
		symbolType.type = '0';
		symbolType.value = result;
		num_stack.push(symbolType);

		break;

	default:
		std::cout << "Ошибка" << std::endl;
		return false;
	}
	oper_stack.pop();
	return true;
}

int main(int argc, char *argv[])
{
	char number, operation;
	float value;
	bool isUnaryMinus = true;

	std::stack<SymbolType> num_stack;
	std::stack<SymbolType> oper_stack;
	SymbolType symbolType;
	std::cout << "Добро пожаловать в калькулятор!\nОн поддерживает операции + - / * ^ ()" << std::endl;
	std::cout << std::endl;
	std::cout << "Введите выражение: ";
	while (true)
	{
		number = std::cin.peek();
		if (number == '\n')
		{
			break;
		}
		if (number == ' ')
		{
			std::cin.ignore();
			continue;
		}
		// Ввод цифр и проверка на унарный минус
		else if (number >= '0' && number <= '9' || number == '-' && isUnaryMinus == true)
		{
			std::cin >> value;
			symbolType.type = '0';
			symbolType.value = value;
			num_stack.push(symbolType);
			isUnaryMinus = false;
			continue;
		}

		// проверка операции
		else if (number == '+' || (number == '-' && isUnaryMinus == false) || number == '*' || number == '/' || number == '^')
		{
			while (oper_stack.size() != 0 && priority(number) <= priority(oper_stack.top().type))
			{
				if (Compute(num_stack, oper_stack, symbolType) == false)
				{
					system("pause");
					return 0;
				}
			}
			symbolType.type = number;
			symbolType.value = 0;
			oper_stack.push(symbolType);
			std::cin.ignore();
			continue;
			{
			}
		}
		// действия со скобками
		if (number == '(')
		{
			symbolType.type = number;
			symbolType.value = 0;
			oper_stack.push(symbolType);
			std::cin.ignore();
			continue;
		}
		if (number == ')')
		{
			while (oper_stack.top().type != '(')
			{
				if (Compute(num_stack, oper_stack, symbolType) == false)
				{
					system("pause");
					return 0;
				}
				else
				{
					continue;
				}
			}
			oper_stack.pop();
			std::cin.ignore();
			continue;
		}
		else
		{
			std::cout << "Неверное выражение" << std::endl;
			break;
		}
	}
	// читаем и выводим результат
	while (oper_stack.size() != 0)
	{
		if (Compute(num_stack, oper_stack, symbolType) == false)
		{
			system("pause");
			return 0;
		}
		else
		{
			continue;
		}
	}
	std::cout << "Результат: " << num_stack.top().value << std::endl;

//результат для разработчика
#ifdef DEBUGMOD
	std::cout << "Количество цифр в стэке: " << num_stack.size() << std::endl;
	std::cout << "Количество операторов в стэке: " << oper_stack.size() << std::endl;
#endif
}