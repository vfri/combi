// combi14.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

						// размещения без повторений из n по m (элементы от 0 до n - 1)
static int n = 12; 
static int m = 6;

void PrintAllocation(std::vector<int>& alloC)
{
	if (alloC.size() != 0)
	{
		for (unsigned int i = 0; i < alloC.size(); ++i)
		{
			std::cout << alloC[i] << " ";
		}
		std::cout << std::endl;
	}
}

bool NextPermutation(std::vector<int>& prmT)
{
	bool result = true;

	if (m < 2)
	{
		return false;
	}

	int k = m - 2;					// номер элемента, который можно переставить
	while (prmT[k] > prmT[k + 1])
	{
		k--;
		if (k < 0) break;
	}
	if (k >= 0) // следующая перестановка существует
	{
		int temp = k + 1;
		while ((temp < m - 1) && (prmT[temp + 1]) > prmT[k])
		{
			temp++;
		}
		std::swap(prmT[k], prmT[temp]);
		for (int i = k + 1; i <= (k + m) / 2; i++)
		{
			std::swap(prmT[i], prmT[m + k - i]);
		}
	}
	else
	{
		result = false;
	}
	return result;
}

bool NextCombination(std::vector<int>& comB)
{
	if (n < 2)
	{
		return false;
	}

	if (comB[m - 1] != n - 1)
	{
		comB[m - 1]++;
	}
	else
	{
		int i = m - 2;
		while ((comB[i + 1] - comB[i] == 1))
		{
			i--;
			if (i < 0)
			{
				return false;
			}
		}
		comB[i]++;
		for (int j = i + 1; j < m; j++)
		{
			comB[j] = comB[j - 1] + 1;
		}
	}

	return true;
}

bool NextAllocation(std::vector<int>& alloC)
{
	std::vector<int> newSet(m);

	if (NextPermutation(alloC))
	{
		return true;
	}
	else
	{
		std::reverse(alloC.begin(), alloC.end());
		return NextCombination(alloC);
	}
}


int main()
{
	std::vector<int> alloC(m);

	for (unsigned int i = 0; i < alloC.size(); ++i)
	{
		alloC[i] = i;
	}

	PrintAllocation(alloC);
	int allocNum = 1; // число найденных перестановок

	while (NextAllocation(alloC))
	{
		PrintAllocation(alloC);
		allocNum++;
	}

	std::cout << allocNum << " allocations were found" << std::endl;

	return 0;
}

