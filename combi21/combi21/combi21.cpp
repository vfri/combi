// combi21.cpp: определяет точку входа для консольного приложения.
//	поиск точек сочленения и мостов неориентированного графа

#include "stdafx.h"

static const int MAXV = 401;

struct Graph
{
	int numVert = 0;
	int numChilds[MAXV];
	std::vector<int> neighbours[MAXV];
	bool used[MAXV];
	int enTime[MAXV];
	int estimate[MAXV];
};

void ReadGraph(const std::string& graphFileName, Graph& graph)
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
		graph.enTime[i] = 0;
		graph.estimate[i] = 0;
	}
	
	for (int i = 1; i <= numEdges; ++i)
	{
		int vert1, vert2;
		graphFile >> vert1 >> vert2;
		graph.neighbours[vert1].push_back(vert2);
		graph.neighbours[vert2].push_back(vert1);
		graph.numChilds[vert1]++;
		graph.numChilds[vert2]++;
	}
	
}

void PrintGraph(const Graph& graph)
{
	std::cout << "Graph on " << graph.numVert << " vertices." << std::endl;
	for (int i = 1; i <= graph.numVert; ++i)
	{
		std::cout << "Vertex [" << i << "] of degree " << graph.numChilds[i] << ". Neighbours are: ";
		for (int j = 0; j < graph.numChilds[i]; ++j)
		{
			std::cout << graph.neighbours[i][j] << " ";
		}
		std::cout << std::endl;
	}
}



void DepthFirstSearch(Graph& graph, int& time, const int currVert, const int parentVert = - 1)  
{	// от вершины currVert с предшествующей по дереву parentVert, текущее время time
	graph.used[currVert] = true;
	graph.enTime[currVert] = time;
	graph.estimate[currVert] = time;
	time++;
		
	int newChildren = 0;
	for (size_t i = 0; i < graph.neighbours[currVert].size(); ++i) 
	{
		int neiVert = graph.neighbours[currVert][i];
		if (neiVert == parentVert) continue;
		if (graph.used[neiVert])
		{
			graph.estimate[currVert] = (graph.estimate[currVert] < graph.enTime[neiVert]) ?
				graph.estimate[currVert] : graph.enTime[neiVert];
		}
		else 
		{
			DepthFirstSearch(graph, time, neiVert, currVert);
			graph.estimate[currVert] = (graph.estimate[currVert] < graph.estimate[neiVert]) ?
				graph.estimate[currVert] : graph.estimate[neiVert];
			if ((graph.estimate[neiVert] >= graph.enTime[currVert]) && (parentVert != -1))
			{
				std::cout << "[" << currVert << "] is cutpoint" << std::endl;
			}
			if (graph.estimate[neiVert] > graph.enTime[currVert])
			{
				std::cout << "[" << currVert << "]-[" << neiVert << "] is a bridge" << std::endl;
			}
			++newChildren;
		}
	}
	if ((parentVert == -1) && (newChildren > 1))
	{
		std::cout << "[" << currVert << "] is cutpoint" << std::endl;
	}
}


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Graph file expected!" << std::endl;
		return 1;
	}
	else
	{
		std::string graphFileName(argv[1]);
		Graph graph;
		ReadGraph(graphFileName, graph);
		PrintGraph(graph);

		int time = 0;
		DepthFirstSearch(graph, time, 1);
	}
	
	return 0;
}

