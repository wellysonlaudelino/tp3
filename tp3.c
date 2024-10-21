/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* coloque aqui as funções auxiliares que precisar neste arquivo */

void imprime_vetor (struct racional **vet, int tam)
{
  int i;
  for (i=0; i<tam; i++)
  {
    // imprimir sem espaço
    if (i == tam - 1)
    {
     imprime_r(vet[i]);
     return;
    }
    imprime_r(vet[i]);
    printf(" ");  
  }
}


void ordena_vetor (struct racional **v, int tam)
{
  int i, a;
  struct racional *temp;
    
  // Bubble Sort: Percorre o vetor várias vezes, trocando elementos adjacentes.
  for (i = 0; i < tam ; i++)
  {
    // Compara elementos adjacentes
    for (a = 0; a < tam - i  - 1; a++)  
    {
      // Se v[a] é maior que v[a+1], troque-os
      if (compara_r(v[a], v[a + 1]) == 1) 
      {
        // Realiza a troca dos elementos
        temp = v[a];
        v[a] = v[a + 1];
        v[a + 1] = temp;
      }
    }
  }
}


void le_vetor (struct racional **vi, int tam)
{
  int i, le1, le2;
  for (i=0; i<tam; i++)
  {
    scanf ("%d %d", &le1, &le2);
    vi[i] = cria_r(le1, le2);
  }
}


int elimina_invalidos (struct racional **vi, struct racional **v, int tam)
{
  int i, j, a;
  j = 0;
  a = tam - 1;
  for (i = 0; i <= a; i++) 
  {
    // Insere em v, valores que não são inválidos
    if (valido_r(vi[i])) 
    {
      v[j] = vi[i];
      j++;
    } 
    else
    {
      // Procura por válidos de trás para frente
      while (a > i && valido_r(vi[a]) == 0)
        a--;
      // Se encontrar um válido
      if (a > i && valido_r(vi[a])) 
      {
        v[j] = vi[a];
        j++;
        a--; 
      }
    }
  }
  // Retorna o novo tamanho
  return j; 
}


struct racional *somar(struct racional **v, int novo_tam)
{
  int i;
  struct racional *soma;
  if (novo_tam == 0)
    return NULL;
  // soma será armazenada nesse novo endereço
  soma = cria_r(v[0]->num, v[0]->den);
  if (novo_tam == 0)
  {
    printf ("SOMA = 0\n");
    return NULL;
   }
  if (novo_tam > 1)
  {
    for (i=0; i<novo_tam-1; i++)
    {  
      soma_r (soma, v[i+1], soma);
    }
  }
  return soma;
}


void libera_racional (struct racional **vet, int tam)
{
  int i;
  for (i=0; i<tam; i++)
  {
    destroi_r (vet[i]);
    vet[i] = NULL;
  }
}


void atribui_null (struct racional **v, int tam)
{
  int i;
  for (i=0; i<tam; i++)
    v[i] = NULL;
}


/* programa principal */
int main ()
{
  int n, j;
  struct racional **v, **vi;
  struct racional *soma;
 
  scanf("%d", &n);
  vi = malloc(n * sizeof(struct racional *));
  v = malloc(n * sizeof(struct racional *));
  if (v == NULL || vi == NULL) 
    return 1;
    
  // se o parametro passado for inválido, finaliza o programa
  if ((n > 100) || (n < 0)) 
  {
    printf ("PARAMETRO INVALIDO");
    printf ("\n");
    return 0;
  }
  le_vetor (vi,n);
  printf ("VETOR = ");
  // imprime vetor original simplificado
  imprime_vetor (vi, n); 
  printf ("\n");
  // j recebe o tamanho do novo vetor
  j = elimina_invalidos (vi, v, n);
  printf ("VETOR = ");
  // imprime vetor de validos simplificado
  imprime_vetor(v, j); 
  printf ("\n");
  
  ordena_vetor (v, j);
  printf ("VETOR = ");
  // imprime vetor ordenado
  imprime_vetor (v, j); 
  printf ("\n");

  soma = somar (v, j);
  if (soma == NULL)
   printf ("SOMA = 0\n");
  else
  {
    printf ("SOMA = ");
    imprime_r (soma);
    printf ("\n");
  }
  libera_racional (vi, n);
  atribui_null (v, n);
  printf ("VETOR = ");
  // imprime vetor com memoria liberada
  imprime_vetor (v, j); 
  printf ("\n");
  free (v);
  free (vi);
  free (soma);
  return (0) ;
}
