#if !defined(CANDIDATO_H)
#define CANDIDATO_H

using namespace std;

#include <string>

class Candidato {
    string CD_CARGO;
    string CD_SITUACAO_CANDIDATO_TOT;
    string NR_CANDIDATO;
    string NM_URNA_CANDIDATO;
    string NR_PARTIDO;
    string SG_PARTIDO;
    string NR_FEDERACAO;
    string DT_NASCIMENTO;
    string CD_SIT_TOT_TURNO;
    string CD_GENERO;
    string NM_TIPO_DESTINACAO_VOTOS;
    int QT_VOTOS;

    public:
    Candidato() {};
    Candidato(const string &CD_CARGO,
        const string &CD_SITUACAO_CANDIDATO_TOT,
        const string &NR_CANDIDATO,
        const string &NM_URNA_CANDIDATO,
        const string &NR_PARTIDO,
        const string &SG_PARTIDO,
        const string &NR_FEDERACAO,
        const string &DT_NASCIMENTO,
        const string &CD_SIT_TOT_TURNO,
        const string &CD_GENERO,
        const string &NM_TIPO_DESTINACAO_VOTOS);
    
    void addVotosCandidato(int votos);
    bool estáApto() const;
    const string &getCD_CARGO() const;
    const string &getCD_SITUACAO_CANDIDATO_TOT() const;
    const string &getNR_CANDIDATO() const;
    const string &getNM_URNA_CANDIDATO() const;
    const string &getNR_PARTIDO() const;
    const string &getSG_PARTIDO() const;
    const string &getNR_FEDERACAO() const;
    const string &getDT_NASCIMENTO() const;
    const string &getCD_SIT_TOT_TURNO() const;
    const string &getCD_GENERO() const;
    const string &getNM_TIPO_DESTINACAO_VOTOS() const;
    int getQT_VOTOS() const;
    int getIdadeEmDias(const string& dataAtual);
};

#endif // CANDIDATO_H
