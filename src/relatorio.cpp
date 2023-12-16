#include "relatorio.h"
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>

void imprimeCandidato(const Candidato &candidato)
{
    cout << candidato.getCD_CARGO() << "\\" << candidato.getCD_GENERO() << "\\" << candidato.getCD_SIT_TOT_TURNO()
    << "\\" << candidato.getCD_SITUACAO_CANDIDATO_TOT() << "\\" << candidato.getDT_NASCIMENTO() << "\\" <<
    candidato.getNM_TIPO_DESTINACAO_VOTOS() << "\\" << candidato.getNM_URNA_CANDIDATO() << "\\" <<
    candidato.getNR_CANDIDATO() << "\\" << candidato.getNR_FEDERACAO() << "\\" << candidato.getNR_PARTIDO()
    << "\\" << candidato.getSG_PARTIDO() << "\\" << candidato.getQT_VOTOS();
}

void imprimeTodosCandidatos(Eleicao &eleicao)
{
    map<string, Candidato>::iterator it;
    for (it = eleicao.getCandidatos().begin(); it != eleicao.getCandidatos().end(); ++it) {
        imprimeCandidato(it->second);
        cout << '\n';
    }
}

void imprimePartido(Partido &partido)
{

    cout << partido.getNR_PARTIDO() << "\\" << partido.getSG_PARTIDO() << "-------> LEGENDA:" << partido.getQT_VOTOS_LEGENDA() << "-------> NOMINAIS:" << partido.getQT_VOTOS_NOMINAIS(); 

    // map<string, Candidato>::iterator it;
    // for (it = partido.getCandidatosPartido().begin(); it != partido.getCandidatosPartido().end(); ++it) {
    //     imprimeCandidato(it->second);
    //     cout << '\n';
    // }
}

void imprimeTodosPartidos(Eleicao &eleicao)
{
    map<string, Partido>:: iterator it;
    for (it = eleicao.getPartidos().begin(); it != eleicao.getPartidos().end(); ++it) {
        imprimePartido(it->second);
        cout << "\n\n";
    }
}

void numeroVagas(Eleicao &eleicao)
{ cout << "Número de vagas: " << eleicao.getVagas() << "\n\n"; }

void candidatosEleitos(Eleicao &eleicao, string cargo) 
{
    if(cargo == "--federal")
        cout << "Deputados federais eleitos:\n";
    else if(cargo == "--estadual")
        cout << "Deputados estaduais eleitos:\n";

    locale brLocale("pt_BR.UTF-8");
    cout.imbue(brLocale);

    vector<Candidato> lista;
    eleicao.ordenaCandidatosQtVoto(lista);

    int colocacao = 1;

    for (const Candidato& candidato : lista) {
        if (candidato.estáApto()) {
            string federacao = "";
            if (candidato.getNR_FEDERACAO() != "-1")
                federacao = "*";

            cout << colocacao << " - " << federacao << candidato.getNM_URNA_CANDIDATO() << " (" << candidato.getSG_PARTIDO() << ", " << fixed << setprecision(2) << candidato.getQT_VOTOS() << " votos)" << endl;
            colocacao++;
        }
    }

    cout << '\n';
}

void candidatosMaisVotados(Eleicao &eleicao)
{
    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):\n";

    int colocacao = 1;

    locale brLocale("pt_BR.UTF-8");
    cout.imbue(brLocale);
    cout << fixed << setprecision(2);

    vector<Candidato> lista;
    eleicao.ordenaCandidatosQtVoto(lista);

    for (int i = 0; i < eleicao.getVagas() && i < (int)lista.size(); ++i) {
        string federacao = (lista[i].getNR_FEDERACAO() != "-1") ? "*" : "";
        cout << colocacao << " - " << federacao << lista[i].getNM_URNA_CANDIDATO() << " (" << lista[i].getSG_PARTIDO() << ", " << lista[i].getQT_VOTOS() << " votos)\n";

        colocacao++;
    }

    cout << '\n';
}

void candidatosNaoEleitosMasSeriamMajoritariamente(Eleicao &eleicao) {
    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:\n";
    cout << "(com sua posição no ranking de mais votados)\n";

    int colocacao = 1;

    locale brLocale("pt_BR.utf8");
    cout.imbue(brLocale);

    vector<Candidato> lista;
    eleicao.ordenaCandidatosQtVoto(lista);

    for (int i = 0; i < eleicao.getVagas(); i++) {
        if (lista[i].estáApto() == false) {
            string federacao = "";
            if (lista[i].getNR_FEDERACAO() != "-1")
                federacao = "*";

            cout << colocacao << " - " << federacao << lista[i].getNM_URNA_CANDIDATO() << " (" << lista[i].getSG_PARTIDO() << ", " << fixed << setprecision(2) << lista[i].getQT_VOTOS() << " votos)" << endl;
        }
        colocacao++;
    }

    cout << '\n';
}

void candidatosEleitosQueNaoSeriamMajoritariamente(Eleicao &eleicao) {
    cout << "Eleitos, que se beneficiaram do sistema proporcional:\n";
    cout << "(com sua posição no ranking de mais votados)\n";

    int colocacao = eleicao.getVagas()+1;

    locale brLocale("pt_BR.utf8");
    cout.imbue(brLocale);

    vector<Candidato> lista;
    eleicao.ordenaCandidatosQtVoto(lista);

    for (long unsigned int i = eleicao.getVagas(); i < lista.size(); i++) {
        if (lista[i].getQT_VOTOS() < lista[i-1].getQT_VOTOS() && lista[i].estáApto()) {
            string federacao = "";
            if (lista[i].getNR_FEDERACAO() != "-1")
                federacao = "*";

            cout << colocacao << " - " << federacao << lista[i].getNM_URNA_CANDIDATO() << " (" << lista[i].getSG_PARTIDO() << ", " << fixed << setprecision(2) << lista[i].getQT_VOTOS() << " votos)" << endl;
        }
        colocacao++;
    }

    cout << '\n';
}

void votacaoPartidos(Eleicao &eleicao)
{
    cout << "Votação dos partidos e número de candidatos eleitos:\n";

    int colocacao = 1;

    locale brLocale("pt_BR.utf8");
    cout.imbue(brLocale);

    vector<Partido> lista;
    eleicao.ordenaPartidosQtVoto(lista);

    for (size_t i = 0; i < lista.size(); i++) {
        cout << colocacao << " - " << lista[i].getSG_PARTIDO() << " - " << lista[i].getNR_PARTIDO() << ", " << fixed << setprecision(2) << lista[i].getQT_VOTOS_TOTAIS() << " votos (" << lista[i].getQT_VOTOS_NOMINAIS() << " nominais e " << lista[i].getQT_VOTOS_LEGENDA() << " de legenda), " << lista[i].getCandidatosEleitos() << " candidatos eleitos\n";
        colocacao++;
    }

    cout << '\n';
}

void primeiroUltimoColocadoPartidos(Eleicao &eleicao)
{
    cout << "Primeiro e último colocados de cada partido:\n";

    int colocacao = 1;

    locale brLocale("pt_BR.utf8");
    cout.imbue(brLocale);

    Candidato maisVotado, menosVotado;
    vector<Partido> lista;
    eleicao.ordenaPartidosCandidatoMaisVotado(lista, maisVotado);

        for (const Partido& partido : lista) {
            if (partido.getQT_VOTOS_NOMINAIS() == 0) {
                continue;
            }

            partido.setCandidatoMaisVotado(maisVotado);

            cout << colocacao << " - " << partido.getSG_PARTIDO() << " - " << partido.getNR_PARTIDO() << ", " << maisVotado.getNM_URNA_CANDIDATO() << " (" << maisVotado.getNR_CANDIDATO() << ", " << fixed << setprecision(2) << maisVotado.getQT_VOTOS() << " votos) / ";
            
            partido.setCandidatoMenosVotado(menosVotado);

            cout << menosVotado.getNM_URNA_CANDIDATO() << " (" << menosVotado.getNR_CANDIDATO() << ", " << fixed << setprecision(2) << menosVotado.getQT_VOTOS() << " votos)\n";

            colocacao++;
    }

    cout << '\n';
}

void eleitosPorFaixaEtaria(Eleicao &eleicao, const string &dataAtual)
{
    int idade0_30 = 0, idade30_40 = 0, idade40_50 = 0, idade50_60 = 0, idade60_ = 0;

    for(pair<string, Candidato>candidato : eleicao.getCandidatos()){
        int anosCandidato = candidato.second.getIdadeEmDias(dataAtual)/365;
        if(candidato.second.estáApto() == true){
            if(anosCandidato < 30){
                idade0_30++;
            }else if(anosCandidato >= 30 && anosCandidato < 40){
                idade30_40++;
            }else if(anosCandidato >= 40 && anosCandidato < 50){
                idade40_50++;
            }else if(anosCandidato >= 50 && anosCandidato < 60){
                idade50_60++;
            }else if(anosCandidato >= 60){
                idade60_++;
            }
        }
    }

    double idade0_30_percent = (double)idade0_30 / (double)eleicao.getVagas() * 100;
    double idade30_40_percent = (double)idade30_40 / (double)eleicao.getVagas() * 100;
    double idade40_50_percent = (double)idade40_50 / (double)eleicao.getVagas() * 100;
    double idade50_60_percent = (double)idade50_60 / (double)eleicao.getVagas() * 100;
    double idade60_percent = (double)idade60_ / (double)eleicao.getVagas() * 100;

    cout << "Eleitos, por faixa etária (na data da eleição):\n";
    
    cout << "      Idade < 30:" << setw(2) << idade0_30 << " (" << fixed << setprecision(2) << idade0_30_percent << "%)\n";
    cout << "30 <= Idade < 40:" << setw(2) << idade30_40 << " (" << fixed << setprecision(2) << idade30_40_percent << "%)\n";
    cout << "40 <= Idade < 50:" << setw(2) << idade40_50 << " (" << fixed << setprecision(2) << idade40_50_percent << "%)\n";
    cout << "50 <= Idade < 60:" << setw(2) << idade50_60 << " (" << fixed << setprecision(2) << idade50_60_percent << "%)\n";
    cout << "60 <= Idade     :" << setw(2) << idade60_ << " (" << fixed << setprecision(2) << idade60_percent << "%)\n";

    cout << '\n';
}

void eleitosPorGenero(Eleicao &eleicao)
{
    int feminino = 0, masculino = 0;

    for(const pair<string, Candidato> candidato : eleicao.getCandidatos()){
        if(candidato.second.estáApto()){
            if(candidato.second.getCD_GENERO() == "4")
                feminino++;
            else if(candidato.second.getCD_GENERO() == "2")
                masculino++;
        }
    }

    double feminino_percent = (double)feminino / (double)eleicao.getVagas() * 100;
    double masculino_percent = (double)masculino / (double)eleicao.getVagas() * 100;

    cout << "Eleitos, por gênero:\n";
    
    cout << "Feminino: " << setw(2) << feminino << " (" << fixed << setprecision(2) << feminino_percent << "%)\n";
    cout << "Masculino: " << setw(2) << masculino << " (" << fixed << setprecision(2) << masculino_percent << "%)\n";

    cout << '\n';
}

void votacaoGeral(Eleicao &eleicao)
{
    int votosNominais = 0, votosLegenda = 0, votosTotais = 0;

    for (const pair<string, Partido> partido : eleicao.getPartidos()) {
        votosNominais += partido.second.getQT_VOTOS_NOMINAIS();
        votosLegenda += partido.second.getQT_VOTOS_LEGENDA();
        votosTotais += partido.second.getQT_VOTOS_TOTAIS();
    }

    double votosNominaisPercent = (double)votosNominais / (double)votosTotais * 100;
    double votosLegendaPercent = (double)votosLegenda / (double)votosTotais * 100;

    cout << "Total de votos válidos:    " << setw(5) << votosTotais << '\n' << "Total de votos nominais:   " << setw(5) << votosNominais << " (" << fixed << setprecision(2) << votosNominaisPercent << "%)\n" << "Total de votos de legenda: " << setw(5) << votosLegenda << " (" << fixed << setprecision(2) << votosLegendaPercent << "%)\n";

    cout << '\n';
}









