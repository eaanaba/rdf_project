/*****
** Varias funciones utiles.
*****/

void myfree(void **ptr)
{
  free(*ptr);
  *ptr = NULL;
}