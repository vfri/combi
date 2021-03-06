// combi13.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

static int n = 10;
static int k = 5;

void PrintCombination(std::vector<int>& comB)
{
	if (comB.size() != 0)
	{
		for (auto i = 0; i < comB.size(); ++i)
		{
			std::cout << comB[i] << " ";
		}
		std::cout << std::endl;
	}
}

bool NextExists(std::vector<int>& comB)
{
	if (n < 2)
	{
		return false;
	}

	if (comB[k - 1] != n - 1)
	{
		comB[k - 1]++;
	}
	else
	{
		int i = k - 2;
		while ((comB[i + 1] - comB[i] == 1))
		{
			i--;
			if (i < 0)
			{
				return false;
			}
		}
		comB[i]++;
		for (auto j = i + 1; j < k; j++)
		{
			comB[j] = comB[j - 1] + 1;
		}
	}

	return true;
}

int main()
{
	std::vector<int> comB(k);
	
	for (auto i = 0; i < k; ++i) // инициализация сочетания
	{
		comB[i] = i;
	}

	PrintCombination(comB);
	int amount = 1;

	while (NextExists(comB))
	{
		PrintCombination(comB);
		amount++;
	}
	std::cout << amount << " combinations are found" << std::endl;

	return 0;
}

