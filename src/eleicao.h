#if !defined(ELEICAO_H)
#define ELEICAO_H

#include "candidato.h"
#include "partido.h"
#include <string>
#include <map>
#include <vector>

class Eleicao {
    map<string, Candidato> candidatos;
    map<string, Partido> partidos;
    int vagas;

    public:
    Eleicao() {};
    void addCandidato(const Candidato &candidato);
    void addPartido(const Partido &partido);
    map<string, Candidato> &getCandidatos();
    map<string, Partido> &getPartidos();
    void computaVoto(string NR_VOTAVEL, int QT_VOTOS);
    void calculaVagas();
    int getVagas() const;
    void ordenaCandidatosQtVoto(vector<Candidato> &lista);
    void ordenaPartidosQtVoto(vector<Partido> &lista);
    void ordenaPartidosCandidatoMaisVotado(vector<Partido> &lista, Candidato &maisVotado);
};

#endif // ELEICAO_H
