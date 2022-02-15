#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <stdexcept>
#include <chrono>
#include <thread>
using namespace std;
const int SIZE = 200000;
//readfile
vector<string> readFile(string fileName)
{
	//initialize vector 
	vector<string> power;
	//this will take the file name given to the program and then it will use that, to allow variability;
	ifstream file(fileName);
	string line;
	//check if file is open
	if (!file.is_open()) throw runtime_error("could not open file");
	//while the file hasnt been read through
	while (getline(file, line))
	{
		power.push_back(line);
	}
	//return vector of ints
	return power;
}
//convert string to integer
vector<int> stringtoint(vector<string> vec) 
{
	int x;
	vector<int> ints;
	for (int i = 0; i < vec.size(); i++)
	{
		stringstream str(vec.at(i));
		str >> x;
		ints.push_back(x);
	}
	return ints;
}

//for verification purposes
void printVec(vector<int> vec)
{
	int n = vec.size();
	cout << "***********************************************************************************************************************" << endl;
	cout << "[";
	for (int i = 0; i < n; i++)
	{
		cout << vec[i] <<", ";
	}
	cout << "]\n";
	cout << "***********************************************************************************************************************" << endl;
}

//insert, takes the tree, and a key to insert
void insert(int tree[], int key)
{
	//start at 0
	int index = 0;
	//while the node is full

	while (tree[index] != -1)
	{
	
		//if its larger than the node, go to the left
		if (key > tree[index])
		{
		
			//left::
			index = index * 2 + 2;
			
		}
		else
		{
			
			//right::
			index = index * 2 + 1;
		}
	}
	//if the index isnt full, then insert the key
	cout << "key: "<<key<<" inserted at positon: " << index << endl;
	tree[index] = key;
}

void searchTree(int tree[], int key)
{
	int index = 0;
	while (true)
	{
		if (tree[index] == -1)
		{
			cout << key << " sorry, i couldn't find what you were looking for " << endl;
			return;
		}

		if (tree[index] == key)
		{
			cout << "Ah HA! I found " << key << endl;
			return;
		}
		if (key > tree[index])
		{
			index = index * 2 + 2;
		}
		else
		{
			index = index * 2 + 1;
		}
	}
}

void inOrder(int tree[], int index)
{
	if (index > SIZE)
	{
		return;
	}
	if (tree[index] != -1)
	{
		inOrder(tree, index * 2 + 1);
		cout << tree[index] << " ";
		inOrder(tree, index * 2 + 2);
	}
}

void preOrder(int tree[], int index)
{
	if (index > SIZE)
	{
		return;
	}
	if (tree[index] != -1)
	{
		cout << tree[index] << " ";
		preOrder(tree, index * 2 + 1);
		preOrder(tree, index * 2 + 2);
	}

}

void postOrder(int tree[], int index)
{
	if (index > SIZE)
	{
		return;
	}
	if (tree[index] != -1)
	{
		postOrder(tree, index * 2 + 1);
		postOrder(tree, index * 2 + 2);
		cout << tree[index] << " ";
	}
	
}

void treeMin(int tree[])
{
	int index = 0;
	int min;
	while (tree[index] != -1)
	{
		min = tree[index];
		index = index * 2 + 1;
	}
	cout << "the smallest leaf: " << min << endl;

}

void treeMax(int tree[])
{
	int index = 0;
	int max;
	while (tree[index] != -1)
	{
		max = tree[index];
		index = index * 2 + 2;
	}
	cout << "the largest leaf: " << max << endl;

}

void maxHeapify(int heap[], int index, int size)
{
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int Largest = index;
	if ((left < size) && (heap[left] > heap[index]))
	{
		Largest = left;
	}
	if ((right < size) && (heap[right] > heap[Largest]))
	{
		Largest = right;
	}
	if (Largest != index)
	{
		std::swap(heap[index], heap[Largest]);
		maxHeapify(heap, Largest, size);
	}
}

void createMaxHeap(int heap[], int size)
{
	for (int i = floor((size - 2) / 2); i > -1; i--)
	{
		maxHeapify(heap, i, size);
	}
}
void printHeap(int heap[], int size) 
{
	for (int i = 0; i < size; i++)
		std::cout << heap[i] << " ";
	cout << endl;
}

//build tree calls insert for the size of vector
void buildTree(int tree[], vector<int> data)
{
	for (int i = 0; i < data.size(); i++)
	{
		insert(tree, data[i]);
	}
}

//print main
void printMain() 
{
	cout << endl;
	cout << "you can call me the lorax, cause i plant trees\n";
	cout << "let me plant the seed of sorting for you my friend\n";
	cout << "enter a, b, or c for which seed you want to use!\n";
	cout << "if you would like to quit at any time, when prompted press 'E'\n";
	cout << "\n";
	cout << "+------------------------------------------------+\n";
	cout << "| a.seed 1          b.seed 2            c.seed 3 |\n";
	cout << "+------------------------------------------------+\n";
	cout << endl;
}

//prints out query to get size of array to sort
void printMethods() 
{
	cout << endl;
	cout << "Now choose which function you want to do on this tree!\n";
	cout << "+---------------------------------------------------------------------------+\n";
	cout << "|D. insert?               F.search?                   G. Min?               |\n";
	cout << "|H. Max?                  I. pre-order travsersal?    J. In-Order Traversal?|\n";
	cout << "|     K. Post-Order traversal?                 L. heapify!                  |\n";
	cout << "+---------------------------------------------------------------------------+\n";
	cout << endl;

}

char getOption(string validOptions)
{
	//create variables
	string userChoice;
	char choice;
	int indexer;
	do {
		cout << "Enter option: ";
		if (cin.peek() == '\n')cin.ignore();
		getline(cin, userChoice);

		choice = toupper(userChoice[0]);

		indexer = validOptions.find(choice);
		if (indexer == -1) {
			cout << "Invalid Option, choose one of the valid responses Please" << endl;
		}

	} while (indexer == -1);

	return choice;

}

/*int main() 
{
	//initialize tree 
	int tree[SIZE];
	//fill tree with null
	for (int i = 0; i < SIZE; i++)
		tree[i] = -1;
	//create vector of strings to hold data before stoi
	vector<string> power;
	//vector of data
	vector<int> data;
	//string for the test file location
	string test1 = "C:\\Users\\Thebl\\source\\repos\\315 project 2\\Debug\\test1.csv";
	//readfile into string vector
	power = readFile(test1);
	//convert string to integer
	data = stringtoint(power);
	//print vector to make sure im not stupid
	printVec(data);
	//build tree, this takes data from the vector, and inserts it into the tree array
	buildTree(tree, data);
	//print tree so im not dumb
	searchTree(tree, 84);
	searchTree(tree, 1000);	
	cout << "inorder: ";
	cout << endl;
	inOrder(tree, 0);
	cout << endl;
	cout << "postOrder: ";
	cout << endl;
	postOrder(tree, 0);
	cout << endl;
	cout << "preOrder: ";
	cout << endl;
	preOrder(tree, 0);
	cout << endl;
	int min;
	treeMin(tree);
	treeMax(tree);
	int* heap = data.data();
	cout << "Heaps: ";
	createMaxHeap(heap, data.size());
	printHeap(heap, data.size());
	return 0;
}
*/
int main()
{
	//initialize user input to null
	char userInput = ' ';
	char methodInput = ' ';
	int userKey;
	
	//initialize tree 
	int tree[SIZE];
	for (int i = 0; i < SIZE; i++)
		tree[i] = -1;
	
	//create vector of strings to hold data before stoi
	vector<string> power;
	//vector of data
	vector<int> data;
	
	//string for the test file location
	string test1 = "C:\\Users\\Thebl\\source\\repos\\315 project 2\\Debug\\test1.csv";
	string test2 = "C:\\Users\\Thebl\\source\\repos\\315 project 2\\Debug\\test2.csv";
	string test3 = "C:\\Users\\Thebl\\source\\repos\\315 project 2\\Debug\\test3.csv";

	//user options for get option
	string userOptions = "AaBbCcEe";
	string methodOptions = "EeDdFfGgHhIiJjKkLl";
	//while loop to check for exit
	do 
	{
		//prints which data file to use
		printMain();
		//gets users choice
		userInput = getOption(userOptions);
		
		//if seed A is picked
		if (userInput == 'A' || userInput == 'a')
		{
			cout << "you have chosen seed A!, lets plant.\n";

			//readfile into string vector
			power = readFile(test1);
			//convert string to integer
			data = stringtoint(power);

			//pause... for dramatic effect!!!
			std::chrono::seconds timeSpan(3);
			std::this_thread::sleep_for(timeSpan);
			cout << "its growing!!!\n";

			//build tree, this takes data from the vector, and inserts it into the tree array
			buildTree(tree, data);
			int* heap = data.data();

			std::this_thread::sleep_for(timeSpan);
			cout << "your tree has now grown, what would you like to do with it?" << endl;
			do {
				//prints the methods menu
				printMethods();
				methodInput = getOption(methodOptions);
				if (methodInput == 'D' && 'd')
				{
					cout << "what number would you like to insert?, remember, you cant insert too much into the tree, or it will explode and crash in a firey ball of death... please be reasonable" << endl;
					cin >> userKey;
					cout << "ahh, " << userKey << " the classic. inputing into tree! " << endl;
					cout << endl;
					insert(tree, userKey);

				}
				if (methodInput == 'F' && 'f')
				{
					cout << "what number do you want to search for? ";
					cin >> userKey;
					cout << "oo, ill go take a look! " << endl;
					cout << "*russtling in leaves*"<<endl;
					searchTree(tree, userKey);
				}
				if (methodInput == 'G' && 'g')
				{
					cout << "lets find the smallest number in this tree" << endl;
					cout << "*rustles around*" << endl;
					treeMin(tree);
				}
				if (methodInput == 'H' && 'h')
				{
					cout << "lets find the largest number in this tree" << endl;
					cout << "*rustles around*" << endl;
					treeMax(tree);
				}
				if (methodInput == 'I' && 'i')
				{
					cout << "i will now traverse this tree, but in preorder fashion! where would you like me to start?" << endl;
					cin >> userKey;
					while (userKey > SIZE) {
						if (userKey > SIZE)
						{
							cout << "this tree isn't even that big dummy!, choose a number less than 2000000" << endl;
							cin >> userKey;
						}
						else
							break;
					}
					preOrder(tree,userKey);
				}
				if (methodInput == 'J' && 'j')
				{
					cout << "i will now traverse this tree, but in inorder fashion! where would you like me to start?" << endl;
					cin >> userKey;
					while (userKey > SIZE) {
						if (userKey > SIZE)
						{
							cout << "this tree isn't even that big dummy!, choose a number less than 2000000" << endl;
							cin >> userKey;
						}
						else
							break;
					}
					inOrder(tree, userKey);
				}
				if (methodInput == 'K' && 'k')
				{
					cout << "i will now traverse this tree, but in post order fashion! where would you like me to start?" << endl;
					cin >> userKey;
					while (userKey > SIZE) {
						if (userKey > SIZE)
						{
							cout << "this tree isn't even that big dummy!, choose a number less than 2000000" << endl;
							cin >> userKey;
						}
						else
							break;
					}
					postOrder(tree, userKey);
				}
				if (methodInput == 'L' && 'l')
				{	
					cout << "time to condense this puppy down wouldn't you say! lets heapify!" << endl;
					createMaxHeap(heap, data.size());
					cout << "here is the heap you created!\n";
					printHeap(heap, data.size());

				}
			} while ((userInput != 'e' && userInput != 'E') && (methodInput != 'e' && methodInput != 'E'));

		}
		if (userInput == 'B' || userInput == 'b')
		{
			cout << "you have chosen seed B!, lets plant.\n";

			//readfile into string vector
			power = readFile(test2);
			//convert string to integer
			data = stringtoint(power);

			//pause... for dramatic effect!!!
			std::chrono::seconds timeSpan(3);
			std::this_thread::sleep_for(timeSpan);
			cout << "its growing!!!\n";

			//build tree, this takes data from the vector, and inserts it into the tree array
			buildTree(tree, data);
			int* heap = data.data();

			std::this_thread::sleep_for(timeSpan);
			cout << "your tree has now grown, what would you like to do with it?" << endl;
			do {
				//prints the methods menu
				printMethods();
				methodInput = getOption(methodOptions);
				if (methodInput == 'D' && 'd')
				{
					cout << "what number would you like to insert?, remember, you cant insert too much into the tree, or it will explode and crash in a firey ball of death... please be reasonable" << endl;
					cin >> userKey;
					cout << "ahh, " << userKey << " the classic. inputing into tree! " << endl;
					cout << endl;
					insert(tree, userKey);

				}
				if (methodInput == 'F' && 'f')
				{
					cout << "what number do you want to search for? ";
					cin >> userKey;
					cout << "oo, ill go take a look! " << endl;
					cout << "*russtling in leaves*" << endl;
					searchTree(tree, userKey);
				}
				if (methodInput == 'G' && 'g')
				{
					cout << "lets find the smallest number in this tree" << endl;
					cout << "*rustles around*" << endl;
					treeMin(tree);
				}
				if (methodInput == 'H' && 'h')
				{
					cout << "lets find the largest number in this tree" << endl;
					cout << "*rustles around*" << endl;
					treeMax(tree);
				}
				if (methodInput == 'I' && 'i')
				{
					cout << "i will now traverse this tree, but in preorder fashion! where would you like me to start?" << endl;
					cin >> userKey;
					while (userKey > SIZE) {
						if (userKey > SIZE)
						{
							cout << "this tree isn't even that big dummy!, choose a number less than 2000000" << endl;
							cin >> userKey;
						}
						else
							break;
					}
					preOrder(tree, userKey);
				}
				if (methodInput == 'J' && 'j')
				{
					cout << "i will now traverse this tree, but in inorder fashion! where would you like me to start?" << endl;
					cin >> userKey;
					while (userKey > SIZE) {
						if (userKey > SIZE)
						{
							cout << "this tree isn't even that big dummy!, choose a number less than 2000000" << endl;
							cin >> userKey;
						}
						else
							break;
					}
					inOrder(tree, userKey);
				}
				if (methodInput == 'K' && 'k')
				{
					cout << "i will now traverse this tree, but in post order fashion! where would you like me to start?" << endl;
					cin >> userKey;
					while (userKey > SIZE) {
						if (userKey > SIZE)
						{
							cout << "this tree isn't even that big dummy!, choose a number less than 2000000" << endl;
							cin >> userKey;
						}
						else
							break;
					}
					postOrder(tree, userKey);
				}
				if (methodInput == 'L' && 'l')
				{
					cout << "time to condense this puppy down wouldn't you say! lets heapify!" << endl;
					createMaxHeap(heap, data.size());
					cout << "here is the heap you created!\n";
					printHeap(heap, data.size());

				}
			} while ((userInput != 'e' && userInput != 'E') && (methodInput != 'e' && methodInput != 'E'));

		}
		if (userInput == 'C' || userInput == 'c')
		{
			cout << "you have chosen seed C!, lets plant.\n";

			//readfile into string vector
			power = readFile(test3);
			//convert string to integer
			data = stringtoint(power);

			//pause... for dramatic effect!!!
			std::chrono::seconds timeSpan(3);
			std::this_thread::sleep_for(timeSpan);
			cout << "its growing!!!\n";

			//build tree, this takes data from the vector, and inserts it into the tree array
			buildTree(tree, data);
			int* heap = data.data();

			std::this_thread::sleep_for(timeSpan);
			cout << "your tree has now grown, what would you like to do with it?" << endl;
			do {
				//prints the methods menu
				printMethods();
				methodInput = getOption(methodOptions);
				if (methodInput == 'D' && 'd')
				{
					cout << "what number would you like to insert?, remember, you cant insert too much into the tree, or it will explode and crash in a firey ball of death... please be reasonable" << endl;
					cin >> userKey;
					cout << "ahh, " << userKey << " the classic. inputing into tree! " << endl;
					cout << endl;
					insert(tree, userKey);

				}
				if (methodInput == 'F' && 'f')
				{
					cout << "what number do you want to search for? ";
					cin >> userKey;
					cout << "oo, ill go take a look! " << endl;
					cout << "*russtling in leaves*" << endl;
					searchTree(tree, userKey);
				}
				if (methodInput == 'G' && 'g')
				{
					cout << "lets find the smallest number in this tree" << endl;
					cout << "*rustles around*" << endl;
					treeMin(tree);
				}
				if (methodInput == 'H' && 'h')
				{
					cout << "lets find the largest number in this tree" << endl;
					cout << "*rustles around*" << endl;
					treeMax(tree);
				}
				if (methodInput == 'I' && 'i')
				{
					cout << "i will now traverse this tree, but in preorder fashion! where would you like me to start?" << endl;
					cin >> userKey;
					while (userKey > SIZE) {
						if (userKey > SIZE)
						{
							cout << "this tree isn't even that big dummy!, choose a number less than 2000000" << endl;
							cin >> userKey;
						}
						else
							break;
					}
					preOrder(tree, userKey);
				}
				if (methodInput == 'J' && 'j')
				{
					cout << "i will now traverse this tree, but in inorder fashion! where would you like me to start?" << endl;
					cin >> userKey;
					while (userKey > SIZE) {
						if (userKey > SIZE)
						{
							cout << "this tree isn't even that big dummy!, choose a number less than 2000000" << endl;
							cin >> userKey;
						}
						else
							break;
					}
					inOrder(tree, userKey);
				}
				if (methodInput == 'K' && 'k')
				{
					cout << "i will now traverse this tree, but in post order fashion! where would you like me to start?" << endl;
					cin >> userKey;
					while (userKey > SIZE) {
						if (userKey > SIZE)
						{
							cout << "this tree isn't even that big dummy!, choose a number less than 2000000" << endl;
							cin >> userKey;
						}
						else
							break;
					}
					postOrder(tree, userKey);
				}
				if (methodInput == 'L' && 'l')
				{
					cout << "time to condense this puppy down wouldn't you say! lets heapify!" << endl;
					createMaxHeap(heap, data.size());
					cout << "here is the heap you created!\n";
					printHeap(heap, data.size());

				}
			} while ((userInput != 'e' && userInput != 'E') && (methodInput != 'e' && methodInput != 'E'));

		}

	} while ((userInput != 'e' && userInput != 'E') && (methodInput != 'e' && methodInput != 'E')); 
	cout << "thank you for planting these amazing tress, remember, climate change is real and we have to do something about it!!!!" << endl;
	system("pause");
	return 0;
}

