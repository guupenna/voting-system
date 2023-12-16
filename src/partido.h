#if !defined(PARTIDO_H)
#define PARTIDO_H

using namespace std;

#include "candidato.h"
#include <string>
#include <map>

class Partido {
    string NR_PARTIDO;
    string SG_PARTIDO;
    int QT_VOTOS_LEGENDA;
    map<string, Candidato> candidatos;

    public:
    Partido() {};
    Partido(const string &NR_PARTIDO, const string &SG_PARTIDO);
    const string &getNR_PARTIDO() const;
    const string &getSG_PARTIDO() const;
    map<string, Candidato> &getCandidatosPartido();
    void addCandidatos(const Candidato &candidato);
    void setCandidatoMaisVotado(Candidato &maisVotado) const;
    void setCandidatoMenosVotado(Candidato &menosVotado) const;
    void addVotosPartidoLegenda(int votos);
    int getQT_VOTOS_NOMINAIS() const;
    int getQT_VOTOS_LEGENDA() const;
    int getQT_VOTOS_TOTAIS() const;
    int getCandidatosEleitos() const;
};

#endif // PARTIDO_H
