#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "eleicao.h"
#include "relatorio.h"

using namespace std;

string _iso_8859_1_to_utf8(string &str)
{
  // adaptado de: https://stackoverflow.com/a/39884120 :-)
  string strOut;
  for (string::iterator it = str.begin(); it != str.end(); ++it)
  {
    uint8_t ch = *it;
    if (ch < 0x80)
    {
      // já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
      strOut.push_back(ch);
    }
    else
    {
      // está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
      // o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
      strOut.push_back(0b11000000 | (ch >> 6));
      // o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
      strOut.push_back(0b10000000 | (ch & 0b00111111));
    }
  }
  return strOut;
}

void leCandidatos(Eleicao &e, string fileCandidatos, string cargo) {
    try
    {
        ifstream inputStream(fileCandidatos);
        string line;

        int idCargo;
        if(cargo == "--federal")
            idCargo = 6;
        else if(cargo == "--estadual")
            idCargo = 7;
        else
            throw invalid_argument("Argumento inválido referente ao cargo do deputado.\n");
        
        while(getline(inputStream, line))
        {
            vector<string> columns;

            istringstream lineStream(line);

            string str, strConvertida;

            while(getline(lineStream, str, ';'))
            {
                strConvertida = _iso_8859_1_to_utf8(str);
                columns.push_back(strConvertida);
            }

            string NR_PARTIDO = columns[27].substr(1, columns[27].length() - 2);
            string SG_PARTIDO = columns[28].substr(1, columns[28].length() - 2);

            // Ignorar cabeçalho
            if (NR_PARTIDO == "NR_PARTIDO")
                continue;

            Partido p(NR_PARTIDO, SG_PARTIDO);
            if(e.getPartidos().find(NR_PARTIDO) == e.getPartidos().end()) {
                e.addPartido(p);
            }

            // Limita somente a candidatos com candidatura deferida e votos para legenda
            if ((columns[68].substr(1, columns[68].length() - 2) != "2" && columns[68].substr(1, columns[68].length() - 2) != "16") &&(columns[67].substr(1, columns[67].length() - 2) != "Válido (legenda)"))
                continue;

            // Limita somente a candidatos com cargo específico (estadual ou federal)
            if (stoi(columns[13].substr(1, columns[13].length() - 2)) != idCargo)
                continue;
            
            string CD_CARGO = columns[13].substr(1, columns[13].length() - 2);
            string CD_SITUACAO_CANDIDATO_TOT = columns[68].substr(1, columns[68].length() - 2);
            string NR_CANDIDATO = columns[16].substr(1, columns[16].length() - 2);
            string NM_URNA_CANDIDATO = columns[18].substr(1, columns[18].length() - 2);
            string NR_FEDERACAO = columns[30].substr(1, columns[30].length() - 2);
            string DT_NASCIMENTO = columns[42].substr(1, columns[42].length() - 2);        
            string CD_SIT_TOT_TURNO = columns[56].substr(1, columns[56].length() - 2);
            string CD_GENERO = columns[45].substr(1, columns[45].length() - 2);
            string NM_TIPO_DESTINACAO_VOTOS = columns[67].substr(1, columns[67].length() - 2);

            Candidato c(CD_CARGO, CD_SITUACAO_CANDIDATO_TOT, NR_CANDIDATO, NM_URNA_CANDIDATO, NR_PARTIDO, SG_PARTIDO, NR_FEDERACAO, DT_NASCIMENTO, CD_SIT_TOT_TURNO, CD_GENERO, NM_TIPO_DESTINACAO_VOTOS);

            try
            {
                e.getPartidos().at(NR_PARTIDO).addCandidatos(c);
                e.addCandidato(c);
            }
            catch(const out_of_range& e)
            {
                cerr << e.what() << '\n';
            }
        }
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}

void leVotacao(Eleicao &e, string fileVotacao, string cargo)
{
    try
    {
        ifstream inputStream(fileVotacao);
        string line;

        int idCargo;
        if(cargo == "--federal")
            idCargo = 6;
        else if(cargo == "--estadual")
            idCargo = 7;
        else
            throw invalid_argument("Argumento inválido referente ao cargo do deputado.\n");

        bool header = false;
        while(getline(inputStream, line))
        {
            vector<string> columns;

            istringstream lineStream(line);

            string str, strConvertida;
            while(getline(lineStream, str, ';'))
            {
                strConvertida = _iso_8859_1_to_utf8(str);
                columns.push_back(strConvertida);
            }
            
            if (header == false) {
                header = true;
                continue;
            }

            if (stoi(columns[17].substr(1, columns[17].length() - 2)) != idCargo)
                continue;

            
            string NR_VOTAVEL = columns[19].substr(1, columns[19].length() - 2);
            string QT_VOTOS = columns[21].substr(1, columns[21].length() - 2);

            e.computaVoto(NR_VOTAVEL, stoi(QT_VOTOS));
        }
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }

    e.calculaVagas();
}
