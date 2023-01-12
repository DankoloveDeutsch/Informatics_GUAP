#include <iostream>




template <typename T>
struct Node
{
	T data;
	Node* next;
};

template <typename T>
class List
{
private:
	Node<T>* _head;
	int _size = 0;

public:
	List() {
		_head = nullptr;
	};
	void push(T val) {  // добавление в конец
		_size++;
		if (_head == nullptr) {
			_head = new Node<T>();
			_head->data = val;
			return;
		}
		Node<T>* temp = _head;
		while (temp->next) {
			temp = temp->next;
		}
		Node<T>* n = new Node<T>();
		n->data = val;
		n->next = nullptr;
		temp->next = n;
	};
	T pop() { // удаление с конца
		if (_head) {
			T p = _head->data;
			_head = _head->next;
			_size--;
			return p;
		}
	};
	void set_value(int idx, T value) {
		Node<T>* temp = _head;
		int index = 0;
		while (temp->next) {
			if (index == idx) {
				temp->data = value;
				return;
			}
			else {
				temp = temp->next;
			}
			index++;
		}
		temp->data = value;
	};
	T& operator [](int idx) { // доступ по индексу
		Node<T>* temp = _head;
		int index = 0;
		while (temp->next) {
			if (index == idx) {
				return temp->data;
			}
			else {
				temp = temp->next;
			}
			index++;
		}
		return temp->data;
	};
	void print_data() {
		Node<T>* temp = _head;
		while (temp->next) {
			std::cout << temp->data << " ";
			temp = temp->next;
		}
		if (temp != nullptr)
			std::cout << temp->data << std::endl;
	};
};




int main() {
	int n;
	std::cout << "Input n=";
	std::cin >> n;

	List<int> list;
	int temp;
	for (int i = 0; i < n; i++) {
		std::cout << "Input list1[" << i << "]=";
		std::cin >> temp;
		list.push(temp);
	};

	int min_value = list[0];
	for (int i = 0; i < n; i++) {
		if (min_value > list[i]) {
			min_value = list[i];
		}
	}
	for (int i =0; i < n; i++) {
		if (list[i] == min_value) {
			list.set_value(i, min_value*2);
			break;
		}
	}

	list.print_data();
	return 0;
};