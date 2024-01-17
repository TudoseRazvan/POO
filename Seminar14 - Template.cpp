#include<iostream>
using namespace std;

template<typename DataType>
struct Node
{
	DataType data;
	Node* next;
	Node(DataType d) :data(d), next(nullptr) {}
};

template<class T>
class MyList
{
private:
	Node<T>* head;

public:
	MyList()
	{
		head = NULL;
	}
	void add(T data)
	{
		Node<T>* newNode = new Node<T>(data);

		if (head)
		{
			Node<T>* last = head;
			while (last)
			{
				if (last->next == NULL)
					break;
				else
					last = last->next;
			}
			last->next = newNode;
		}
		else
		{
			head = newNode;
		}

	}


	//returneaza indexul nodului
	int search(T data)
	{
		if (head == NULL)
			return -1;
		if (head->data == data)
			return 0;

		Node<T>* found = head;
		int position = 1;

		while (found->next)
		{
			if (found->next->data == data)
				return position;
			found = found->next;
			position++;
		}

		return -1;
	}

	void remove(T data)
	{
		if (head == NULL)
			return;
		if (head->data == data)
		{
			Node<T>* tmp = head;
			head = head->next;

			delete tmp;

			return;
		}

		Node<T>* prev = head;

		while (prev->next)
		{
			if (prev->next->data == data)
				break;
			prev = prev->next;
		}

		Node<T>* tmp = prev->next;
		prev->next = prev->next->next;

		delete tmp;

	}

	void print()
	{
		cout << endl << "#Elementele din lista sunt:" << endl << endl;
		Node<T>* tmp = head;
		while (tmp)
		{
			cout << tmp->data << endl;
			tmp = tmp->next;
		}
		cout << endl;
	}

	int count()
	{
		if (head == NULL)
			return 0;

		Node<T>* node = head;
		int cnt = 1;

		while (node->next)
		{
			node = node->next;
			cnt++;
		}

		return cnt;
	}
};

class Test
{
public:
	string x;
	void print()
	{
		cout << x << endl;
	}
	Test(string x)
	{
		this->x = x;
	}

	friend ostream& operator<<(ostream& os, const Test& t);
};
ostream& operator<<(ostream& os, const Test& t)
{
	os << t.x;
	return os;
}

void main()
{
	MyList<Test> test;

	test.add(Test("primul"));
	test.add(Test("al doilea"));
	test.add(Test("al treilea"));

	test.print();

	MyList<string> strList;
	strList.add("unu");
	strList.add("doi");
	strList.add("trei");
	strList.add("patru");

	strList.print();

	cout << strList.count() << endl;;
	cout << strList.search("cinci") << endl;;

	strList.remove("trei");
	strList.print();


	cout << strList.count() << endl;


	strList.remove("patru");
	strList.print();

	strList.remove("doi");
	strList.print();

	strList.remove("unu");
	strList.print();

	MyList<int> seml;
	seml.add(1);
	seml.add(2);
	seml.add(3);
	seml.print();
	cout << seml.count() << endl;
}