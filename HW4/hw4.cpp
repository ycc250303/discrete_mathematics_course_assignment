#include<iostream>
#include <vector>
#include<limits>
#include<conio.h>
#include<algorithm>

#define MAX_VERTEX_NUM 26
#define MAX_COST INT_MAX
#define MEMORY_ALLOCATION_ERROR -1
#define INVAVID_PARENT_NODE -1

/*
 * Function Name:   inputInteger
 * Function:        input an integer within a range
 * Input Parameters:int minNum
 *                  int maxNum
 *                  const char* prompt
 * Return Value:    int
 */
int inputInteger(int minNum, int maxNum, const char* prompt = "") {
	
	double num;
	while (true) {
		if (prompt != "")
			std::cout << "������" << prompt << "[��Χ" << minNum << "-" << maxNum << "]:";
		std::cin >> num;
		if (std::cin.fail()||static_cast<int>(num)!= num|| num < minNum || num > maxNum) {
			std::cout << "����Ƿ�,����������!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			return num;
	}
}

/*define the Edge struct*/
struct Edge {
	int start;
	int end;
	int weight;
	bool operator<(const Edge& other) const {
		return this->weight < other.weight;
	}
};

/*define the MininumSpanningTree class*/
class MininumSpanningTree {
private:
	int** costMatrix;
	int vertexNum;
	int minTotalCost;
	std::vector<Edge> edges;
	std::vector<int>parents;
	std::vector<int> heights;
	int findSet(int v);
	void mergeSet(int v1, int v2);
public:
	MininumSpanningTree(const int v);
	~MininumSpanningTree();
	bool insertEdge(const int v1, const int v2, const int cost);
	void Kruskal();
	int getMinTotalCost();
};

/*
 * Function Name:   findSet
 * Function:        find the root of the set that v belongs to
 * Input Parameters:int v
 * Return Value:    int
 */
int MininumSpanningTree::findSet(int v) {
	if (parents[v] < 0)
		return v;
	else
		findSet(parents[v]);
}

/*
 * Function Name:   mergeSet
 * Function:        merge two sets that v1 and v2 belong to
 * Input Parameters:int v1
 *                  int v2
 * Return Value:    void
 */
void MininumSpanningTree::mergeSet(int v1, int v2) {
	int root1 = findSet(v1), root2 = findSet(v2);
	if (heights[root1] > heights[root2])
		parents[root2] = root1;
	else if (heights[root1] < heights[root2])
		parents[root1] = root2;
	else if (parents[root1] == parents[root2]) {
		parents[root2] = root1;
		heights[root1]++;
	}
}

/*
 * Function Name:   MininumSpanningTree
 * Function:        the constructor of the MininumSpanningTree class
 * Input Parameters:int V
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
MininumSpanningTree::MininumSpanningTree(const int v) {
	/*cost matrix initialization*/
	vertexNum = v;
	minTotalCost = 0;
	parents.resize(vertexNum, INVAVID_PARENT_NODE);
	costMatrix = new(std::nothrow) int* [vertexNum];
	if (costMatrix == NULL) {
		std::cerr << "Error: Memory allocation failed." << std::endl;
		exit(MEMORY_ALLOCATION_ERROR);
	}
	for (int i = 0; i < vertexNum; i++) {
		costMatrix[i] = new(std::nothrow) int[vertexNum];
		if (costMatrix[i] == NULL) {
			std::cerr << "Error: Memory allocation failed." << std::endl;
			exit(MEMORY_ALLOCATION_ERROR);
		}
		for (int j = 0; j < vertexNum; j++) {
			costMatrix[i][j] = 0;
		}
	}

	std::cout << std::endl;
	std::cout << ">>> ����ͨ�ŵ�·���ڵ�";
	for (int i = 0; i < vertexNum; i++) {
		std::cout << static_cast<char>(i + 'A') << " ";
		
	}
	std::cout << "�����ɹ�!" << std::endl << std::endl;

	/*input edge distance*/
	std::cout << ">>> ������������ڵ�֮��ľ���,û��·����������" << MAX_COST << std::endl;
	for (size_t i = 0; i < vertexNum; i++) {
		for (size_t j = i + 1; j < vertexNum; j++) {
			std::cout << "���������ͨ�����ڵ�" << static_cast<char>(i + 'A') << "��" << static_cast<char>(j + 'A')
				<< "�ıߵľ���[������Χ1-" << MAX_COST << "]:";
			int cost = inputInteger(1, MAX_COST);
			insertEdge(i, j, cost);
		}
	}
}

/*
 * Function Name:   ~MininumSpanningTree
 * Function:        the destructor of the MininumSpanningTree class
 * Input Parameters:void
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
MininumSpanningTree::~MininumSpanningTree() {
	for (int i = 0; i < vertexNum; i++) {
		delete[] costMatrix[i];
	}
	delete[] costMatrix;
}
/*
 * Function Name:   insertEdge
 * Function:        insert an edge into the cost matrix
 * Input Parameters:const int v1
 *                  const int v2
 *                  const int cost
 * Return Value:    true / false
 * Notes:           Class external implementation of member functions
 */
bool MininumSpanningTree::insertEdge(const int v1, const int v2, const int cost) {
	if (v1 < 0 || v1 >= vertexNum || v2 < 0 || v2 >= vertexNum || cost < 0 || cost > MAX_COST) {
		return false;
	}
	costMatrix[v1][v2] = costMatrix[v2][v1] = cost;
	edges.push_back({ v1,v2,cost });
	return true;
}

/*
 * Function Name:   Kruskal
 * Function:        create the minimal spanning tree using Kruskal algorithm
 * Input Parameters:void
 * Return Value:    void
 * Notes:           Class external implementation of member functions
 */
void MininumSpanningTree::Kruskal() {
	/* Initialize the parents and heights of each vertex to -1 and 0 respectively */
	parents.resize(vertexNum,INVAVID_PARENT_NODE);
	heights.resize(vertexNum, 0);

	/* Sort the edges by weight */
	std::sort(edges.begin(), edges.end());
	int count = 0;
	std::vector<Edge>results;

	/* Iterate through the edges and add the edge to the MST if it does not form a cycle */
	for (const auto& edge : edges) {
		int x = findSet(edge.start);
		int y = findSet(edge.end);
		if (x != y) {
			results.push_back(edge);
			mergeSet(x, y);
			count++;
			if (count == vertexNum - 1)
				break;
		}
	}
	
	/* Output the MST */
	std::cout << std::endl<<">>> ������С Kruskal ������:" << std::endl;
	for (const auto& result : results) {
		std::cout << static_cast<char>(result.start + 'A') << "-<" << result.weight << ">-" << static_cast<char>(result.end + 'A') << std::endl;
		minTotalCost += result.weight;
	}
}

/*
 * Function Name:   getMinTotalCost
 * Function:        get the total cost of the minimal spanning tree
 * Input Parameters:void
 * Return Value:    int
 * Notes:           Class external implementation of member functions
 */
int MininumSpanningTree::getMinTotalCost() {
	return minTotalCost;
}

/*
 * Function Name:	inputLogicalValue
 * Function:		input a logical value from user
 * Input Parameters:char FalseValue = '0'
 *					char TrueValue = '1'
 * Return Value:	true / false
 */
bool inputLogicalValue(char FalseValue = '0', char TrueValue = '1')
{
	while (true) {
		char InputChar = _getch();
		if (InputChar == 0 || InputChar == -32)
			InputChar = _getch();
		else if (InputChar == FalseValue || InputChar == TrueValue) {
			std::cout << InputChar << std::endl << std::endl;
			return InputChar == TrueValue;
		}
	}
}


/*
 * Function Name:   makeChoice
 * Function:        choose the start node
 * Input Parameters:const char* prompt
 *                  int vertexNum
 * Return Value:    int
 */
int makeChoice(const char* prompt, int vertexNum)
{
	std::cout << prompt;
	while (true) {
		char choice = _getch();;
		if (choice == 0 || choice == 32)
			choice = _getch();
		if ('A' <= choice && choice <= static_cast<char>(vertexNum + 'A' - 1)) {
			std::cout << " [" << choice << "]" << std::endl << std::endl;
			return choice;
		}
	}
}

/*
 * Function Name:   main
 * Function:        the main function of the program
 * Return Value:    int
 */
int main() {
	do {
		/*output the title*/
		system("cls");
		std::cout << "+-----------------------+" << std::endl;
		std::cout << "|      ��С������       |" << std::endl;
		std::cout << "| Minimum Spanning Tree |" << std::endl;
		std::cout << "+-----------------------+" << std::endl;

		/*input the number of vertices*/
		int vertexNum = inputInteger(2, MAX_VERTEX_NUM, "����ͨ�����ڵ���");
		MininumSpanningTree mininumSpanningTree(vertexNum);

		/*create minimal spanning tree*/
		mininumSpanningTree.Kruskal();

		std::cout << ">>> Kruskal ��С����������Ȩ��Ϊ " << mininumSpanningTree.getMinTotalCost() << std::endl << std::endl;

		std::cout << "�Ƿ��˳����� [y/n]: ";
	} while (!inputLogicalValue('n', 'y'));
	/*wait for user input to quit*/
	

	return 0;
}