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
    // Inicializando valor base como 1 = 2^0
    int base = 1;
    
    int temp = binario;
    //Enquanto houver digitos
    while (temp) {
        //Divida por 10 e pegue o resto, que será o ultimo digito
        int ultimoDigito = temp % 10;
        //Recebe o quociente da divisao acima
        temp = temp / 10;
        //Soma o valor em decimal ao ultimo digito vezes a base
        valorDecimal += ultimoDigito * base;
        //Altera a base
        base = base * 2;
    }
    //Retorna valor decimal
    return valorDecimal;
}
/*
    Função que separa, e remove o numero em binario e o caracter extra, retornando a string pura
*/
std::string preencheEDecifra(std::string linha){ 
    //String que receberá o numero binario
    std::string numeroBinario="";
    //Posicao do caracter extra na linha
    int posicaoASerRemovida=0;
    //StringPura é a string com numero e caracter extra removidos
    std::string stringPura="";

    //Percorro a linha
    for(int i=0; i< (int)linha.size(); i++){
        //Se o caracter da posição i for um numero...
        if(linha.at(i) >= 48 && linha.at(i) <= 57){
            //... concateno para a string de numeroBinario
            numeroBinario += linha.at(i);
            //Se a string de binario tiver 5 digitos, que é o limite
            if((int)numeroBinario.size() == 5){
                //Converto a string binario para inteiro binario
                posicaoASerRemovida = std::stoi( numeroBinario );
                //Chamo a função que transforma binario em decimal
                posicaoASerRemovida = converteBinarioDecimal(posicaoASerRemovida);
            }
        }else{
            //Se o caracter da posição i não for um número e i diferente da posição que encontramos do 
            //caracter falso, concatenamos o digito para a stringPura
            if( i != posicaoASerRemovida-1 + 5 ){
                // std::cout << "POSICAO BINARIA - 1 = " << (posicaoASerRemovida - 1) << std::endl;
                // std::cout << " i - POSICAO BINARIA - 1 = " << (i - posicaoASerRemovida-1) << std::endl;
                stringPura += linha.at(i);
            }
        }

    }
    //Retorno a stringPura
    return stringPura;
}
/*
    Função que reordena os blocos e inverte a reflexão
*/
std::vector<std::string> reoordenarBlocos(std::string alterada){
    //String temporaria que será cada bloco e esvaziada quando chegar em n digitos
    std::string stringTemp;
    //Criação de um vector de strings para separar os blocos por posição
    std::vector<std::string> vetorDeBlocos;

    // Separa em blocos de 2
    for(int i = 0; i < (int)alterada.size(); i++){
        //Sea a string temporaria encher
        if( (int)stringTemp.size() == 2 ){
            //Insiro ela no vector
            vetorDeBlocos.push_back(stringTemp);
            //Limpo a string
            stringTemp.clear();
            //Concateno o valor de agora
            stringTemp += alterada.at(i);
            //Se for o ultimo i, pode ser o caso de faltar char no ultmo bloco, pra garantir
        }else if(i == (int)alterada.size()-1){
            //Adiciona o ultimo char antes 
            stringTemp += alterada.at(i);
            //Insiro no vector
            vetorDeBlocos.push_back(stringTemp);
            //Limpo a string
            stringTemp.clear();
        }else{
            //De resto, apenas adiciono o digito na string temporaria
            stringTemp += alterada.at(i);
        }
    }
    
    // Inverte blocos percorrendo ate a metade do vector
    for(int i = 0; i < (int)vetorDeBlocos.size()/2; i++){
        //Se a posição for par
        if( i % 2 == 0 ){
            //String temporaria recebe valor da posição i 
            stringTemp = vetorDeBlocos.at(i);
            //Posição i é substituida pela posição inversa na ordem 
            vetorDeBlocos.at(i) = vetorDeBlocos.at((int)vetorDeBlocos.size() - i - 1);
            //Posição inversa recebe o valor salvo na temporaria
            vetorDeBlocos.at((int)vetorDeBlocos.size() - i - 1) = stringTemp;
        }
    }
    // Reflete os blocos usando std::reverse no vector
    for(int i = 0; i < (int)vetorDeBlocos.size(); i++){
        std::reverse(vetorDeBlocos.at(i).begin(), vetorDeBlocos.at(i).end());
    }
    //Retorna o vector de blocos
    return vetorDeBlocos;
}
/*
    Função cifraDeCesar
*/
std::string cifraDeCesar(std::vector<std::string> vetorBlocos){
    //Variavel que será o retorno final e definitivo da mensagem descriptografada
    std::string retornoFinal;
    //Percorre o vector de strings
    for(int i = 0; i < (int)vetorBlocos.size(); i++){
        //Percorre digito a digito das strings
        for(int j = 0; j < (int)vetorBlocos.at(i).size(); j++){
            //Se o digito for #, concateno um espaço para a string final
            if(vetorBlocos.at(i).at(j) == '#'){
                retornoFinal += ' ';
            }else{
                //Se o digito estiver entre a e z minusculo
                if(vetorBlocos.at(i).at(j) >= 'a' && vetorBlocos.at(i).at(j) <= 'z'){
                    //Um char temporario recebe a posição rotacionada para a esquerda 5 posições
                    char temp = vetorBlocos.at(i).at(j) - 5;
                    //Se a rotação fez com que o caracter saiu do limite
                    if( temp < 'a'){
                        //Concertamos ao realizar a seguinte operação
                        temp = temp +'z' - 'a' + 1;
                    }
                    //Concatena o temporario
                    retornoFinal += temp;
                    //Se o digito estiver entre A e Z maiusculo
                }else if(vetorBlocos.at(i).at(j) >= 'A' && vetorBlocos.at(i).at(j) <= 'Z'){
                        //Um char temporario recebe a posição rotacionada para a esquerda 5 posições
                        char temp = vetorBlocos.at(i).at(j) - 5;
                            //Se a rotação fez com que o caracter saiu do limite
                            if( temp < 'A'){
                                //Concertamos ao realizar a seguinte operação
                                temp = temp +'Z' - 'A' + 1;
                            }
                        //Concatena o temporario
                        retornoFinal += temp;
                }
            }
        }
    }
    //Retorna a string com o retorno final
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
    //Abre o arquivo
    std::ifstream arquivo(nomeArquivo);
    if(arquivo.is_open()){
        // Percorre o arquivo pegando linha a linha
        while(std::getline(arquivo,linha)){
            // Printa a linha para estar corretamente formatada
            std::cout << linha << std::endl << std::endl;
            // String alterada recebe a linha depois de separar o binario e remover o caracter extra
            alteredCarbon = preencheEDecifra(linha);
            // Vector de blocos recebe o retorno da função que separa a string alterada em blocos
            vectorBlocos = reoordenarBlocos(alteredCarbon);
            // String alterada finalmente recebe o retorno da função que decifra a cifra de cesar
            alteredCarbon = cifraDeCesar(vectorBlocos);
        }
    // Se não conseguir acessar o arquivo exibe mensagem de erro (conveniente para programas completos)
	}else{
        std::cout << "Não foi possível abrir o arquivo. Tente novamente." << std::endl;
    }
    // Retorna a string definitiva
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