#if !defined(LEITOR_H)
#define LEITOR_H

#include "eleicao.h"
#include <string>

void leCandidatos(Eleicao &e, string csvCandidatos, string cargo);
void leVotacao(Eleicao &e, string csvVotacao, string cargo);

#endif // LEITOR_H
