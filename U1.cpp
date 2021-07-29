#include <iostream>


struct node {
	node* next;
	int x;
};


//Anzahl Elemente zählen
int count(node* list) {
	int count = 0;
	while(list != NULL) {
		count ++;
		list = list->next;
	}
	return count;
}


//Knoten an Position x finden und return den Knoten
node* node_at(int x, node* list) {
	if (x >= count(list)) return NULL;
	if (x < 0) return NULL;
	node* current = list;
	for(int i=0; i<x; i++) {
		current = current->next;	//findet die x. Stelle in der Liste
	}
	return current;
}


//Inhalt an Position x zurückliefern
int data_at(int x, node* list) {
	node* current = node_at(x, list);
	if (current == NULL) {
		std::cout << "Speicherzugriffsfehler! Index " << x << " existiert nicht\n!";
		exit(1);
	}
	return current->x;
}


//Neues Element ans Ende anhängen
void add_element(int x, node* &list) {
	node* neu = new node();
	neu->x = x;
	if (list == NULL) {
		list = neu;
		neu->next = NULL;
		std::cout << "\nErstes Element hinzugefügt\n";
	}
	else {
		node_at(count(list)-1, list)->next = neu;
		std::cout << "\nNeues Element hinzugefügt\n";
	}
}

//Liste anhängen ans Ende
void add_list(node* list, node* &current) {
	while (list != NULL) {
		add_element(list->x, current);
		list = list->next;
	}
	std::cout << "\nListe angehängt!\n";
}


// TODO: Element an Position x löschen
void remove(int x, node* &list) {
	node* toremove = node_at(x, list);
	if (toremove == NULL) {
		std::cout << "Speicherzugriffsfehler! Index " << x << " existiert nicht\n!";
		exit(1);
	}
	if (toremove == list) {
		list = list->next;
	}
	else {
		node* previous = node_at(x-1, list);
		previous->next = toremove->next;
	}
	delete(toremove);
}


// TODO: Löschen der ganzen Liste
void remove_list(node* &list) {
	while (list != NULL) {
		remove(0, list);
	}
}


// TODO: Einfügen eines Elements an Position x
void add_in_position(int pos, int x, node* &list) {
	node* toadd = new node();
	toadd->x = x;
	toadd->next = node_at(pos, list);
	node* previous = node_at(pos-1, list);
	previous->next = toadd;
	if (list == NULL) {
			std::cout << "Speicherzugriffsfehler! Liste existiert nicht\n!";
			exit(1);
	}
}


//Sortieren der Liste nach ihren Inhalten aufsteigend (Bubble sort)
void sort(node* list) {
	node* current = list;
	if (list==NULL) {
		std::cout << "Fehler beim Sortieren! Liste existiert nicht\n!";
		exit(1);
	}
	else {
		while (current != NULL) {
			node* index = current->next;
			while (index != NULL) {
				if (current->x > index->x) {
					int temp = current->x;
					current->x = index->x;
					index->x = temp;
				}
				index = index->next;
			}
			current = current->next;
		}
	}

}


// TODO: Ausgeben der ganzen Liste (mit Kommata getrennt, am Ende Punkt)
void ausgabe(node *list) {
	std::cout << "\n==Inhalt der Liste==\n";
	if (list == NULL) {
		std::cout << "Speicherzugriffsfehler! Liste ist leer!";
		exit(1);
	}
	for (int i=0; i<count(list)-1; i++) {
		std::cout << data_at(i, list) << ", ";
		}
	int i=count(list)-1;
	std::cout << data_at(i, list);
	std::cout << ".\n";
}


//Ausgabe/Überprüfen
void test(node* list) {
	std::cout << "\n==Inhalt der Liste==\n";
	if (list == NULL) {
		std::cout << "Speicherzugriffsfehler! Liste ist leer!";
		exit(1);
	}
	for (int i=0; i<count(list); i++) {
	std::cout << "Inhalt an Position " << i << " = " << data_at(i, list) << std::endl;
	}
}


int main() {

	node* first = NULL;

	//Anzahl Elemente zählen
	std::cout << "Anzahl Elemente am Anfang: " << count(first) << std::endl;

	//Add Element
	add_element(4, first);

	//Überprüfen
	test(first);

	//first = new node();
	node* second = new node();
	node* third = new node();

	first->next = second;
	second->next = third;
	third->next = NULL;

	//first->x = 1;
	second->x = 2;
	third->x = 3;

	//Anzahl Elemente zählen
	std::cout << "\nAnzahl Elemente im zweiten Durchlauf: " << count(first) << std::endl;

	//Knoten finden an Position x
	std::cout << "\n==Knoten finden an Position x==\n";
	for (int i=0; i<count(first); i++) {
		std::cout << "Inhalt an Position " << i << " = " << node_at(i, first)->x << std::endl;
	}

	//Inhalt an Position x
	test(first);

	//Add Element
	add_element(4, first);

	//Überprüfen
	test(first);

	//Liste anhängen (an Kopie)
	node* kopie = NULL;
	add_list(first, kopie);
	add_list(third, kopie);

	//Überprüfen
	test(kopie);

	//Element an Position x löschen
	remove(0, kopie);
	remove (3, kopie);

	//Überprüfen
	test(kopie);

	//Einfügen Element an Position x
	add_in_position(2, 1, kopie);
	test(kopie);

	//Sortieren aufsteigend
	sort(kopie);
	test(kopie);

	ausgabe(kopie);

	//Liste löschen
	remove_list(kopie);
	test(kopie);


	return 0;

}
