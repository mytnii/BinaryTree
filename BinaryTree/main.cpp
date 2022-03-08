#include <iostream>

using namespace std;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}

		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}

		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		this->Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}

	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i, Root);
	}

	Tree(const Tree& other) :Tree()
	{
		copy(other.Root);
		cout << "CopyConstructor:\t" << this << endl;
	}
	
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}

	void clear()
	{
		clear(Root);
		Root = nullptr;
	}


	void erase(int Data)
	{
		erase(Data, Root);
	}

	double Avg()const
	{
		if (Root == nullptr)return 0;
		return (double)Sum(Root) / Size(Root);
	}

	int Sum()const
	{
		return Sum(Root);
	}

	int Size()const
	{
		return Size(Root);
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}
		int minValue()const
	{
		return minValue(this->Root);
	}
	int maxValue()const
	{
		return maxValue(this->Root);
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)
		{
			return;
		}
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			else
			{
				insert(Data, Root->pLeft);
			}
		}
		else
		{
			if (Root->pRight == nullptr)
			{
				Root->pRight = new Element(Data);
			}
			else
			{
				insert(Data, Root->pRight);
			}
		}
	}

	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf())	
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Size(Root->pLeft) > Size(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);	
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	int Sum(Element* Root)const
	{
		/*if (Root == nullptr)return 0;*/
		return Root ? Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data : 0;
	}

	int Size(Element* Root)const
	{
		/*if (Root == nullptr)return 0;*/
		return Root ? Size(Root->pLeft) + Size(Root->pRight) + 1 : 0;
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}

	void copy(Element* Root)
	{
		if (Root == nullptr) return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	}

	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		/*if (Root->pLeft == nullptr)return Root->Data;
		return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}

	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		if (Root->pRight == nullptr)return Root->Data;
		return maxValue(Root->pRight);
		
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)
		{
			return;
		}
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)
		{
			return;
		}
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			else
			{
				insert(Data, Root->pLeft);
			}
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)
			{
				Root->pRight = new Element(Data);
			}
			else
			{
				insert(Data, Root->pRight);
			}
		}
	}

public:
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "¬ведите размер дерева: ";
	cin >> n;

	UniqueTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;


	cout << tree.minValue() << endl;
	cout << tree.maxValue() << endl;
	cout << tree.Size() << endl;
	cout << tree.Sum() << endl;
	cout << tree.Avg() << endl;

	int value;

	cout << "¬ведите удавл€емое значение: "; cin >> value;

	tree.erase(value);
	tree.print();
#endif // BASE_CHECK

	Tree tree{ 50, 25, 75, 16, 32, 64, 80, 27,35 };
	tree.print();

	/*Tree tree2 = tree;
	tree2.print();*/
	int value;

	cout << "¬ведите удавл€емое значение: "; cin >> value;

	tree.erase(value);
	tree.print();
}