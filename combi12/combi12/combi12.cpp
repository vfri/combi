// combi12.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

static int n = 6;

void PrintPermutation(std::vector<int>& prmT)
{
	if (prmT.size() != 0)
	{
		for (auto i = 0; i < prmT.size(); ++i)
		{
			std::cout << prmT[i] << " ";
		}
		std::cout << std::endl;
	}
}

bool NextPermutation(std::vector<int>& prmT)
{
	bool result = true;

	if (n < 2)
	{
		return false;
	}
	
	int k = n - 2;					// номер элемента, который можно переставить
	while (prmT[k] > prmT[k + 1])
	{
		k--;
		if (k < 0) break;
	}
	if (k >= 0) // следующая перестановка существует
	{ 
		int temp = k + 1;
		while ((temp < n - 1) && (prmT[temp + 1]) > prmT[k])
		{
			temp++;
		}
		std::swap(prmT[k], prmT[temp]);
		for (auto i = k + 1; i <= (k + n) / 2; i++)
		{
			std::swap(prmT[i], prmT[n + k - i]);
		}
	}
	else
	{
		result = false;
	}
	return result;
}


int main()
{
	std::vector<int> prmT(n);
	
	for (auto i = 0; i < prmT.size(); ++i)
	{
		prmT[i] = i;
	}

	PrintPermutation(prmT);
	int permuNum = 1; // число найденных перестановок

	while (NextPermutation(prmT))
	{
		PrintPermutation(prmT);
		permuNum++;
	}

	std::cout << permuNum << " permutations were found" << std::endl;

	return 0;
}

