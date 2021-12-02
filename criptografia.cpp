#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<ctype.h>
#include <algorithm>
/**
Criptografia
Autor : Paulo Lopes do Nascimento
Disciplina: Laboratório de Algoritmos e Estruturas de Dados
Profª: Natalia Cosse Batista
*/
/* Função para converter binario para decimal*/
int converteBinarioDecimal(int binario)
{
    int valorDecimal = 0;
    // Initializing base value to 1, i.e 2^0
    int base = 1;
 
    int temp = binario;
    while (temp) {
        int ultimoDigito = temp % 10;
        temp = temp / 10;
        valorDecimal += ultimoDigito * base;
        base = base * 2;
    }
 
    return valorDecimal;
}
/*
    Função que separa, e remove o numero em binario e o caracter extra, retornando a string pura
*/
std::string preencheEDecifra(std::string linha){ 
    std::string numeroBinario="";
    int posicaoASerRemovida=0;
    std::string stringPura="";

    for(int i=0; i< (int)linha.size(); i++){
        if(linha.at(i) >= 48 && linha.at(i) <= 57){
            numeroBinario += linha.at(i);
            if((int)numeroBinario.size() == 5){
                posicaoASerRemovida = std::stoi( numeroBinario );
                posicaoASerRemovida = converteBinarioDecimal(posicaoASerRemovida);
            }

        }else{
            if( i != posicaoASerRemovida-1 + 5 ){
                // std::cout << "POSICAO BINARIA - 1 = " << (posicaoASerRemovida - 1) << std::endl;
                // std::cout << " i - POSICAO BINARIA - 1 = " << (i - posicaoASerRemovida-1) << std::endl;
                stringPura += linha.at(i);
            }
        }

    }
    return stringPura;
}
/*
    Função que reordena os blocos e inverte a reflexão
*/
std::vector<std::string> reoordenarBlocos(std::string alterada){
    std::string stringTemp;
    std::vector<std::string> vetorDeBlocos;
    //std::cout << alterada << std::endl;

    // Separa em blocos de 2
    for(int i = 0; i < (int)alterada.size(); i++){
        if( (int)stringTemp.size() == 2 ){
            vetorDeBlocos.push_back(stringTemp);
            stringTemp.clear();
            stringTemp += alterada.at(i);
        }else if(i == (int)alterada.size()-1){
            stringTemp += alterada.at(i);
            vetorDeBlocos.push_back(stringTemp);
            stringTemp.clear();
        }else{
            stringTemp += alterada.at(i);
        }
    }
    
    // Inverte blocos
    for(int i = 0; i < (int)vetorDeBlocos.size()/2; i++){
        if( i % 2 == 0 ){
            stringTemp = vetorDeBlocos.at(i);
            vetorDeBlocos.at(i) = vetorDeBlocos.at((int)vetorDeBlocos.size() - i - 1);
            vetorDeBlocos.at((int)vetorDeBlocos.size() - i - 1) = stringTemp;
        }
    }
    // Reflete os blocos
    for(int i = 0; i < (int)vetorDeBlocos.size(); i++){
        std::reverse(vetorDeBlocos.at(i).begin(), vetorDeBlocos.at(i).end());
    }
    // for (std::string i: vetorDeBlocos)
    //     std::cout << i << ' ';
    //std::cout << std::endl;
    return vetorDeBlocos;
}
/*
    Função cifraDeCesar
*/
std::string cifraDeCesar(std::vector<std::string> vetorBlocos){
    std::string retornoFinal;
    for(int i = 0; i < (int)vetorBlocos.size(); i++){
        for(int j = 0; j < (int)vetorBlocos.at(i).size(); j++){
            if(vetorBlocos.at(i).at(j) == '#'){
                retornoFinal += ' ';
            }else{

                if(vetorBlocos.at(i).at(j) >= 'a' && vetorBlocos.at(i).at(j) <= 'z'){
                    char temp = vetorBlocos.at(i).at(j) - 5;
                    if( temp < 'a'){
                        temp = temp +'z' - 'a' + 1;
                    }
                    retornoFinal += temp;
                }else if(vetorBlocos.at(i).at(j) >= 'A' && vetorBlocos.at(i).at(j) <= 'Z'){
                        char temp = vetorBlocos.at(i).at(j) - 5;
                        if( temp < 'A'){
                            temp = temp +'Z' - 'A' + 1;
                        }
                        retornoFinal += temp;
                }
            }
        }
    }
    return retornoFinal;
}
/* 
    Função que lê o arquivo e faz chamadas subsequentes para decriptografia
*/
std::string leArquivo(std::string nomeArquivo){

    //String alterada
    std::string alteredCarbon;
    //Vector de string com blocos refletidos
    std::vector<std::string> vectorBlocos;
    //String linha
    std::string linha;

    std::ifstream arquivo(nomeArquivo);
    if(arquivo.is_open()){

        while(std::getline(arquivo,linha)){
            std::cout << linha << std::endl << std::endl;
            alteredCarbon = preencheEDecifra(linha);
            vectorBlocos = reoordenarBlocos(alteredCarbon);
            alteredCarbon = cifraDeCesar(vectorBlocos);
        }
        
	}else{
        std::cout << "Não foi possível abrir o arquivo. Tente novamente." << std::endl;
    }
    return alteredCarbon;
}

int main(){

    std::string nomeArquivo, stringDecodificada;

    std::cout << "Digite o nome do arquivo: ";
    std::cin  >> nomeArquivo; std::cout << std::endl;
    std::cout << "--------------------"<< std::endl 
              << "Mensagem codificada:"<< std::endl
              << "--------------------"<< std::endl;
    stringDecodificada = leArquivo(nomeArquivo);
    std::cout << "----------------------"<< std::endl 
              << "Mensagem decodificada:"<< std::endl
              << "----------------------"<< std::endl;
    std::cout << stringDecodificada << std::endl;

}