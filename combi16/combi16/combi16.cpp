// combi16.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

static const int n = 20;	// количество предметов на выбор
static const int M = 80; // ограничение на суммарную массу набора


bool InputData(const std::string& dataFileName, std::vector<int>& mass, std::vector<int>& cost)
{
	bool success = true;
	std::ifstream inputFile;
	inputFile.open(dataFileName);
	if (inputFile.is_open())
	{
		int i = 0;
		while ((i < n) && (inputFile >> mass[i] >> cost[i]))
		{
			std::cout << "Mass " << mass[i] << " with cost " << cost[i] << std::endl;
			i++;
		}
		success = (i == n) ? true : false;
	}
	else
	{
		std::cout << "Input file is absent!" << std::endl;
		success = false;
	}
	return success;
}

bool NextSet(std::bitset<n>& setMark) // следующий набор битов
{
	if (!setMark.all())
	{
		unsigned long long int ruler = setMark.to_ullong();
		ruler++;
		std::bitset<n> setMarkNew(ruler);
		setMark = setMarkNew;
		return true;
	}
	return false;
}

int AmountCost(const std::vector<int>& mass, const std::vector<int>& cost, const std::bitset<n>& setMark)
{
	int sumMass = 0;
	int result = 0;
	size_t i = 0;
	while ((sumMass <= M) && (i < n))
	{
		sumMass += mass[i] * setMark[i];
		result += cost[i] * setMark[i];
		++i;
	}
	return result;
}

void PrintSubSet(const std::vector<int>& mass, const std::vector<int>& cost, const std::bitset<n>& subSet)
{
	int sumMass = 0;
	for (size_t i = 0; i < n; ++i)
	{
		if (subSet[i])
		{
			std::cout << "mass " << mass[i] << ", cost " << cost[i] << std::endl;
			sumMass += mass[i];
		}
	}
	std::cout << "Overall mass is " << sumMass << std::endl;
}



int main(int argc, char* argv[])
{
	std::cout << "Maximal overall cost for several things of overall weight not greater than " << M << std::endl;
	
	std::string dataFileName;
	
	if (argc > 1)
	{
		dataFileName = argv[1];
	}
	else
	{
		std::cout << "No input file!" << std::endl;
		return 1;
	}

	std::vector<int> mass(n);
	std::vector<int> cost(n);
	int maxAmount = 0;

	unsigned long long int ruler = 0;
	std::bitset<n> subSet;
	std::cout << ruler << std::endl;

	if (InputData(dataFileName, mass, cost))
	{
		std::bitset<n> bestSet;
		while (NextSet(subSet))
		{
			int currAmount = AmountCost(mass, cost, subSet);
			if (currAmount > maxAmount)
			{
				maxAmount = currAmount;
				bestSet = subSet;
			}
		}
		std::cout << "maxAmount " << maxAmount << " is reached on " << std::endl;
		PrintSubSet(mass, cost, bestSet);
	}

	return 0;
}

