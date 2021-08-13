#include <stdio.h>
#include <string.h>

/**
 * Definição das constantes
 */
#define ACEITA  1
#define REJEITA 0

/**
 * Funções
 */
void console(int, int);
int q0(int);
int q1(int);
int q2(int);

/**
 * Sentença
 */
char sentence[255];

/**
 * Os Método principais :
 *
 * argc quantidade de argumentos na linha de comando (nao utilizado)
 * argv argumentos da linha de comando (nao utilizado)
 * o return é saida para o sistema operacional (padrao 0)
 */
int main(int argc, char** argv)
{
  printf("Analise a sentença: ");
  fgets(sentence, 255, stdin);

  if(strchr(sentence, '$') != 0)
  {
    sentence[strlen(sentence) - 1] = '\0';
    printf("A sentença \"%s\" é inválida\n", sentence);
    return 1;
  }

  sentence[strlen(sentence) - 1] = '$';

  printf("Observação: \"$\" representa o fim da sentença");

  if(q0(0))
  {
    printf(" - ACEITA\n");
  }
  else
  {
    printf(" - REJEITA\n");
  }

  return 0;
}

/**
 * Imprime a execucao do automato finito deterministico
 */
void console(int state, int symbol)
{
  int i;

  int length = strlen(sentence);

  printf("\nq%i - ", state);

  for(i = 0; i < length; i++)
  {
    if(i != symbol)
    {
      printf(" %c ", sentence[i]);
    }
    else
    {
      printf("[%c]", sentence[i]);
    }
  }
}

/**
 * Estado q0 (inicial)
 */
int q0(int symbol)
{
  console(0, symbol);

  switch(sentence[symbol++])
  {
    case 'a': return q0(symbol);
    case 'c': return q0(symbol);
    case 'b': return q1(symbol);
    default : return REJEITA;
  }
}

/**
 * Estado q1
 *
 * o symbol simbolo corrente
 * o return ACEITA ou REJEITA
 */
int q1(int symbol)
{
  console(1, symbol);

  switch(sentence[symbol++])
  {
    case 'a': return q1(symbol);
    case 'c': return q1(symbol);
    case 'b': return q2(symbol);
    default : return REJEITA;
  }
}

int q2(int symbol)
{
  console(2, symbol);

  switch(sentence[symbol++])
  {
    case 'a': return q2(symbol);
    case 'b': return q2(symbol);
    case 'c': return q2(symbol);
    case '$': return ACEITA;
    default : return REJEITA;
  }
}
