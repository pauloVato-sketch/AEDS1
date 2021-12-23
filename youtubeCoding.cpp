#include<iostream>
#include<vector>
#include<cmath>
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
    std::vector<std::vector<int>> solucoesBinarias(nItens, std::vector<int>(pow(2,nItens),0));
    std::vector<std::vector<int>> retornoDeSolucoes;
    int controle = 0;
    for(int i = 0;i<nItens;i++){
        for(int j = 0;j < pow(2,nItens); j++){
            int limite = pow(2,nItens-i-1);
            if(controle < limite){
                solucoesBinarias.at(i).at(j) = 0;
                controle++;
            }else{
                solucoesBinarias.at(i).at(j) = 1;
                controle++;
                if(controle >= limite*2){
                    controle = 0;
                }
            }
        }
        controle = 0;
    }
    int pesoTemp=0;
    for(int j = 0;j<solucoesBinarias.at(0).size();j++){
        for(int i = 0;i < solucoesBinarias.size(); i++){
            if(solucoesBinarias.at(i).at(j) == 1){
                pesoTemp+=vecItens.at(i).getPeso();
            }
        }
        if(pesoTemp > pesoT){
            for(int i2 = 0;i2 < solucoesBinarias.size(); i2++){
                solucoesBinarias.at(i2).at(j) -= 2;
            }
        }
        pesoTemp = 0;
    }
    std::vector<int> auxiliar;
    for(int i = 0;i<solucoesBinarias.size();i++){
        for(int j = 0;j < solucoesBinarias.at(0).size(); j++){
            if(solucoesBinarias.at(i).at(j)>=0){
                auxiliar.push_back(solucoesBinarias.at(i).at(j));
            }
        }
        retornoDeSolucoes.push_back(auxiliar);
        auxiliar.clear();
    }
    int pesoTemp2=0;
    for(int j3 = 0; j3 < retornoDeSolucoes.at(0).size();j3++){
        for(int i3 = 0; i3 < retornoDeSolucoes.size();i3++){
            //std::cout << retornoDeSolucoes.at(i3).at(j3) ;
            if(retornoDeSolucoes.at(i3).at(j3) == 1){
                pesoTemp2+=vecItens.at(i3).getPeso();
            }
        }
        //std::cout << std::endl;
        //std::cout << "Peso = "<< pesoTemp2 << std::endl;
        pesoTemp2 = 0;
    }
    return retornoDeSolucoes;
}

int main(){
    int itens = 5;
    std::vector<Item> arrayItens;
    std::vector<int> cap = {65,85};
    Item aux1,aux2,aux3,aux4,aux5,aux6;
    aux1.setPeso(40);aux1.setValor(110);
    aux2.setPeso(7);aux2.setValor(13);
    aux3.setPeso(11);aux3.setValor(23);
    aux4.setPeso(8);aux4.setValor(15);
    aux5.setPeso(9);aux5.setValor(16);
    aux6.setPeso(5);aux6.setValor(5);

    arrayItens.push_back(aux1);arrayItens.push_back(aux2);
    arrayItens.push_back(aux3);arrayItens.push_back(aux4);
    arrayItens.push_back(aux5);arrayItens.push_back(aux6);
    std::vector<std::vector<int>> solucoesViaveis = preencheEChecaPossiblidades(itens, arrayItens,cap.at(0));
    for(int i=0;i<cap.size();i++){
        int retorno = (itens, arrayItens, cap.at(i), 0);
       // std::cout << retorno << std::endl;
    }   
}