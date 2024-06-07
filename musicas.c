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

void display(CircularDoublyLinkedlista *lista) {
  if (!lista->head) {
    printf("Playlist vazia.\n");
    return;
  }
  Node *atual = lista->head;
  do {
    printf("%s - %s\n", atual->artista, atual->musica);
    atual = atual->next;
  } while (atual != lista->head);
}

void readFile(CircularDoublyLinkedlista *lista, const char *fileName) {
  FILE *file = fopen(fileName, "r");
  if (!file) {
    perror("Não foi possível abrir");
    return;
  }
  char line[256];
  while (fgets(line, sizeof(line), file)) {
    char *artista = strtok(line, ";");
    char *musica = strtok(NULL, "\n");
    if (artista && musica) {
      append(lista, artista, musica);
    }
  }
  fclose(file);
}
