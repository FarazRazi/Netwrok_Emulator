#pragma once
//Header
#include <iostream>
#include "Header.h"
#include <fstream>
#include "string"
#include <sstream>
#include <ctime>
#include <conio.h>
using namespace std;

//size of binary heap is fixed "10"
const int Cap = 10;
//Delay
int delay(int milliseconds) {
	clock_t goal = milliseconds + clock();
	while (goal > clock());
	return 1;
}
template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;

	void setData(T data)
	{
		this->data = data;
	}
	void setNext(Node* next)
	{
		this->next = next;
	}
	T getData()
	{
		return this->data;
	}
	Node* getNext()
	{
		return this->next;
	}

};

template <typename T>
class adjacencyList
{
public:
	Node<T>* head;
	adjacencyList()
	{
		head = NULL;
	}

	void insert(T data)
	{
		Node<T>* newNode = new Node<T>;
		newNode->data = data;

		newNode->next = NULL;

		if (isEmpty())
			head = newNode;
		else
		{
			Node<T>* temp = head;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}

	void display()
	{
		Node<T>* curr = new Node<T>;
		curr = head;
		while (curr)
		{
			cout << curr->data << "-->";
			curr = curr->next;
		}
		delete curr;
	}
	bool checkpair(string target)
	{
		Node<T>* curr = new Node<T>;
		curr = head->next;
		while (curr)
		{
			if (curr->data == target)
				return true;

			curr = curr->next;
		}
		delete curr;
		return false;
	}
	string getAllconnections()
	{
		string strRet;
		Node<T>* curr = new Node<T>;
		curr = head->next;
		while (curr)
		{
			strRet += curr->data;
			strRet += " ";
			curr = curr->next;
		}
		delete curr;

		return strRet;
	}

	bool isEmpty()
	{
		if (head == NULL)
			return true;
		else
			return false;
	}

	T headData()
	{
		return head->getData();
	}

	T getData(int index)
	{
		Node<T>* temp = head;
		int i = 0;
		while (temp && i < index)
		{
			i++;
			temp = temp->next;
		}
		if (i == index && temp)
			return temp->data;
		else
			return " ";
	}

	bool notPresent(string val)
	{
		Node<T>* curr = new Node<T>;
		curr = head;
		while (curr)
		{
			if (curr->data == val)
				return false;
			curr = curr->next;
		}
		delete curr;
		return true;
	}
};

template <typename T>
class Graph
{
public:
	adjacencyList<T>* adjList;
	int maxVertices;
	int matrix[20][20];
	Graph()
	{
		adjList = NULL;
		maxVertices = 0;
	}

	Graph(int v)
	{
		maxVertices = v;
		adjList = new adjacencyList<T>[maxVertices];
	}

	void addVertex(Node<T>* newVertex)
	{
		for (int i = 0; i < maxVertices; i++)
		{
			if (adjList[i].head == NULL)
			{
				adjList[i].insert(newVertex->data);
				break;
			}
		}
	}

	void addedge(T source, T target, T wieght)
	{

		if (wieght != "?" && wieght != "")
		{
			int sIndex = searchGraph(source);
			int dIndex = searchGraph(target);

			if (source == "M2" || source == "M3")
			{
				adjList[sIndex].insert(target);
				matrix[sIndex][dIndex] = std::stoi(wieght);
			}

			if (checkPair(source, target))
			{
				matrix[sIndex][dIndex] = std::stoi(wieght);
			}

			else
			{
				adjList[sIndex].insert(target);
				matrix[sIndex][dIndex] = std::stoi(wieght);
			}
		}
	}
	bool checkPair(string source, string target)
	{
		for (int i = 0; i < maxVertices; i++)
			if (adjList[i].head != NULL && adjList[i].head->data == source)
				return adjList->checkpair(target);
		return false;
	}

	void showGraph()
	{
		for (int i = 0; i < maxVertices; i++)
		{
			cout << "\t\t";
			if (adjList[i].head != NULL)
			{
				adjList[i].display();

				cout << "NULL\n";
			}
		}
	}

	int searchGraph(T data)
	{
		for (int i = 0; i < maxVertices; i++)
		{
			if (adjList[i].head->data == data)
				return i;
		}
		return -1;
	}

	adjacencyList<T>* returnNode(int index)
	{
		if (&adjList[index])
			return &adjList[index];
		else
		{
			cout << "\n..............\nData not found";
			return NULL;
		}

	}

	void showMatrix()
	{
		for (int i = 0; i < 20; i++)
		{
			cout << "\t\t";
			for (int j = 0; j < 20; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << "\n";
		}
	}

	T returnMatrix()
	{
		return matrix;
	}

};

class Message
{

public:
	//next pointer
	Message* next;
	//A unique identifier that is used to differentiate between different messages from the same machine.
	int id;
	//An integer with values from 0 to 10 indicating the priority of the message.
	int priority;
	//The address of the machine that sends the message
	string sourceAddress;
	//The address of the target machine that is the recipient of this message.
	string destinationAddress;
	//Payload contains the actual text/data of the message
	string payload;
	//stores the path followed by the message
	string trace;

	bool recieved;
	Message()
	{
		next = NULL;
		recieved = false;
	}
	Message(int id, int priority, string SA, string DA, string PL, string T)
	{
		this->id = id;
		this->priority = priority;
		this->sourceAddress = SA;
		this->destinationAddress = DA;
		this->payload = PL;
		this->trace = T;
		recieved = false;
	}

	void setData(Message* temp)
	{
		id = temp->id;
		priority = temp->priority;
		sourceAddress = temp->sourceAddress;
		destinationAddress = temp->destinationAddress;
		payload = temp->payload;
		trace = temp->trace;
	}

	void setNext(Message* next)
	{
		this->next = next;
	}
	void display()
	{
		cout << "--------------------------------------" << endl;
		cout << "Message id : " << id << endl;
		cout << "Message priority : " << priority << endl;
		cout << "Message SA : " << sourceAddress << endl;
		cout << "Message DA : " << destinationAddress << endl;
		cout << "Message PL : " << payload << endl;
		cout << "Message T : " << trace << endl << endl;
	}
};

void readMessage(string file, Message& M);
class binaryHeap
{
	Message* array;
	int currSize;
public:
	binaryHeap()
	{
		currSize = 0;
		array = new Message[Cap];
	}
	//to get upper level parent
	int parent(int i)
	{
		return (i - 1) / 2;
	}
	//get left
	int left(int i)
	{
		return (2 * i + 1);
	}
	//get right
	int right(int i)
	{
		return (2 * i + 2);
	}
	//insertion
	void insert(Message M)
	{
		if (currSize == Cap)
		{
			cout << "Can't insert...";
			return;
		}
		currSize++;
		int i = currSize - 1;
		array[i] = M;

		while (array[i].priority > array[parent(i)].priority && i != 0)
		{
			swap(&array[i], &array[parent(i)]);
			i = parent(i);
		}
	}
	/*void decreaseKey(int i, int new_val)
	{
		array[i] = new_val;
		while (i != 0 && array[parent(i)] < array[i])
		{
			swap(&array[i], &array[parent(i)]);
			i = parent(i);
		}
	}*/

	Message* extractMax()
	{
		if (currSize <= 0)
			//infinity
			exit(0);
		if (currSize == 1)
		{
			currSize = currSize - 1;
			return &array[0];
		}
		Message* retMsg = &array[0];
		array[0] = array[currSize - 1];
		currSize--;
		MaxHeapify(0);
		return retMsg;
	}
	//deleting a Key
	/*void removeKey(int i)
	{
		decreaseKey(i, INT_MAX);
		extractMax();
	}*/
	//ReArranging Heap
	void MaxHeapify(int i)
	{
		int largest = i;
		int r = right(i);
		int l = left(i);
		if (l < currSize && array[l].priority > array[i].priority)
			largest = l;
		if (r < currSize && array[r].priority > array[largest].priority)
			largest = r;
		if (largest != i)
		{
			swap(&array[i], &array[largest]);
			MaxHeapify(largest);
		}
	}
	//swapping
	void swap(Message* a, Message* b)
	{
		Message temp = *a;
		*a = *b;
		*b = temp;
	}

};

class Queue
{
public:
	Queue()
	{
		front = NULL;
		rear = NULL;
	}
	void enqueue(Message* data)
	{
		Message* newNode = new Message;
		newNode->setData(data);
		newNode->setNext(NULL);
		//new queue
		if (isEmpty()) {
			front = newNode;
			rear = newNode;
		}
		//next node in queue
		else {
			rear->setNext(newNode);
			rear = newNode;
		}
	}
	void dequeue()
	{
		Message* temp = new Message;
		if (isEmpty())
			return;
		else {
			temp = front->next;
			delete front;
			front = temp;
			if (front == NULL)
				rear = NULL;

		}


	}
	Message* Front()
	{
		return front;
	}
	bool isEmpty(void)
	{
		if (front == NULL && rear == NULL)
			return true;
		else
			return false;
	}


	Message* getRear()
	{
		return rear;
	}
	Message* getFront()
	{
		return front;
	}
private:

	Message* front;
	Message* rear;

};

// Splay tree
int Length(string str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;

	return i;
}

template<typename T>
class SplayNode
{
public:
	T value;
	int height;
	SplayNode* left;
	SplayNode* right;
	SplayNode()
	{
		left = NULL;
		right = NULL;
	}
	void setNull()
	{
		left = NULL;
		right = NULL;
	}

	void print()
	{
		//cout << "\n...........................\n" << endl;
		cout << value << " ";
		//cout << height << endl;
	}
};

template<typename T>
class SplayTree
{
	SplayNode<T>* root;

	SplayNode<T>* Insert(SplayNode<T>* temp, T num)
	{
		SplayNode<T>* newNode = new SplayNode<T>;
		newNode->value = num;
		newNode->setNull();
		if (temp == NULL)
		{
			temp = newNode;
			temp->height = BalancedFactorLeft(temp);
		}
		else if (temp->value > num)
		{
			temp->left = Insert(temp->left, num);
			if (BalancedFactorLeft(temp) == 2)
			{
				if (temp->left->value > num)
					temp = singleRotateLeft(temp);
				else
					temp = doubleRotateLeft(temp);
			}
		}
		else if (temp->value < num)
		{
			temp->right = Insert(temp->right, num);
			if (BalancedFactorRight(temp) == 2)
			{
				if (temp->right->value < num)
					temp = singleRotateRight(temp);
				else
					temp = doubleRotateRight(temp);
			}
		}

		return temp;
	}

	SplayNode<T>* doubleRotateRight(SplayNode<T>* temp)
	{
		temp->right = singleRotateLeft(temp->right);
		return singleRotateRight(temp);
	}

	SplayNode<T>* doubleRotateLeft(SplayNode<T>* temp)
	{
		temp->right = singleRotateRight(temp->right);
		return singleRotateLeft(temp);
	}

	int Height(SplayNode<T>* temp)
	{
		if (temp == NULL)
		{
			return -1;
		}
		else
		{
			return temp->height;
		}
	}

	int BalancedFactorLeft(SplayNode<T>* temp)
	{
		return Height(temp->left) - Height(temp->right);
	}

	int BalancedFactorRight(SplayNode<T>* temp)
	{
		temp->height = Height(temp->right) - Height(temp->left);
		return Height(temp->right) - Height(temp->left);
	}

	SplayNode<T>* singleRotateLeft(SplayNode<T>* newNode)
	{
		SplayNode<T>* temp;
		temp = newNode->left;
		newNode->left = temp->right;
		temp->right = newNode;
		newNode->height = MaxHeight(Height(newNode->left), Height(temp->right)) + 1;
		temp->height = MaxHeight(Height(temp->left), newNode->height) + 1;
		return temp;
	}

	SplayNode<T>* singleRotateRight(SplayNode<T>* newNode)
	{
		SplayNode<T>* temp;
		temp = newNode->right;
		newNode->right = temp->left;
		temp->left = newNode;
		newNode->height = (MaxHeight(Height(newNode->left), Height(newNode->right)) + 1);
		temp->height = (MaxHeight(Height(temp->right), newNode->height) + 1);
		return temp;
	}

	int MaxHeight(int temp1, int temp2)
	{
		if (temp1 > temp2)
			return temp1;
		else
			return temp2;
	}
public:
	SplayTree()
	{
		root = NULL;
	}

	void insert(T num)
	{
		root = Insert(root, num);
	}

	void displayInOrder()
	{
		cout << "\n.......... Display in Inorder ..........\n";
		Inorder(root);
	}

	void Inorder(SplayNode<T>* temp)
	{
		if (temp)
		{
			Inorder(temp->left);
			temp->print();
			Inorder(temp->right);
		}
	}

	void displayPreOrder()
	{
		cout << "\n.......... Display in Preorder ..........\n";
		Preorder(root);
	}

	void Preorder(SplayNode<T>* temp)
	{
		if (temp)
		{
			temp->print();
			Inorder(temp->left);
			Inorder(temp->right);
		}
	}

	void displayPostOrder()
	{
		cout << "\n.......... Display in Postorder ..........\n";
		Postorder(root);
	}

	void Postorder(SplayNode<T>* temp)
	{
		if (temp)
		{
			Inorder(temp->left);
			Inorder(temp->right);
			temp->print();
		}
	}

	// for splay tree searching

	SplayNode<T>* singleRotateLeftforSplaySearch(SplayNode<T>* newNode)
	{
		SplayNode<T>* temp;
		temp = newNode->left;
		newNode->left = temp->right;
		temp->right = newNode;
		return temp;
	}

	SplayNode<T>* singleRotateRightforSplaySearch(SplayNode<T>* newNode)
	{
		SplayNode<T>* temp;
		temp = newNode->right;
		newNode->right = temp->left;
		temp->left = newNode;
		return temp;
	}


	SplayNode<T>* splay(SplayNode<T>* currNode, T key)
	{
		if (currNode == NULL)
			return currNode;
		if (currNode->value == key)
			return currNode;

		// if required key is in the left side if tree becuase we have avl tree
		if (currNode->value > key)
		{
			return DataInLeftSide(currNode, key);
		}
		else
		{
			return DataInRightSide(currNode, key);
		}
	}

	SplayNode<T>* DataInRightSide(SplayNode<T>* currNode, T key)
	{
		if (currNode->right == NULL)
			return currNode;// if key is not found


		if (currNode->right->value > key)// key on the left of remaining tree
		{
			currNode->right->left = splay(currNode->right->left, key);//call splay function again to find from left side

			if (currNode->right->left != NULL)// perform right rotation becuase we are moving in right of tree 
				currNode->right = singleRotateLeftforSplaySearch(currNode->right);// it is important to move the search value at root

		}
		else if (currNode->right->value < key)
		{
			currNode->right->right = splay(currNode->right->right, key);
			currNode = singleRotateRightforSplaySearch(currNode);
		}

		if (currNode->right == NULL)// key not found
			return currNode;
		else
		{
			currNode = singleRotateRightforSplaySearch(currNode);
			return currNode;
		}
	}

	SplayNode<T>* DataInLeftSide(SplayNode<T>* currNode, T key)
	{
		if (currNode->left == NULL)// cannot found a key
			return currNode;   // to save program from any error of memory


		if (currNode->left->value > key)// if data is to the left of currNode left
		{
			currNode->left->left = splay(currNode->left->left, key);
			currNode = singleRotateLeftforSplaySearch(currNode);
		}
		else if (currNode->left->value < key)
		{

			currNode->left->right = splay(currNode->left->right, key);


			if (currNode->left->right != NULL)
				currNode->left = singleRotateRightforSplaySearch(currNode->left);
		}


		if (currNode->left == NULL)
			return currNode;
		else
		{
			currNode = singleRotateLeftforSplaySearch(currNode);
			return currNode;
		}
	}

	SplayNode<T>* search(T key)
	{
		root = splay(root, key);
		return root;
	}

};

class routingTable
{
	string* destination;
	//Delay of one seconds

	routingTable()
	{

	}

};

class Router
{
public:

	string Name;

	Router()
	{

	}
	Router(string Name)
	{
		this->Name = Name;
	}
	Message* processMessage(Message& M1, string& path)
	{
		cout << Name;
		Incomming.insert(M1);
		M1.trace += "-";
		M1.trace += Name;
		for (int i = 0; i < destcount; i++)
		{
			if (M1.destinationAddress == destination[i])
				M1.recieved == true;
		}
		if (!M1.recieved)
			deletePath(path);

		return sendMessage();
	}
	void deletePath(string& str)
	{

		string newstr;
		for (int i = 3; i < str.length(); i++)
		{
			newstr += str[i];
		}
		str = newstr;
	}
	Message* sendMessage()
	{
		Outgoing.enqueue(Incomming.extractMax());
		delay(1000);
		cout << "-->";
		Message* mRet = Outgoing.getFront();
		Outgoing.dequeue();
		return mRet;

	}
	void appendDestination(string str)
	{
		string* temp = new string[destcount + 1];
		int i;
		for (i = 0; i < destcount; i++)
		{
			temp[i] = destination[i];
		}
		temp[i] = str;
		destcount++;
		destination = temp;
	}
	//Binary Heap
	binaryHeap Incomming;
	//Queue
	Queue Outgoing;

	//Routing Table
	//routingTable rTable;

	string* destination;
	int destcount = 0;

};

class Network
{
private:
	Graph<string>* G;

	Router routers[5];

	int routerNum = 0;
	adjacencyList<string>* adj;
	Node<string> Array[20];
	int index;
public:
	Network()
	{
		G = NULL;
		index = 0;
		adj = NULL;
	}
	void DisplayGraph()
	{
		G->showGraph();
	}
	void DisplayMatrix()
	{
		G->showMatrix();
	}
	void GraphLoading()
	{
		fstream network;

		network.open("network.csv", ios::in);
		string str, value, source;

		Graph<string>* temp = new Graph<string>(20);
		G = temp;
		string vertices[20];
		int row = 1;
		int i = 0;
		getline(network, str);

		std::stringstream s(str);
		while (getline(s, value, ',') && row == 1)
		{
			if (value != "")
			{
				vertices[i] = value;
				Array[i].setData(value);
				Array[i].setNext(NULL);
				G->addVertex(&Array[i]);
				i++;
				index = i;
			}
		}
		row = 0;
		while (getline(network, str))
		{
			int i = 0;
			std::stringstream s(str);
			getline(s, source, ',');
			getline(s, value, ',');
			do {
				G->addedge(source, vertices[i++], value);
			} while (getline(s, value, ','));

			row++;
		}
		//G->showGraph();
		//G->showMatrix();
		makeNetwork();
	}
	void makeNetwork()
	{
		//Saving router destinations
		for (int i = 0; i < 20; i++)
		{
			if (G->adjList[i].head->data[0] == 'R')
			{
				routers[routerNum].Name = G->adjList[i].head->data;
				string data = G->adjList[i].getAllconnections();
				string str;
				int j = 0;
				while (data[j] != '\0')
				{
					if (data[j] != ' ')
						str += data[j];
					else
					{
						routers[routerNum].appendDestination(str);
						str = "\0";
					}
					j++;
				}
				routerNum++;
			}
		}

	}
	void changeedge(string e1, string e2, int wieght)
	{
		string str;
		stringstream ss;
		ss << wieght;
		ss >> str;
		G->addedge(e1, e2, str);
	}
	void takeMessage()
	{
		while (1)
		{
			int choice;
			Message M;
			string msg;
		input:
			cout << "\n\t\t-----How you want to send message----------------\n";
			cout << "\n\t\t-----Press 1 for commandline\n\t\t-----Press 2 for file\n\t\t-----Press 3 to abort\n";
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "\n\t--------------Message Entering--------------\n";
				cout << "\n\tEnter Message ID\n";
				cin >> M.id;
				cout << "\n\tEnter Priority Key for Message\n";
				cin >> M.priority;
				cout << "\n\tEnter Source for Message\n";
				cin >> M.sourceAddress;
				cout << "\n\tEnter Destination for Message\n";
				cin >> M.destinationAddress;
				cout << "\n\tEnter Payload for Message\n";
				cin >> M.payload;

				break;

			case 2:
				cout << "\n-----Input message file Name ; ";
				cin >> msg;
				readMessage(msg);
				goto input;
				break;
			case 3:
				cout << "\n-----Ending...." << endl;
				return;
				break;

			default:
				cout << "\n----Wrong Input\n";
				goto input;
				break;
			}
			sendMessage(M);
		}
	}
	void sendMessage(Message M)
	{
		string sourceR = getRouter(M.sourceAddress);
		string destinationR = getRouter(M.destinationAddress);

		string path = getpathstring(sourceR, destinationR);

		while (!M.recieved)
		{
			if (path == "")
				break;
			routers[getRouterIndex(path)].processMessage(M, path);
		}

		cout << "Message Recieved" << endl;
		M.display();
	}
	void readMessage(string file)
	{
		string str;
		ifstream inputFile;
		Message* M;
		inputFile.open(file);
		if (!inputFile)
		{
			cout << "File Not Opened" << endl;
			exit(0);
		}
		else
		{
			while (!inputFile.eof())
			{
				M = new Message;
				inputFile >> M->id >> M->priority >> M->sourceAddress >> M->destinationAddress >> M->payload;
				Message m = *M;
				sendMessage(m);
			}
		}
		inputFile.close();
	}
	void path1to1(string s1, string s2)
	{
		string r1, r2;
		r1 = getRouter(s1);
		r2 = getRouter(s2);
		s1 += " ";
		s1 += getpathstring(r1, r2);
		s1 += " ";
		s1 += s2;
		cout << "\t\t Path : " << s1 << endl;
	}
	void path1toall(string s1)
	{
		string r1, r2, s2;
		r1 = getRouter(s1);
		r2 = s1;
		for (int i = 0; i < routerNum; i++)
		{
			if (r1 != routers[i].Name)
			{
				s1 += " - ";
				s1 += getpathstring(r1, routers[i].Name);
				s1 += " ";
				s1 += s2;
				for (int j = 0; j < routers[i].destcount; j++)
				{
					if (routers[i].destination[j][0] == 'M')
						cout << "\t\t Path : " << s1 << " - " << routers[i].destination[j] << endl;
				}
			}
			s1 = r2;
		}
	}
	void pathallto1(string s2)
	{
		string r1, r2, s1;
		r2 = getRouter(s2);
		r1 = s2;
		for (int i = 0; i < routerNum; i++)
		{
			if (r2 != routers[i].Name)
			{
				s2 = "\0";
				s2 += getpathstring(routers[i].Name, r2);
				for (int j = 0; j < routers[i].destcount; j++)
				{
					if (routers[i].destination[j][0] == 'M')
						cout << "\t\t Path : " << routers[i].destination[j] << " - " << s2 << " - " << r1 << endl;
				}

			}
			s2 = r1;
		}
	}
	void getPaths()
	{
		char choice;
		string s1, s2;
		string r1, r2;
	menu:
		cout << "\n";
		cout << "\t\t\t Printing Paths Menu" << endl;
		cout << " \t\tPress 1 for one to one path " << endl;
		cout << " \t\tPress 2 for one to all " << endl;
		cout << " \t\tPress 3 for all to one " << endl;
		cout << " \t\tPress 0 to Exit" << endl;
		choice = _getch();
		system("cls");

		switch (choice)
		{
		case 49:
			cout << "\t\Input Source : ";
			cin >> s1;
			cout << "\t\Input Destination : ";
			cin >> s2;
			path1to1(s1, s2);
			goto menu;
		case 50:
			cout << "\t\Input Source : ";
			cin >> s1;
			path1toall(s1);
			goto menu;
		case 51:
			cout << "\t\Input Destination : ";
			cin >> s2;
			pathallto1(s2);
			goto menu;
		case 48:

			break;



		}
	}
	string getRouter(string str)
	{
		for (int i = 0; i < 20; i++)
		{
			if (G->adjList[i].head->data == str)
			{
				return G->adjList[i].head->next->data;
			}
		}
	}
	int getRouterIndex(string path)
	{

		for (int i = 0; i < 5; i++)
		{
			if (routers[i].Name[0] == path[0] && routers[i].Name[1] == path[1])
			{
				return i;
			}
		}
	}
	string getpathstring(string source, string destination)
	{
		int s = -1, d = -1;
		for (int i = 0; i < 20; i++)
		{
			if (G->adjList[i].head->data == source)
				s = i;
			if (G->adjList[i].head->data == destination)
				d = i;
		}
		if (s == -1 || d == -1)
			exit(0);

		int i = 0;
		string str = getpathint(s, d);
		string temp;
		string retStr;
		int tempi;
		while (str[i] != '\0')
		{
			if (str[i] == ' ')
			{
				tempi = stoi(temp);
				retStr += indextoName(tempi);
				retStr += " ";
				temp = "\0";
			}
			temp += str[i];
			i++;
		}
		source += " ";
		source += retStr;
		source += destination;
		return source;
	}
	string indextoName(int i)
	{
		return G->adjList[i].head->data;
	}
	int minDistance(int dist[], bool sptSet[])
	{
		int min = INT_MAX, min_index;

		for (int v = 0; v < 20; v++)
			if (sptSet[v] == false && dist[v] <= min)
				min = dist[v], min_index = v;

		return min_index;
	}
	string getpathint(int source, int destination)
	{
		cout << endl;
		int dist[20];
		bool sptSet[20];
		string parent[20];
		string s;

		for (int i = 0; i < 20; i++)
			dist[i] = INT_MAX, sptSet[i] = false;

		dist[source] = 0;

		for (int count = 0; count < 20 - 1; count++) {
			int u = minDistance(dist, sptSet);

			sptSet[u] = true;

			for (int v = 0; v < 20; v++)

				if (!sptSet[v] && G->matrix[u][v] && dist[u] != INT_MAX && dist[u] + G->matrix[u][v] < dist[v])
				{
					dist[v] = dist[u] + G->matrix[u][v];
					s = to_string(u);
					parent[v] += s;
					parent[v] += " ";
				}
		}
		//cout << destination << "\t" << dist[destination] << endl;
		//cout << parent[destination] << endl;
		return parent[destination];
	}
};
