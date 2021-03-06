// combi11.cpp: определяет точку входа для консольного приложения.
// Перечисление всех перестановок. Соседние перестановки получаются друг из друга 
// транспозицией двух элементов

#include "stdafx.h"

static int n = 9; // длина перестановки

void PrintPermutation(std::vector<int> prm)
{
	if (prm.size() == 0)
	{
		std::cout << "Empty data!\n";
	}
	else
	{
		for (unsigned int i = 0; i < prm.size(); ++i)
		{
			std::cout << prm[i] << " ";
		}
		std::cout << std::endl;
	}
}

void Transpose(std::vector<int>& prmT, std::vector<int>& invPrmT,
	std::vector<int>& diagram, std::vector<int>& direction, bool& canTranspose)
{
	int i = n - 1;
	while ((i > 0) && (((direction[i] == 1) && (diagram[i] == i)) || ((direction[i] == -1) && (diagram[i] == 0))))
	{
		i--;
	}
	canTranspose = (i > 0);
	if (canTranspose)
	{
		diagram[i] += direction[i];
		for (int j = i + 1; j < n; ++j)
		{
			direction[j] = - direction[j];
		}
		int sbstPos1 = invPrmT[i];
		int sbstVal1 = i;
		int sbstPos2 = sbstPos1 + direction[i];
		int sbstVal2 = prmT[sbstPos2];			// будем менять местами i и соседний с ним sbstVаl2
		std::swap(prmT[sbstPos1], prmT[sbstPos2]);
		std::swap(invPrmT[sbstVal1], invPrmT[sbstVal2]);
	}
}


int main()
{
	//time_t tBegin, tEnd;
		
	std::vector<int> prmT(n);		// перестановка
	std::vector<int> invPrmT(n);	// обратное для перестановки отображение
	std::vector<int> diagram(n);	// диаграмный счетчик процесса
	std::vector<int> direction(n);	// направление перемещения элементов

	
	for (int i = 0; i < n; ++i)	// инициализация
	{
		prmT[i] = n - 1 - i;
		invPrmT[i] = n - 1 - i;
		diagram[i] = 0;
		direction[i] = 1;
	}
	
	PrintPermutation(prmT);

	//time(&tBegin);

	long long linearCounter = 1;
	bool canTranspose = true;
	while (canTranspose)
	{
		Transpose(prmT, invPrmT, diagram, direction, canTranspose);
		if (canTranspose)
		{
			// PrintPermutation(prmT);
			linearCounter++;
		}
	}
	PrintPermutation(prmT);

	//time(&tEnd);

	std::cout << linearCounter << " permutations are found" << std::endl;
	//std::cout << "Executing time " << static_cast<int>(difftime(tEnd, tBegin)) << " seconds" << std::endl;
	
	return 0;
}

