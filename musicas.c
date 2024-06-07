#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *criarNode(char *artista, char *musica) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  strcpy(newNode->artista, artista);
  strcpy(newNode->musica, musica);
  newNode->next = newNode->prev = NULL;
  return newNode;
}

void append(CircularDoublyLinkedlista *lista, char *artista, char *musica) {
  Node *newNode = criarNode(artista, musica);
  if (!lista->head) {
    lista->head = newNode;
    lista->head->next = lista->head;
    lista->head->prev = lista->head;
  } else {
    Node *tail = lista->head->prev;
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = lista->head;
    lista->head->prev = newNode;
  }
}
