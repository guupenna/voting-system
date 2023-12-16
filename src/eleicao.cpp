#include "eleicao.h"
#include "relatorio.h"
#include "iostream"
#include <vector>
#include <algorithm>

void Eleicao::addCandidato(const Candidato &candidato)
{ candidatos.insert(std::make_pair(candidato.getNR_CANDIDATO(), candidato)); }

void Eleicao::addPartido(const Partido &partido)
{ partidos.insert(std::make_pair(partido.getNR_PARTIDO(), partido)); }

map<string, Candidato> &Eleicao::getCandidatos()
{ return candidatos; }

map<string, Partido> &Eleicao::getPartidos()
{ return partidos; }

void Eleicao::computaVoto(string NR_VOTAVEL, int QT_VOTOS)
{
    if(partidos.find(NR_VOTAVEL) != partidos.end())
    {
        partidos.at(NR_VOTAVEL).addVotosPartidoLegenda(QT_VOTOS);
    }

    if(candidatos.find(NR_VOTAVEL) != candidatos.end())
    {
        if(candidatos.at(NR_VOTAVEL).getNM_TIPO_DESTINACAO_VOTOS() == "Válido (legenda)") 
            partidos.at(candidatos.at(NR_VOTAVEL).getNR_PARTIDO()).addVotosPartidoLegenda(QT_VOTOS);
        else
        {
            candidatos.at(NR_VOTAVEL).addVotosCandidato(QT_VOTOS);
            partidos.at(candidatos.at(NR_VOTAVEL).getNR_PARTIDO()).getCandidatosPartido().at(NR_VOTAVEL).addVotosCandidato(QT_VOTOS);
        }
    }
}

void Eleicao::calculaVagas()
{
    for (const pair<string, Candidato> candidato : getCandidatos()) {
        if (candidato.second.estáApto()) {
            vagas++;
        }
    }
}

int Eleicao::getVagas() const
{ return vagas; }


void Eleicao::ordenaCandidatosQtVoto(vector<Candidato> &lista)
{
    try {
        for (const pair<string, Candidato> candidato : candidatos)
        lista.push_back(candidato.second);

        sort(lista.begin(), lista.end(), [](Candidato& a, Candidato& b) {
            return a.getQT_VOTOS() > b.getQT_VOTOS();
        });
    }
    catch(const out_of_range& e)
    {
        cerr << e.what() << '\n';
    }
}

void Eleicao::ordenaPartidosQtVoto(vector<Partido> &lista)
{
    try {
        for (const pair<string, Partido> partido : partidos)
        lista.push_back(partido.second);

        sort(lista.begin(), lista.end(), [](const Partido& a, const Partido& b) {
            return a.getQT_VOTOS_TOTAIS() > b.getQT_VOTOS_TOTAIS();
        });
    }
    catch(const out_of_range& e)
    {
        cerr << e.what() << '\n';
    }
}

void Eleicao::ordenaPartidosCandidatoMaisVotado(vector<Partido> &lista, Candidato &maisVotado)
{
    try {
        for (const pair<string, Partido> partido : partidos) {
            lista.push_back(partido.second);
        }

        sort(lista.begin(), lista.end(), [&maisVotado](const Partido& a, const Partido& b) {
            int QT_VOTOS_A = 0, QT_VOTOS_B = 0;

            if(a.getQT_VOTOS_NOMINAIS() != 0)
            {
                a.setCandidatoMaisVotado(maisVotado);
                QT_VOTOS_A = maisVotado.getQT_VOTOS();
            }

            if(b.getQT_VOTOS_NOMINAIS() != 0)
            {
                b.setCandidatoMaisVotado(maisVotado);
                QT_VOTOS_B = maisVotado.getQT_VOTOS();
            }

            return QT_VOTOS_A > QT_VOTOS_B;
        });
    }
    catch(const out_of_range &e)
    {
        cerr << e.what() << '\n';
    }

}