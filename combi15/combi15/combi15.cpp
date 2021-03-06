// combi15.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

static const int n = 20;


int main()
{
	std::vector<int> result(0);
	std::vector<int> choise(n);
	
	for (int i = 0; i < n; ++i)
	{
		choise[i] = i;
	}

	srand(time(NULL));

	for (int j = n; j > 0; j--)
	{
		int nextElem = rand() % j;
		result.push_back(choise[nextElem]);
		choise.erase(choise.begin() + nextElem);
	}

	for (int j = 0; j < result.size(); ++j)
	{
		std::cout << result[j] << " ";
	}
	std::cout << std::endl;
	
	return 0;
}

