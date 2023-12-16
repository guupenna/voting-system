#if !defined(RELATORIO_H)
#define RELATORIO_H

#include "eleicao.h"

void imprimeCandidato(const Candidato &candidato);
void imprimeTodosCandidatos(Eleicao &eleicao);
void imprimePartido(Partido &partido);
void imprimeTodosPartidos(Eleicao &eleicao);
void numeroVagas(Eleicao &eleicao);
void candidatosEleitos(Eleicao &eleicao, string cargo);
void candidatosMaisVotados(Eleicao &eleicao);
void candidatosNaoEleitosMasSeriamMajoritariamente(Eleicao &eleicao);
void candidatosEleitosQueNaoSeriamMajoritariamente(Eleicao &eleicao);
void votacaoPartidos(Eleicao &eleicao);
void primeiroUltimoColocadoPartidos(Eleicao &eleicao);
void eleitosPorGenero(Eleicao &eleicao);
void eleitosPorFaixaEtaria(Eleicao &eleicao, const string &dataAtual);
void votacaoGeral(Eleicao &eleicao);

#endif // RELATORIO_H
