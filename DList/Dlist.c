#include "Dlist.h"

void dlist_init(DList * liste, void (* detruire)(void * donnee))
{
  liste->taille = 0;
  liste->detruire = detruire;
  liste->tete = NULL;
  liste->queue = NULL;
}

void dlist_destroy(DList * liste)
{
  void * donnee;

  while (dlist_size(liste) > 0)
    if (dlist_remove(liste, dlist_tail(liste), (void **)&donnee) == 0 && liste->detruire != NULL)
      liste->detruire(donnee);
  memset(liste, 0, sizeof(DList));
}

int dlist_ins_next(DList * liste, DListElmt * element, const void * donnee)
{
  DListElmt * nouv_element;

  /*element == NULL est liste pas vide*/
  if (element == NULL && dlist_size(liste) != 0)
    return (-1);
  nouv_element = (DListElmt *) malloc(sizeof(DListElmt));
  if (nouv_element == NULL)
    return (-1);
  nouv_element->donnee = (void *) donnee;
  if (dlist_size(liste) == 0) { /*Insertion liste vide*/
    liste->tete = nouv_element;
    liste->tete->precedent = NULL;
    liste->tete->suivant = NULL;
    liste->queue = nouv_element;
  }
  else { /*Insertion liste pas vide*/
    nouv_element->suivant = element->suivant;
    nouv_element->precedent = element;
    if (element->suivant == NULL)
      liste->queue = nouv_element;
    else
      element->suivant->precedent = nouv_element;
    element->suivant = nouv_element;
  }
  liste->taille++;
  return (0);
}

int dlist_rem_prev(DList * liste, DListElmt * element, void ** donnee)
{
  DListElmt * nouv_element;

  if (element == NULL && dlist_size(liste) != 0)
    return (-1);
  nouv_element = (DListElmt *) malloc(sizeof(DListElmt));
  if (nouv_element == NULL)
    return (-1);
  nouv_element->donnee = (void *) donnee;
  if (dlist_size(liste) == 0) {
    liste->tete = nouv_element;
    liste->tete->precedent = NULL;
    liste->tete->suivant = NULL;
    liste->queue = nouv_element;
  }
  else {
    nouv_element->suivant = element;
    nouv_element->precedent = element->precedent;
    if (element->precedent == NULL)
      liste->tete = nouv_element;
    else
      element->precedent->suivant = nouv_element;
    element->precedent = nouv_element;
  }
  liste->taille++;
  return (0);
}

int dlist_remove(DList * liste, DListElmt * element ,void ** donnee)
{
  if (element == NULL || dlist_size(liste) == 0)
    return (-1);
  * donnee = element->donnee;
  if (element == liste->tete) { /*Suppression tête de liste*/
    liste->tete = element->suivant;
    if (liste->tete == NULL)
      liste->queue = NULL;
    else
      element->suivant->precedent = NULL;
  }
  else { /*Supression autre que tête*/
    element->precedent->suivant = element->suivant;
    if (element->suivant == NULL)
      liste->queue = element->precedent;
    else
      element->suivant->precedent = element->precedent;
  }
  free(element);
  liste->taille--;
  return (0);
}
