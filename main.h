#ifndef MAIN_H
#define MAIN_H

// Define the structure for a node in the circular doubly linked lista
typedef struct Node {
  char artista[100];
  char musica[100];
  struct Node *prev;
  struct Node *next;
} Node;

// Define the structure for the circular doubly linked lista
typedef struct {
  Node *head;
} CircularDoublyLinkedlista;

// Function prototypes
Node *criarNode(char *artista, char *musica);
void append(CircularDoublyLinkedlista *lista, char *artista, char *musica);
void display(CircularDoublyLinkedlista *lista);
void readFile(CircularDoublyLinkedlista *lista, const char *fileName);
void writeFile(CircularDoublyLinkedlista *lista, const char *fileName);
void displaySortedPlaylista(CircularDoublyLinkedlista *lista);
void insertMusica(CircularDoublyLinkedlista *lista, const char *fileName);
void removeMusica(CircularDoublyLinkedlista *lista, const char *fileName);
void searchMusica(CircularDoublyLinkedlista *lista);
Node *nextMusica(Node *atual);
Node *prevMusica(Node *atual);
void menu();

#endif // MAIN_H
