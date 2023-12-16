#include "leitor.h"
#include "relatorio.h"

int main(int argc, char *argv[]) {
    Eleicao e;
    leCandidatos(e, argv[2], argv[1]);
    leVotacao(e, argv[3], argv[1]);

    numeroVagas(e);
    candidatosEleitos(e, argv[1]);
    candidatosMaisVotados(e);
    candidatosNaoEleitosMasSeriamMajoritariamente(e);
    candidatosEleitosQueNaoSeriamMajoritariamente(e);
    votacaoPartidos(e);
    primeiroUltimoColocadoPartidos(e);
    eleitosPorFaixaEtaria(e, argv[4]);
    eleitosPorGenero(e);
    votacaoGeral(e);
}