#include "scheduler.hpp"
#include "basicTADS.hpp"
#include "event.hpp"
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

    int l = 0;
    for (l = 0; l < depotNum; l++){
        int value;
        int j = 0;
        for (j = 0; j < depotNum; j++) {
            inputFile >> value;
            if (value == 1){
                std::cout << "adding Edge " << l << " " << j << std::endl;
                DepotNet.addEdge(l, j); // Utilizasse o addEdge indexado para menor complexidade.
            }
        }
        DepotNet.setEdgeConnections(l);
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
        if (currentEvent->getType() == 1){// evento é transporte 1 
            int k = 0;
            List<Package*> transportTruck;
            try{
                currentEvent->TransportOut();
            }catch (DepotNotPrepared &e){
                e.what();
                k = e.getNumUntillOk(); // Número de pacotes a serem retirados antes que o transporte possa acontecer;
            }

            if(k != 0){
                Depot* currentDepot = currentEvent->getDepot();
                Depot* nextDepot = currentEvent->getDestinationDepot();
                for(int n = 1; n <= k; n++){
                    // Os eventos de tipo 0 servem para remover os pacotes da stack de saída e colocar
                    // em uma auxiliar, para permitir a retirada dos últimos pacotes.
                    mainScheduler.queueEvent(new Event(0, simulation_time + n, currentDepot, nextDepot));
                    mainScheduler.queueEvent(new Event(3, simulation_time + k, currentDepot, nextDepot));
                }

            }

        }else if(currentEvent->getType() == 2){// evento é pacote
            try{
                currentEvent->TransportIn(simulation_time);
            }catch(const PackageDeliveredException &e){
                deliveredPackages.pushBack(currentEvent->DeliveredPackage());
            }// Para quando o evento é de um armazem para um outro
            


        }else if(currentEvent->getType() == 0 || currentEvent->getType() == 3){// evento de pacote para rearmazenamento
            try{
                currentEvent->TransportOut();
            }catch(const int &e){
                mainScheduler.requeueEvent(currentEvent, e);
            }// Para quando o evento é do reestoque para o próprio armazém
        }
    }

}