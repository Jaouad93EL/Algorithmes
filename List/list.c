#include "list.h"

void list_init(List * liste, void (* detruire)(void * donnee))
{
  liste->taille = 0;
  liste->detruire = detruire;
  liste->tete = NULL;
  liste->queue = NULL;
}

void list_destroy(List * liste)
{
  void * donnee;

  while (list_size(liste) > 0)
    if (list_rem_next(liste, NULL, (void **)&donnee) == 0 && liste->detruire != NULL)
      liste->detruire(donnee);
  memset(liste, 0, sizeof(List));
}

int list_ins_next(List * liste, ListElmt * element, const void * donnee)
{
  ListElmt * nouv_element = (ListElmt *) malloc(sizeof(ListElmt));
  if (nouv_element == NULL)
    return (-1);
  nouv_element->donnee = (void *) donnee;
  if (element == NULL) { /*Insertion tête de liste*/
    if (list_size(liste) == 0)
      liste->queue = nouv_element;
    nouv_element->suivant = liste->tete;
    liste->tete = nouv_element;
  }
  else { /*Insertion autre que tête de liste*/
    if (element->suivant == NULL)
      liste->queue = nouv_element;
    nouv_element->suivant = element->suivant;
    element->suivant = nouv_element;
  }
  liste->taille++;
  return (0);
}

int list_rem_next(List * liste, ListElmt * element, void ** donnee)
{
  ListElmt * ancien_element;
  if (list_size(liste) == 0)
    return (-1);
  if (element == NULL) { /*Supression tête de liste*/
    * donnee = liste->tete->donnee;
    ancien_element = liste->tete;
    liste->tete = liste->tete->suivant;
    if (list_size(liste) == 1)
      liste->queue = NULL;
  }
  else { /*Supression autre que tête de liste*/
    if (element->suivant == NULL)
      return (-1);
    * donnee = element->suivant->donnee;
    ancien_element = element->suivant;
    element->suivant = element->suivant->suivant;
    if (element->suivant == NULL)
      liste->queue = element;
  }
  free(ancien_element);
  liste->taille--;
  return (0);
}

void list_aff_string(List * liste)
{
  ListElmt * aff_element = liste->tete;

  for (int i = 0; i < list_size(liste); ++i) {
    printf("%s\n",  *((char **) list_data(aff_element)));
    aff_element = list_next(aff_element);
  }
}

void list_aff_number(List * liste)
{
  ListElmt * aff_element = liste->tete;

  for (int i = 0; i < list_size(liste); ++i) {
    printf("%d\n",  *((int *) list_data(aff_element)));
    aff_element = list_next(aff_element);
  }
}
