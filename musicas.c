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

 Node *atual = lista->head;
  int found = 0;
  do {
    if (strcmp(atual->musica, musicaName) == 0) {
      found = 1;
      if (atual == lista->head) {
        if (atual->next == lista->head) {
          lista->head = NULL;
        } else {
          Node *tail = lista->head->prev;
          lista->head = atual->next;
          tail->next = lista->head;
          lista->head->prev = tail;
        }
      } else {
        atual->prev->next = atual->next;
        atual->next->prev = atual->prev;
      }
      free(atual);
      break;
    }
    atual = atual->next;
  } while (atual != lista->head);

  if (found) {
    escreverArq(lista, fileName);
    printf("Música removida.\n");
  } else {
    printf("Não encontramos a música informada.\n");
  }
}
void searchMusica(CircularDoublyLinkedlista *lista) {
  char musicaName[100];
  printf("Digite o nome da música para procura: ");
  scanf(" %[^\n]s", musicaName);

  if (!lista->head) {
    printf("Playlist está vazia.\n");
    return;
  }

  Node *atual = lista->head;
  int found = 0;
  do {
    if (strcmp(atual->musica, musicaName) == 0) {
      printf("Song found: %s - %s\n", atual->artista, atual->musica);
      found = 1;
      break;
    }
    atual = atual->next;
  } while (atual != lista->head);

  if (!found) {
    printf("Música não encontrada.\n");
  }
}

Node *nextMusica(Node *atual) {
  if (atual && atual->next) {
    atual = atual->next;
  }
  return atual;
}

Node *prevMusica(Node *atual) {
  if (atual && atual->prev) {
    atual = atual->prev;
  }
  return atual;
}
void menu() {
  printf("Menu de opções:\n");
  printf("1. Exibição da playlist pela ordem de cadastro\n");
  printf("2. Exibição da playlist ordenada pelo nome das músicas\n");
  printf("3. Inserção de novas músicas\n");
  printf("4. Remoção de uma música\n");
  printf("5. Busca por uma música\n");
  printf("6. Avançar para próxima música\n");
  printf("7. Retornar a música anterior\n");
  printf("8. Sair\n");
}

int main() {
  CircularDoublyLinkedlista playlista = {NULL};
  Node *atualMusica = NULL;
  const char *fileName = "musicas.txt";
  readFile(&playlista, fileName);
  atualMusica = playlista.head;

  while (1) {
    menu();
    int choice;
    printf("Opção: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      display(&playlista);
      break;
    case 2:
      mostrarPlaylistaAleatoria(&playlista);
      break;
    case 3:
      insertMusica(&playlista, fileName);
      break;
    case 4:
      removeMusica(&playlista, fileName);
      break;
    case 5:
      searchMusica(&playlista);
      break;
    case 6:
      atualMusica = nextMusica(atualMusica);
      if (atualMusica) {
        printf("Now playing: %s - %s\n", atualMusica->artista,
               atualMusica->musica);
      }
      break;
    case 7:
      atualMusica = prevMusica(atualMusica);
      if (atualMusica) {
        printf("Now playing: %s - %s\n", atualMusica->artista,
               atualMusica->musica);
      }
      break;
    case 8:
      printf("Exiting the program.\n");
      exit(0);
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }

  return 0;
}
