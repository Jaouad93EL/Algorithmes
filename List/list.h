#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct ListElmt_ {
  void * donnee;
  struct ListElmt_ * suivant;
} ListElmt;

typedef struct List_ {
  int taille;
  int (* corresp)(const void * val1, const void * val2);
  void (* detruire)(void * donne);
  ListElmt * tete;
  ListElmt * queue;
} List;

/*O(1)*/
void list_init(List * liste, void (* detruire)(void * donnee));
/*O(n)*/
void list_destroy(List * liste);
/*O(1)*/
int list_ins_next(List * liste, ListElmt * element, const void * donnee);
/*O(1)*/
int list_rem_next(List * liste, ListElmt * element, void ** donnee);
/*O(n)*/
void list_aff_string(List * liste);
/*O(n)*/
void list_aff_number(List * liste);

/*ALL DEFINE O(1)*/
#define list_size(liste) ((liste)->taille)
#define list_head(liste) ((liste)->tete)
#define list_tail(liste) ((liste)->queue)
#define list_is_head(liste, element) ((element) == (liste)->tete ? 1 : 0)
#define list_is_tail(element) ((element)->suivant == NULL ? 1 : 0)
#define list_data(element) ((element)->donnee)
#define list_next(element) ((element)->suivant)

#endif
