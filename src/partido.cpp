#include "partido.h"
#include <iostream>

Partido::Partido(const string &NR_PARTIDO, const string &SG_PARTIDO) : NR_PARTIDO(NR_PARTIDO), SG_PARTIDO(SG_PARTIDO)
{ QT_VOTOS_LEGENDA = 0; }

const string &Partido::getNR_PARTIDO() const
{ return NR_PARTIDO; }

const string &Partido::getSG_PARTIDO() const
{ return SG_PARTIDO; }

map<string, Candidato> &Partido::getCandidatosPartido()
{ return candidatos; }

void Partido::addCandidatos(const Candidato &candidato)
{
    if(candidatos.find(candidato.getNR_CANDIDATO()) == candidatos.end()) {
        candidatos.insert(pair<string, Candidato> (candidato.getNR_CANDIDATO(), candidato));
    }
}

void Partido::setCandidatoMaisVotado(Candidato &maisVotado) const
{
    bool first = false;
    for(const pair<string, Candidato> candidato : candidatos) {
        if(first == false)
        {
            maisVotado = candidato.second;
            first = true;
        }
        if(candidato.second.getQT_VOTOS() > maisVotado.getQT_VOTOS()){
            maisVotado = candidato.second;
        }
    }
}

void Partido::setCandidatoMenosVotado(Candidato &menosVotado) const
{
    bool first = false;
    for(const pair<string, Candidato> candidato : candidatos) {
        if(first == false)
        {
            menosVotado = candidato.second;
            first = true;
        }
        if(candidato.second.getQT_VOTOS() < menosVotado.getQT_VOTOS()){
            menosVotado = candidato.second;
        }
    }
}

void Partido::addVotosPartidoLegenda(int votos)
{ QT_VOTOS_LEGENDA += votos; }

int Partido::getQT_VOTOS_NOMINAIS() const
{
    int QT_VOTOS_NOMINAIS = 0;

    for(const pair<string, Candidato> candidato : candidatos) {
        QT_VOTOS_NOMINAIS += candidato.second.getQT_VOTOS();
    }

    return QT_VOTOS_NOMINAIS;
}

int Partido::getQT_VOTOS_LEGENDA() const
{ return QT_VOTOS_LEGENDA; }

int Partido::getQT_VOTOS_TOTAIS() const
{ return QT_VOTOS_LEGENDA + getQT_VOTOS_NOMINAIS(); }

int Partido::getCandidatosEleitos() const
{
    int eleitos = 0;

    for(const pair<string, Candidato> candidato : candidatos) {
        if(candidato.second.estáApto()) {
            eleitos++;
        }
    }

    return eleitos;
}