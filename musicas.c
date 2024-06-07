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

void escreverArq(CircularDoublyLinkedlista *lista, const char *fileName) {
  FILE *file = fopen(fileName, "w");
  if (!file) {
    perror("Não foi possível abrir");
    return;
  }
  Node *atual = lista->head;
  if (atual) {
    do {
      fprintf(file, "%s;%s\n", atual->artista, atual->musica);
      atual = atual->next;
    } while (atual != lista->head);
  }
  fclose(file);
}
void mostrarPlaylistaAleatoria(CircularDoublyLinkedlista *lista) {
  if (!lista->head) {
    printf("Playlista is empty.\n");
    return;
  }
  int count = 0;
  Node *atual = lista->head;
  do {
    count++;
    atual = atual->next;
  } while (atual != lista->head);

  Node *array[count];
  atual = lista->head;
  for (int i = 0; i < count; i++) {
    array[i] = atual;
    atual = atual->next;
  }

  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (strcmp(array[j]->musica, array[j + 1]->musica) > 0) {
        Node *temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }

  for (int i = 0; i < count; i++) {
    printf("%s - %s\n", array[i]->artista, array[i]->musica);
  }
}

void insertMusica(CircularDoublyLinkedlista *lista, const char *fileName) {
  char artista[100];
  char musica[100];
  printf("Informe o nome do artista: ");
  scanf(" %[^\n]s", artista);
  printf("Agora informe a música: ");
  scanf(" %[^\n]s", musica);
  append(lista, artista, musica);
  escreverArq(lista, fileName);
  printf("Música nova adicionada com sucesso!.\n");
}

void removeMusica(CircularDoublyLinkedlista *lista, const char *fileName) {
  char musicaName[100];
  printf("Nome da música a ser removida: ");
  scanf(" %[^\n]s", musicaName);

  if (!lista->head) {
    printf("Playlist está vazia.\n");
    return;
  }
