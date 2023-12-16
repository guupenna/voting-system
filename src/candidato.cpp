#include "candidato.h"

Candidato::Candidato(const string &CD_CARGO,
    const string &CD_SITUACAO_CANDIDATO_TOT,
    const string &NR_CANDIDATO,
    const string &NM_URNA_CANDIDATO,
    const string &NR_PARTIDO,
    const string &SG_PARTIDO,
    const string &NR_FEDERACAO,
    const string &DT_NASCIMENTO,
    const string &CD_SIT_TOT_TURNO,
    const string &CD_GENERO,
    const string &NM_TIPO_DESTINACAO_VOTOS)
        : CD_CARGO(CD_CARGO), CD_SITUACAO_CANDIDATO_TOT(CD_SITUACAO_CANDIDATO_TOT),
        NR_CANDIDATO(NR_CANDIDATO), NM_URNA_CANDIDATO(NM_URNA_CANDIDATO), NR_PARTIDO(NR_PARTIDO),
        SG_PARTIDO(SG_PARTIDO), NR_FEDERACAO(NR_FEDERACAO), DT_NASCIMENTO(DT_NASCIMENTO),
        CD_SIT_TOT_TURNO(CD_SIT_TOT_TURNO), CD_GENERO(CD_GENERO),
        NM_TIPO_DESTINACAO_VOTOS(NM_TIPO_DESTINACAO_VOTOS)
{ QT_VOTOS = 0; }

void Candidato::addVotosCandidato(int votos)
{ QT_VOTOS += votos; }

bool Candidato::estáApto() const
{
    if(CD_SIT_TOT_TURNO == "2" || CD_SIT_TOT_TURNO == "3")
        return true;
    else
        return false;
}

const string &Candidato::getCD_CARGO() const
{ return CD_CARGO; }

const string &Candidato::getCD_SITUACAO_CANDIDATO_TOT() const
{ return CD_SITUACAO_CANDIDATO_TOT; }

const string &Candidato::getNR_CANDIDATO() const
{ return NR_CANDIDATO; }

const string &Candidato::getNM_URNA_CANDIDATO() const
{ return NM_URNA_CANDIDATO; }

const string &Candidato::getNR_PARTIDO() const
{ return NR_PARTIDO; }

const string &Candidato::getSG_PARTIDO() const
{ return SG_PARTIDO; }

const string &Candidato::getNR_FEDERACAO() const
{ return NR_FEDERACAO; }

const string &Candidato::getDT_NASCIMENTO() const
{ return DT_NASCIMENTO; }

const string &Candidato::getCD_SIT_TOT_TURNO() const
{ return CD_SIT_TOT_TURNO; }

const string &Candidato::getCD_GENERO() const
{ return CD_GENERO; }

const string &Candidato::getNM_TIPO_DESTINACAO_VOTOS() const
{ return NM_TIPO_DESTINACAO_VOTOS; }

int Candidato::getQT_VOTOS() const
{ return QT_VOTOS; }

int Candidato::getIdadeEmDias(const string& dataAtual) {
    int idade = 0;

    int diferencaAnos = stoi(dataAtual.substr(6, 9)) - stoi(DT_NASCIMENTO.substr(6, 9));
    int diferencaMes = stoi(dataAtual.substr(3, 4)) - stoi(DT_NASCIMENTO.substr(3, 4));
    int diferencaDia = stoi(dataAtual.substr(1, 2)) - stoi(DT_NASCIMENTO.substr(1, 2));

    idade += diferencaAnos * 365;
    idade += diferencaMes * 30;
    idade += diferencaDia;

    return idade;
}