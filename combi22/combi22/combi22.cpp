// combi22.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


static const int MAXV = 401;

struct OrGraph
{
	int numVert = 0;
	int numChilds[MAXV];
	std::vector<int> neighbours[MAXV];
	bool used[MAXV];
};

void ReadGraph(const std::string& graphFileName, OrGraph& graph)
{
	std::ifstream graphFile(graphFileName);
	int numEdges = 0;
	int numVert = 0;
	graphFile >> numVert >> numEdges;
	graph.numVert = numVert;

	for (int i = 1; i <= numVert; ++i)
	{
		graph.numChilds[i] = 0;
		graph.used[i] = false;
	}

	for (int i = 1; i <= numEdges; ++i)
	{
		int vert1, vert2;
		graphFile >> vert1 >> vert2;
		graph.neighbours[vert1].push_back(vert2);
		graph.numChilds[vert1]++;
	}

}

void MakeReverseGraph(const OrGraph& graph, OrGraph& revGraph)
{
	revGraph.numVert = graph.numVert;
	for (size_t i = 1; i <= revGraph.numVert; ++i)
	{
		revGraph.numChilds[i] = 0;
		revGraph.used[i] = false;
	}
	
	for (size_t i = 1; i <= graph.numVert; ++i)
	{
		for (size_t j = 0; j < graph.numChilds[i]; ++j)
		{
			revGraph.neighbours[graph.neighbours[i][j]].push_back(i);
			revGraph.numChilds[graph.neighbours[i][j]]++;
		}
	}
}

void PrintOrGraph(const OrGraph& graph)
{
	std::cout << "Graph on " << graph.numVert << " vertices." << std::endl;
	for (int i = 1; i <= graph.numVert; ++i)
	{
		std::cout << "Vertex [" << i << "] of degree " << graph.numChilds[i] << ". Arcs to vertices: ";
		for (int j = 0; j < graph.numChilds[i]; ++j)
		{
			std::cout << graph.neighbours[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void AddOrder(OrGraph& graph, const int currVert, std::vector<int>& timeOrder)
{	// определяет очередную вершину в порядке покидания вершин при обходе в глубину (timeOrder)
	graph.used[currVert] = true;
	
	for (size_t i = 0; i < graph.neighbours[currVert].size(); ++i)
	{
		if (!graph.used[graph.neighbours[currVert][i]])
		{
			AddOrder(graph, graph.neighbours[currVert][i], timeOrder);
		}
	}
	timeOrder.push_back(currVert);
}

void MakeOrder(OrGraph& graph, std::vector<int>& timeOrder)
{
	for (size_t i = 1; i <= graph.numVert; ++i)
	{
		if (!graph.used[i])
		{
			AddOrder(graph, i, timeOrder);
		}
	}
}

void AddComponent(OrGraph& graph, const int currVert, std::vector<int>& componenta)
{	// заполняет компоненты связности (componenta)
	graph.used[currVert] = true;
	componenta.push_back(currVert);
	for (size_t i = 0; i < graph.neighbours[currVert].size(); ++i)
	{
		if (!graph.used[graph.neighbours[currVert][i]])
		{
			AddComponent(graph, graph.neighbours[currVert][i], componenta);
		}
	}
}

void MakeComponenta(OrGraph& graph, std::vector<int>& timeOrder, std::vector<int>& componenta)
{
	for (size_t i = 1; i <= graph.numVert; ++i)
	{
		int currVert = timeOrder[graph.numVert - i];
		if (!graph.used[currVert])
		{
			AddComponent(graph, currVert, componenta);
			std::cout << "Component is: ";
			std::copy(componenta.begin(), componenta.end(), std::ostream_iterator<int>(std::cout, " "));
			std::cout << std::endl;
			componenta.clear();
		}
	}
}



int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Graph file expected!" << std::endl;
	}
	else
	{
		std::string graphFileName(argv[1]);
		OrGraph orGraph;
		ReadGraph(graphFileName, orGraph);
		PrintOrGraph(orGraph);
		OrGraph revGraph;
		MakeReverseGraph(orGraph, revGraph);
		PrintOrGraph(revGraph);
		std::vector<int> timeOrder;
		MakeOrder(orGraph, timeOrder);
		std::vector<int> componenta;
		MakeComponenta(revGraph, timeOrder, componenta);
	}
		
	return 0;
}

