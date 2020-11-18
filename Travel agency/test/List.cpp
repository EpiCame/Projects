#include "List.h"

template <typename T>
List<T>::List(const List& ot) {
	//obiectul acum se creaza (constructor) 
	//copiez din ot in this
	head = copy(ot.head);
}
/*
Operator de assignment
- apelat automat la expresii a = b; unde a si b sunt de tip List
*/
template <typename T>
void List<T>::operator=(const List& ot) {
	//poate destinate (this) contine deja ceva
	free_nodes();
	//copiez din ot in this
	head = copy(ot.head);
}

/*
Destructor - apelat cand obiectul este distrus (out of scope sau delete)
*/
template <typename T>
List<T>::~List() {
	free_nodes();
}

template <typename T>
Nod<T>* List<T>::copy(Nod<T>* current) {
	if (current == nullptr) {
		return nullptr;
	}
	auto n = new Nod<T>{ current->val };
	n->urm = copy(current->urm);
	return n;
}

template <typename T>
void List<T>::add_begin(T v) {
	Nod<T>* n = new Nod<T>{ v,head };
	head = n;
}


template <typename T>
void List<T>::push_back(T v) {
	//ma pun pe ultimul element
	auto nCurent = head;
	while (nCurent != nullptr && nCurent->urm != nullptr) {
		nCurent = nCurent->urm;
	}

	if (nCurent == nullptr) {
		head = new Nod<T>{ v,nullptr };//poate era o lista vida
	}
	else {
		nCurent->urm = new Nod<T>{ v,nullptr };
	}
}

template <typename T>
size_t List<T>::size() const {
	auto nCurent = head;
	int lg = 0;
	while (nCurent != nullptr) {
		lg++;
		nCurent = nCurent->urm;
	}
	return lg;
}

template <typename T>
T& List<T>::operator[](size_t poz) {
	auto nCurent = cap;
	int lg = 0;
	while (lg < poz) {
		lg++;
		nCurent = nCurent->urm;
	}
	return nCurent->val;
}

template <typename T>
T& List<T>::first() const {
	return head->val;
}
template <typename T>
void List<T>::free_nodes() {
	auto nCurent = head;
	while (nCurent != nullptr) {
		auto aux = nCurent->urm;
		delete nCurent;
		nCurent = aux;
	}
	head = nullptr;
}


template <typename T>
Iterator<T> List<T>::begin() const {
	return Iterator<T>{ head };
}


template <typename T>
Iterator<T> List<T>::end() const {
	return Iterator<T>{ nullptr };
}


/*
Este nevoie de operator != pentru range for
*/
template <typename T>
bool Iterator<T>::operator!=(const Iterator& ot) {
	return current != ot.current;
}

/*
trece la urmatorul element din interatie
Este nevoie de operator ++ pentru range for
*/
template <typename T>
void Iterator<T>::operator++() {
	current = current->urm;
}
/*
Returneaza elementul curent din interatir
Este nevoie de operator * pentru range for
*/
template <typename T>
T& Iterator<T>::operator*() {
	return current->val;
}






















