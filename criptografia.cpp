#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <ctype.h>
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

    for(int i=0; i<linha.size(); i++){
        if(linha.at(i) >= 48 && linha.at(i) <= 57){
            numeroBinario += linha.at(i);
            if(numeroBinario.size() == 5){
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
std::string reoordenarBlocos(std::string alterada){
    std::string stringTemp;

    for(int i = 0; i < alterada.size(); i++){
        if(i % 2 == 0){
            alterada.insert(i,"-");
        }

    }
    std::cout << alterada << std::endl;
    
    return alterada;

}
/* 
    Função que lê o arquivo e faz chamadas subsequentes para decriptografia
*/
void leArquivo(std::string nomeArquivo){

    //String alterada
    std::string alteredCarbon;
    //String linha
    std::string linha;

    std::ifstream arquivo(nomeArquivo);
    if(arquivo.is_open()){

        while(std::getline(arquivo,linha)){
            alteredCarbon = preencheEDecifra(linha);
            alteredCarbon = reoordenarBlocos(alteredCarbon);
        }
        
	}else{
        std::cout << "Não foi possível abrir o arquivo. Tente novamente." << std::endl;
    }
}

int main(){

    std::string nomeArquivo;

    std::cout << "Digite o nome do arquivo: ";
    std::cin  >> nomeArquivo; std::cout << std::endl;
    leArquivo(nomeArquivo);


}