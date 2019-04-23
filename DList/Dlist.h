#ifndef DLIST_H
#define DLIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct DListElmt_ {
  void * donnee;
  struct DListElmt_ * precedent;
  struct DListElmt_ * suivant;
} DListElmt;

typedef struct DList_ {
  int taille;
  int (* corresp)(const void * val1, const void * val2);
  void (* detruire)(void * donne);
  DListElmt * tete;
  DListElmt * queue;
} DList;

/*O(1)*/
void dlist_init(DList * liste, void (* detruire)(void * donnee));
/*O(n)*/
void dlist_destroy(DList * liste);
/*O(1)*/
int dlist_ins_next(DList * liste, DListElmt * element, const void * donnee);
/*O(1)*/
int dlist_ins_prev(DList * liste, DListElmt * element, const void * donnee);
/*O(1)*/
int dlist_remove(DList * liste, DListElmt * element, void ** donnee);

/*ALL DEFINE O(1)*/
#define dlist_size(liste) ((liste)->taille)
#define dlist_head(liste) ((liste)->tete)
#define dlist_tail(liste) ((liste)->queue)
#define dlist_is_head(liste, element) ((element) == (liste)->tete ? 1 : 0)
#define dlist_is_tail(element) ((element)->suivant == NULL ? 1 : 0)
#define dlist_data(element) ((element)->donnee)
#define dlist_next(element) ((element)->suivant)

#endif
