#include "scheduler.hpp"
#include "basicTADS.hpp"
#include "package.hpp"
#include "depot.hpp"
#include "graph.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]){

    /// Segurança para garantir que o input foi fornecido de forma correta----------------
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo " << argv[1] << std::endl;
        return 1;
    }
    //------------------------------------------------------------------------------------

    int transportCapacity;
    int transportTime;
    int transportFreezeTime;
    int removalCost;
    int depotNum;

    inputFile >> transportCapacity >> transportTime >> transportFreezeTime >> removalCost >> depotNum;

    Graph DepotNet(depotNum);
    for (int i = 0; i < depotNum; i++) {
        DepotNet.addVertex(new Depot(i, transportTime));
    }

    
    for (int i = 0; i < depotNum; i++){
        std::string adjList;
        if (std::getline(inputFile, adjList)) {
            std::istringstream iss(adjList);
            int value;
            int j = 0;
            while (iss >> value) {
                if (value == 1){
                    DepotNet.addEdge(i, j); // Utilizasse o addEdge indexado para menor complexidade.
                }
                j++;
            }
            DepotNet.setEdgeConnections(i);
        }
    }



}