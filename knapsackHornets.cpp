#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<cmath>
/**
O Problema da Mochila
Autor : Paulo Lopes do Nascimento
Disciplina: Laboratório de Algoritmos e Estruturas de Dados
Profª: Natalia Cosse Batista
*/
/*  Classe de Item contendo peso e valor                    */
class Item{
    private:
        int peso, valor;
    public:
    // Getters e Setters de Peso e Valor respectivamente
        int getPeso(){ return peso; }
        void setPeso(int pesoNovo){ peso = pesoNovo; }
        int getValor(){ return valor; }
        void setValor(int valorNovo){ valor = valorNovo; }
};

std::vector<std::vector<int>> preencheEChecaPossiblidades(int nItens, std::vector<Item> vecItens,int pesoT){
    // Matriz que recebera todas as combinações 2^n, inicializada com zeros
    std::vector<std::vector<int>> solucoesBinarias(nItens, std::vector<int>(pow(2,nItens),0));
    // Vector que será as soluções possíveis depois da restrição do peso
    std::vector<std::vector<int>> retornoDeSolucoes;
    // Vector auxiliar para o retorno final      
    std::vector<int> auxiliar;
    // Controle para permutação de 0s e 1s 
    int controle = 0;
    // Variavel que armazena o peso temporario para excluir soluções invalidas (pesoTemp)
    int pesoTemp=0, pesoTemp2=0;
;
    //Percorre a matriz n x 2^n
    for(int i = 0;i<nItens;i++){
        for(int j = 0;j < pow(2,nItens); j++){
            // Limite é um valor que corresponde as possibilidades de preenchimento, tal como uma tabela verdade
            // Ex: Se n = 4, 2^n = 16, então o limite da primeira linha é 8, já que tem 8 zeros e 8 uns
            // na segunda linha, são intervalos de 4 zeros e 4 uns e assim sucessivamente
            int limite = pow(2,nItens-i-1);
            // Se o controle for menor que o limite
            if(controle < limite){
                // Coloca 0 e adiciona 1 ao controle
                solucoesBinarias.at(i).at(j) = 0;
                controle++;
            }else{ // Senão, coloca 1 e adiciona 1 ao controle e verifica se o controle passou do dobro do limite
                   // neste caso, o controle volta a ser 0
                solucoesBinarias.at(i).at(j) = 1;
                controle++;
                if(controle >= limite*2){
                    controle = 0;
                }
            }
        }
        // Zera o controle para começar a proxima linha
        controle = 0;
    }
    // Percorre o array que foi preenchido com 0 e 1 por colunas ao inves de linhas
    for(int j = 0;j<(int)solucoesBinarias.at(0).size();j++){
        for(int i = 0;i < (int)solucoesBinarias.size(); i++){
            // Se haver um 1
            if(solucoesBinarias.at(i).at(j) == 1){
                // Soma o modulo do valor ao pesoTemp (devido ao meu metodo de excluir possibilidades usar negativos)
                pesoTemp+=abs(vecItens.at(i).getPeso());
            }
        }
        // Se o pesoTemp exceder o maximo da mochila
        if(pesoTemp > pesoT){
            // Seto a coluna(a combinação completa) em questão da matriz para negativo
            for(int i2 = 0;i2 < (int)solucoesBinarias.size(); i2++){
                solucoesBinarias.at(i2).at(j) -= 2;
            }
        }
        // Reinicio o peso para a proxima coluna
        pesoTemp = 0;
    }
    // Percorro a matriz de 0s e 1s
    for(int i = 0;i<(int)solucoesBinarias.size();i++){
        for(int j = 0;j < (int)solucoesBinarias.at(0).size(); j++){
            // Se o valor for positivo, ou seja, a combinação é valida
            if(solucoesBinarias.at(i).at(j)>=0){
                //Concateno-a para o auxiliar
                auxiliar.push_back(solucoesBinarias.at(i).at(j));
            }
        }
        // Insiro o auxiliar na matrix final
        retornoDeSolucoes.push_back(auxiliar);
        // Limpo para começar a proxima linha
        auxiliar.clear();
    }
    //Esse for acho que era só teste
    // for(int j3 = 0; j3 < (int)retornoDeSolucoes.at(0).size();j3++){
    //     for(int i3 = 0; i3 < (int)retornoDeSolucoes.size();i3++){
    //         //std::cout << retornoDeSolucoes.at(i3).at(j3) ;
    //         if(retornoDeSolucoes.at(i3).at(j3) == 1){
    //             pesoTemp2+=abs(vecItens.at(i3).getPeso());
    //         }
    //     }
    //     pesoTemp2 = 0;
    // }
    //Retorno a matrix final
    return retornoDeSolucoes;
}
// Função que gerencia o processo
int knapSack(std::vector<Item>vectorItens,std::vector<int>vectorMochilas, std::vector<std::vector<int>>vectorSolucoes){
    // Posicao a ser removida para proxima iteração, vector com os maiores de cada mochila , vector auxiliar das posiçoes a serem removidas
    std::vector<int> posASerRemovida, maiores, vecAux;
    // String para comparar com solução da matrix retornada, string para verificar se a solução é viavel
    // e string usada no processo de conversao de inteiro para string
    std::string auxiliarViabilidade, viavel, stringTemporary;
    // Vector de strings que possuem as soluções de cada mochila em forma de string
    std::vector<std::string> auxiliarViabilidadeChecagem;
    // String que receberá o retorno da função de preenchimento
    std::vector<std::vector<int>> solucoesPossiveis;
    // Maior começa em 0, temp é o somatorio dos valores, começa com 0 e indexAux é o iterador do vecAux
    int maior=0,temp=0,indexAux=0;
    // Inicializa vectores de posição
    for(int i = 0;i < (int)vectorItens.size();i++){
        posASerRemovida.push_back(0);
        vecAux.push_back(0);
    }
    // Se o número de itens for 0, ou se o número de mochilas for 0
    if((int)vectorItens.size() == 0 || (int)vectorMochilas.size()==0){
        for(int ir=0; ir < (int)vectorSolucoes.size()/(int)vectorSolucoes.at(ir).size();ir++){
            for(int jr=0; jr < (int)vectorSolucoes.at(ir).size();jr++){
                // Se existir alguma solução igual a 1, , retorna 2 (Inviavel)
                if(vectorSolucoes.at(ir).at(jr) == 1){
                    return 2;
                }
            }
        }
    }
    // Percorre o vetor de soluções e passa para string(s) 
    for(int iSolucao=0;iSolucao<(int)vectorSolucoes.size()/(int)vectorSolucoes.at(0).size();iSolucao++){
        for(int jSolucao=0;jSolucao<(int)vectorSolucoes.at(0).size();jSolucao++){
            // Transformo os digitos em strings
            std::string temporary = std::to_string(vectorSolucoes.at(iSolucao).at(jSolucao));
            // Concateno os digitos
            stringTemporary += temporary.c_str();
        }
        // Insiro a string concatenada no vector
        auxiliarViabilidadeChecagem.push_back(stringTemporary);
        // Limpo a string para pegar a proxima coluna
        stringTemporary.clear();
    }
    // Percorrendo as mochilas e os itens
    for(int iM = 0;iM<(int)vectorMochilas.size();iM++){
        // Recebo as soluções possiveis para tal mochila
        solucoesPossiveis = preencheEChecaPossiblidades(vectorItens.size(),vectorItens,vectorMochilas.at(iM));
        //Itero pelas soluções possiveis
        for(int j3 = 0; j3 < (int)solucoesPossiveis.at(0).size();j3++){
            for(int i3 = 0; i3 < (int)solucoesPossiveis.size();i3++){
                // Passo para string e salvo no auxiliarViabilidade
                std::string temp2 = std::to_string(solucoesPossiveis.at(i3).at(j3));
                auxiliarViabilidade += temp2.c_str();
                // Se o digito for 1 e o valor for positivo, adiciona ao temp e guarda a posição
                if(solucoesPossiveis.at(i3).at(j3) == 1 && vectorItens.at(i3).getValor() >= 0){
                    temp += vectorItens.at(i3).getValor();
                    vecAux.at(indexAux) = i3;
                    indexAux++;
                }
            }
            // Se o temp da coluna for maior que o maior
            if(temp > maior){
                // Maior recebe o temp
                maior = temp;
                // O vector de posASerRemovida é zerado
                std::fill(posASerRemovida.begin(), posASerRemovida.end(), 0);
                // posASerRemovida recebe o vecAux
                posASerRemovida = vecAux;
                // Temp é zerado para a proxima coluna
                temp = 0;
            }else{
                // SEnão, temp é apenas zerado
                temp = 0;
            }
            // IndexAux é zerado para a proxima iteração
            indexAux=0;
            // VecAux é zerado
            std::fill(vecAux.begin(), vecAux.end(), 0);
            // Comparo a string da coluna atual com a solução do arquivo para tal mochila
            if(auxiliarViabilidade.compare(auxiliarViabilidadeChecagem.at(iM)) != 0){
                // Se forem diferentes, concateno N
                viavel += 'N';
            }else{ // Se forem iguais, concateno S
                viavel += 'S';
            }
            // Limpo a string da coluna
            auxiliarViabilidade.clear();
        }
        // Se houver mais de uma mochila, começa a proibir itens de serem reusados
        if(vectorMochilas.size()>1){
            for(int ite=0;ite< (int)posASerRemovida.size();ite++){
                // Seto os itens a serem removidos como negativos
                vectorItens.at(posASerRemovida.at(ite)).setPeso(vectorItens.at(posASerRemovida.at(ite)).getPeso()*-1);
                vectorItens.at(posASerRemovida.at(ite)).setValor(vectorItens.at(posASerRemovida.at(ite)).getValor()*-1);
            }
        }
        // Se viavel possuir algum S, ou seja, a solução do arquivo existe dentro das soluções viaveis
        if(viavel.find('S')!= std::string::npos){
            // O maior é colocado no vector Maiores
            maiores.push_back(maior);   
        }else{ // Senão, retorna 2 pois a solução é inviavel
            return 2;
        }
        // Reinicia o maior para a proxima mochila
        maior = 0;
        // Reinicia a stirng viavel para a proxima mochila
        viavel.clear();
    }
    // String final para verificar o retorno
    std::string resultado;
    // Percorro as mochilas
    for(int iM = 0;iM<(int)vectorMochilas.size();iM++){
        // Auxiliar para comparação 
        int valorMochila = 0;
        // Percorro os itens
        for(int i=0;i<(int)vectorItens.size();i++){
            // Se tal posição no vetor de soluções do arquivo for 1
            if(vectorSolucoes.at(iM).at(i) == 1){
                // Valor mochila recebe o valor respectivo do vector de itens
                valorMochila +=vectorItens.at(i).getValor();
            }
        }
        // Se o valor da mochila iM de acordo com o arquivo, for igual ao maior valor encontrado para  tal mochila
        if(maiores.at(iM) == abs(valorMochila)){
            // Concatena um V
            resultado += 'V';
        }else{ // SEnão, concatena um N
            resultado += 'N';
        }
    }
    // Se a string resultado achar um N na string, retorna 1 que significa Viavel mas nao otima
    if(resultado.find('N')!= std::string::npos){
        return 1;
    }else{ // Senão, retorna 0 que significa Solução Otima.
        return 0;
    }
}
int leArquivo(std::string nomeArquivo){
    //Vector com os capacidades das mochilas
    std::vector<int> vectorMochilas;
    //Vector com objetos de itens, contendo peso e valor
    std::vector<Item> vectorItens;
    // Matriz de soluções, organizada da forma: vectorSolucoes[i][j],
    //onde i é o numero do item e j o numero da mochila
    std::vector<std::vector<int>> vectorSolucoes;
    //String linha
    std::string linha;
    //Abre o arquivo
    std::ifstream arquivo(nomeArquivo);
    //Controle de linhas do arquivo texto, quantidade de mochilas, número de itens;
    int nLinha=1, quantMochilas, nItens;

    //Verifica abertura do arquivo de texto
    if(arquivo.is_open()){
        // Percorre o arquivo pegando linha a linha
        while(std::getline(arquivo,linha)){
            if(linha.empty()==0){
                //Se for a primeira linha
                if(nLinha == 1){// Linha do numero de mochilas
                    //Transforma a string em inteiro e define como quantidade de mochilas
                    quantMochilas = (int)std::stoi(linha);
                    //Adianta o controlador para próxima linha
                    nLinha++;
                }else if(nLinha == 2){// Linha do(s) peso(s) da(s) mochila(s)
                    //Se a quantidade de mochilas for maior que 1, precisa-se iterar para pegar todos os valores
                    //Auxiliar string para guardar caracteres temporarios ate um espaço
                    std::string temporaryAux;
                    if(quantMochilas > 1){
                        //Percorre-se a linha caracter por caracter
                        for(int i = 0;i < (int)linha.size();i++){
                            //Se encontrar um espaço, significa que terminou de se pegar um peso
                            if(linha.at(i) == ' '){
                                //Coloca o valor como inteiro no vector, transformado via stoi
                                vectorMochilas.push_back( (int)std::stoi(temporaryAux));
                                //Limpa a string temporaria
                                temporaryAux.clear();
                            }else if(i == (int)linha.size()-1){
                                temporaryAux += linha.at(i);
                                vectorMochilas.push_back( (int)std::stoi(temporaryAux));
                            }else{
                                //Enquanto não encontrar um espaço, concatena para a temporaria
                                temporaryAux += linha.at(i);
                            }
                        }
                    }else{
                        //Se for apenas 1 mochila, apenas transforma a linha inteira
                        vectorMochilas.push_back((int)std::stoi(linha));
                    }
                    //Adianta o controlador para próxima linha
                    nLinha++;
                }else if(nLinha == 3){    // Linha do numero de itens
                    //Transforma a string em inteiro e define como número de itens
                    nItens = (int)std::stoi(linha);
                    //Adianta o controlador para próxima linha
                    nLinha++;
                }else if(nLinha <= (4 + nItens - 1)){// Linhas contendo os pesos e valores, começando na linha 4
                    // Declaro variaveis para receber peso e valor em forma de string
                    std::string pesoTemp, valorTemp;
                    // Declaro uma flag para controlar se o peso foi definido
                    bool pesoSetado=false;
                    // Declaro um item auxiliar que será inserido no vector
                    Item itemN;
                    // Percorro a linha caracter por caracter
                    for(int i = 0; i < (int)linha.size();i++){
                        // Se o caracter for um espaço
                        if(linha.at(i) == ' '){
                            // Defino como peso tudo que estava na variavel de peso temporaria
                            itemN.setPeso((int)std::stoi(pesoTemp));
                            // Seto a flag como true
                            pesoSetado = true;
                        }else if(i == (int)linha.size()-1){ // Se for a ultima iteração do for
                            // Concateno o ultimo caracter no valor temporario
                            valorTemp += linha.at(i);
                            // Defino como valor a string temporaria de valor
                            itemN.setValor((int)std::stoi(valorTemp));
                        }else{
                            // Se não for nenhum dos casos, verifica se o peso ja foi definido
                            if(pesoSetado == true){
                                // Se o peso já está definido, concatena para o valor temporario
                                valorTemp += linha.at(i);
                            }else{  // Senão, concatena para o peso temporario
                                pesoTemp += linha.at(i);
                            }
                        }
                    }
                    // Insere o objeto temporario no array de itens
                    vectorItens.push_back(itemN);
                    // Aumento 1 no controlador de linhas do arquivo
                    nLinha++;
                }else if(nLinha >= (3+nItens+1)){ // Depois dos dados dos itens, vem as soluções
                    // A variável controle me ajuda a saber em qual indice de caracter terão valores
                    int controle = 0;
                    // Itero pela quantidade de mochilas e crio vetores auxiliares e os insiro na matriz de soluções
                    for(int i = 0;i < quantMochilas; i++){
                        std::vector<int> auxiliar;
                        vectorSolucoes.push_back(auxiliar);
                    }
                    // Percorro caracter por caracter a linha do arquivo
                    for(int i = 0;i < (int)linha.size(); i++){
                        // Se o caracter for um espaço
                        if(linha.at(i) == ' '){
                            // Adiciono ao vetor de controle o inteiro "linha.at(controle*2)-48" que será o 0 ou 1 em ascii
                            vectorSolucoes.at(controle).push_back(linha.at(controle*2)-48);
                            // Adiciono 1 ao controle para ser a proxima mochila que está na linha do arquivo
                            controle++;
                        }else if(i == (int)linha.size()-1){ // Se for a ultima iteração
                            // Adiciono ao vetor o ultimo valor com base no controle já estabelecido por ultimo
                            vectorSolucoes.at(controle).push_back(linha.at(controle*2)-48);
                        }
                    }
                    // Adiciono 1 ao controlador de linhas do arquivo texto
                    nLinha++;
                }
            }
        }
    }else{  std::cout << "Não foi possível abrir o arquivo. Tente novamente." << std::endl; }
    // Retorna o retorno da função knapsack, função principal do programa
    return knapSack(vectorItens,vectorMochilas, vectorSolucoes);
}
int main(){

    // Varivel com nome do arquivo
    std::string nomeArquivo;
    // Interação com o usuario
    std::cout << "Digite o nome do arquivo: ";
    // Lê o nome do arquivo e pula uma linha
    std::cin  >> nomeArquivo;
    // Recebe o valor de retorno
    int retorno = leArquivo(nomeArquivo);
    // Faz um switch com o retorno a fim de printar a resposta correspondente
    switch(retorno){
        case 0:{
            std::cout << "Solucao otima." << std::endl;
            break;
        };
        case 1:{
            std::cout << "Solucao viavel mas nao otima." << std::endl;
            break;
        };
        case 2:{
            std::cout << "Solucao inviavel." << std::endl;
            break;
        };
    }
    return 0;
}
