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

    /// Leitura e inicialização dos armazens dentro do grafo e de suas conexões
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

    int packNum;
    inputFile >> packNum;
    /// ----------------------------------------------------------------------

    Scheduler mainScheduler;
    bool is_finished = 0;
    int simulation_time = 0;

    List<Depot*>* depotsList = DepotNet.getAdjacencyList();
    int i, j;
    
    /// Agenda a postagem dos pacotes
    for(i = 0; i < packNum; i++){
        std::string packageInfo;
        if (std::getline(inputFile, packageInfo)) {
            std::istringstream iss(packageInfo);
            int postingTime;
            int OriginDepot_i;
            int DestinationDepot_i;
            int packageID;
            std::string tbIgnored;

            iss >> postingTime >> tbIgnored >> packageID >> tbIgnored >> OriginDepot_i >> tbIgnored >> DestinationDepot_i;
            Package* pack = new Package(packageID, depotsList[OriginDepot_i].front(), depotsList[DestinationDepot_i].front());
            pack->setPath(DepotNet);
            mainScheduler.queueEvent(new Event(1, simulation_time + postingTime, pack));
        }
    }

    /// Agenda os eventos de transporte inicialmente
    for(i = 0; i < depotNum; i++){
        List<Depot*> edgesList = depotsList[i];
        for(j = 1; j < edgesList.getSize(); j++){
            mainScheduler.queueEvent(new Event(2, simulation_time + edgesList.front()->getTransportTime(edgesList.get(j)), edgesList.front(), edgesList.get(j)));
        }
    }
    
    List<Package*> deliveredPackages;
    while(!is_finished && simulation_time < 100000){
        Event* currentEvent = mainScheduler.dequeueNextEvent();
        simulation_time += currentEvent->getSTime();
        if (currentEvent->getType() == 1||currentEvent->getType() == 3){// evento é transporte 1 - primeira tentativa / 3 - segunda tentativa
            int k = 0;
            try{
                currentEvent->TransportOut();
            }catch (DepotNotPrepared &e){
                k = e.getNumUntillOk(); // Número de pacotes a serem retirados antes que o transporte possa acontecer;
            }

            if(k != 0){
                Depot* currentDepot = currentEvent->getDepot();
                for(int n = 0; n < k; n++){
                    // Agendar o desinfileirar dos n primeiros pacotes
                }
            }

        }else if(currentEvent->getType() == 2){// evento é pacote
            try{
                currentEvent->TransportIn(simulation_time);
            }catch(const PackageDeliveredException &e){
                deliveredPackages.pushBack(currentEvent->DeliveredPackage());
            }
        }
    }

}