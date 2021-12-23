#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<tuple>
#include <ctype.h>
/**
Jogo das Caixas
Autor : Paulo Lopes do Nascimento
Disciplina: Laboratório de Algoritmos e Estruturas de Dados
Profª: Natalia Cosse Batista
*/
class Matriz {      
  public:             
    int tamanho;    
    std::vector<std::vector<int>> matrizCompleta;  
};

std::vector<int> retornaVectorDeString(std::string linhaArq){
    std::vector<int> valoresLinha;
    std::string temp="";

    for(int i = 0; i < (int)linhaArq.length(); i++) {
        
        if( (linhaArq.at(i) >= 48 && linhaArq.at(i) <= 57) || linhaArq.at(i) == 45){
            temp += linhaArq.at(i);
        }else if(linhaArq.at(i) != 32 || linhaArq.at(i) != 10){
            int aux = std::atoi(temp.c_str());
            valoresLinha.push_back(aux);
            temp.clear();
  
        }
    }
    
    return valoresLinha;
}

std::tuple<int,int> calculaMelhorCaso(Matriz objDeMatriz){
    int fileira=0, coluna=0, maior = 0, valor = 0;
    
    for(int i = 0; i < objDeMatriz.tamanho; i++){
        for(int j = 0; j < objDeMatriz.tamanho; j++){
            if((i-1 >= 0)){
               
                for(int i2 = i-1; i2>=0; i2--){
                    for(int j2 = objDeMatriz.tamanho-1;j2>=0;j2--){ 
                        valor +=  objDeMatriz.matrizCompleta[i2][j2];
                    }  
                }
                valor += objDeMatriz.matrizCompleta[i][j];
                // std::cout << "Valor acima da posicao " << i << " - "<< j << " "<< valor << std::endl;
                if(valor > maior){
                    maior = valor;
                    fileira = i+1;
                    coluna = j+1;
                    valor = 0;
                }
                
            }else{
                valor = objDeMatriz.matrizCompleta[i][j];
                if(valor > maior){
                    maior = valor;
                    fileira = i+1;
                    coluna = j+1;
                    valor = 0;
                }
                
            }           
        }
    }
    //std::cout << " Maior: " << maior << std::endl;
    return  std::make_tuple(fileira, coluna);
}
Matriz leArquivo(std::string nomeArquivo){

    int tamanho;
    std::vector<std::vector<int>> pyramid;
    std::vector<int> numerosDaLinha(0);
    std::string linha;
    Matriz obj;

    std::ifstream arquivo(nomeArquivo);
    if(arquivo.is_open()){
	   
        std::getline(arquivo,linha);
        tamanho = std::atoi(linha.c_str());
        obj.tamanho = tamanho;

        while(std::getline(arquivo,linha)){
            numerosDaLinha = retornaVectorDeString(linha+'\n');
            
            std::vector<int> temporary;
            for(int jtVector = 0; jtVector < tamanho; jtVector++){
                if( jtVector < (int)numerosDaLinha.size()){
                    temporary.push_back(numerosDaLinha[jtVector]);
                }else{
                    temporary.push_back(0);
                }
            }
            pyramid.push_back(temporary);
        
        }
       
        obj.matrizCompleta = pyramid;
	}
    return obj;
}





int main(){

    std::string nomeArquivo;
    int fileira, coluna;
    std::cout << "Digite o nome do arquivo de entrada: ";

    std::cin  >> nomeArquivo;

    std::tie(fileira, coluna) = calculaMelhorCaso(leArquivo(nomeArquivo));

    std::cout << "Resposta: fileira " << fileira << ", caixa "<< coluna << "." <<std::endl;
}

