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

/*
    Função que separa, e remove o numero em binario e o caracter extra, retornando a string pura
*/
std::string preencheEDecifra(std::string linha){ 
    


}
void leArquivo(std::string nomeArquivo){

    std::string alteredCarbon;
    std::string linha;

    std::ifstream arquivo(nomeArquivo);
    if(arquivo.is_open()){

        while(std::getline(arquivo,linha)){
            alteredCarbon = preencheEDecifra(linha);
            
            
        
        }
        
	}
}

int main(){

    std::string nomeArquivo;

    std::cout << "Digite o nome do arquivo: ";
    std::cin  >> nomeArquivo; std::cout << std::endl;



}