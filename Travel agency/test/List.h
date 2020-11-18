#pragma once

#include <iostream>
using namespace std;

template <typename T>
struct Nod {
	T val;
	Nod* urm;
	Nod(T v) :val{ v }, urm{ nullptr } {};
	Nod(T v, Nod* urm) :val{ v }, urm{ urm } {};
};

//forward declaration - clasa iterator e definit mai jos 
//Avem nevoie de asta fiindca clasa iterator este folosit in clasa MyLista dar definitia apare mai jos
template <typename T>
class Iterator;

template <typename T>
class List {
	
private:
	Nod<T>* head;
	

	/*
	Face o copie a listei inlantuite
	Parcurge recursiv lista si creaza noduri in care copieaza valorile
	*/
	Nod<T>* copy(Nod<T>* current);

public:
	
	List() :head{ nullptr } {
	};

	/*
	 Constructor de copiere
	 - apelat automat la transmitere prin valoare, la return prin valoare
	*/
	List(const List<T>& ot) { head = copy(ot.head); };
	/*
	Operator de assignment
	- apelat automat la expresii a = b; unde a si b sunt de tip List
	*/
	void operator=(const List<T>& ot);

	/*
	dealoca toate nodurile
	*/
	void free_nodes();

	/*
	 Destructor - apelat cand obiectul este distrus (out of scope sau delete)
	 Elibereaza memoria pentru fiecare nod
	*/
	~List();
	/*
	Returneaza numarul de elemente
	*/
	int size() const;

	/*
	Adauga la inceput
	*/
	void add_begin(T v);

	/*
	adauga la sfarsit
	*/
	void push_back(T v);

	/*
	Primul element
	*/
	T& first() const { return head->val; };

	/*
	Returneaza un iterator pozitionat pe primul element
	E nevoie de el ex. daca vrem sa folosim lista in range for
	*/
	Iterator<T> begin() const { return Iterator<T>{ head }; };

	/*
	Returneaza un iterator cu nodul nullptr (dupa ultimul element)
	*/
	Iterator<T> end() const { return Iterator<T>{ nullptr };};

	/*
	Acces dupa pozitie
	Operatie ineficienta, trebuie sa parcurg lista pana la poz
	*/
	T& operator[](size_t poz);

	/*
	Sterge un element de pe o pozitie data de un iterator
	*/
	void erase(Iterator<T>& it);


};

template<typename T>
Nod<T>* List<T>::copy(Nod<T>* current) {
	if (current == nullptr) {
		return nullptr;
	}
	auto n = new Nod<T>{ current->val };
	n->urm = copy(current->urm);
	return n;
};


template<typename T>
void List<T>::operator=(const List<T>& ot) {
	free_nodes();
	//copiez din ot in this
	head = copy(ot.head);
};


template<typename T>
void List<T>::free_nodes() {
	auto nCurent = this->head;
	while (nCurent != nullptr) {
		auto aux = nCurent->urm;
		delete nCurent;
		nCurent = aux;
	}
	this->head = nullptr;
};

template<typename T>
List<T>::~List() {
	free_nodes();
};

template<typename T>
int List<T>::size() const {
	auto nCurent = head;
	int lg = 0;
	while (nCurent != nullptr) {
		lg++;
		nCurent = nCurent->urm;
	}
	return lg;
};

template<typename T>
void List<T>::add_begin(T v) {
	Nod<T>* n = new Nod<T>{ v,head };
	head = n;
};


template<typename T>
void List<T>::push_back(T v) {
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
};

template<typename T>
T& List<T>::operator[](size_t poz) {
	auto nCurent = head;
	int lg = 0;
	while (lg < poz) {
		lg++;
		nCurent = nCurent->urm;
	}
	return nCurent->val;
};

template<typename T>
void List<T>::erase(Iterator<T>& it) {
	Nod<T>* node = head;
	Movie mv = *it;
	it.next();
	//daca e pe prima pozitie
	if (node->val == mv)
	{
		head = head->urm;
		delete node;
	}
	else {
		while (!(node->urm->val == mv))
			node = node->urm;
		delete node->urm;
		node->urm = node->urm->urm;
		
	}
};


/*
  Iterator pentru lista inlantuita
*/
template<typename T>
class Iterator {
	//pozitia curenta - este nullptr daca am ajuns la sfarsitul listei
	Nod<T>* current;
public:
	Iterator(Nod<T>* c) :current{ c } {
	}

	/*
	Este nevoie de operator != pentru range for
	*/
	bool operator!=(const Iterator<T>& ot) { return current != ot.current; };

	/*
	trece la urmatorul element din interatie
	Este nevoie de operator ++ pentru range for
	*/
	void operator++() { this->current = this->current->urm; };

	/*
	trece la urmatorul element din interatie
	*/
	void next() { this->current = this->current->urm; };
	/*
	Returneaza elementul curent din interatir
	Este nevoie de operator * pentru range for
	*/
	T& operator*() { return current->val; };
};


