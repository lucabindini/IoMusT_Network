#include "inet/applications/udpapp/UdpBasicApp.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "SmartInstrumentCollectionRecords.cc"
#include <fstream>
#include <string.h>


using namespace omnetpp;

class ServerSmartInstrumentApp: public inet::UdpBasicApp {

protected:
    std::string name;
    std::vector<SmartInstrumentCollectionRecords> collections;
    std::vector<std::string> musicians;
    std::string msg;

    virtual void initialize(int stage) override {
            UdpBasicApp::initialize(stage);
            if(firstCall) {
                name = std::string(packetName);
                loadMusicians();
                loadAllSmartInstruments();
                //std::cerr << musicians.size() << std::endl;
                firstCall = false;
            }
        }

    virtual void sendPacket() override {
        for(int i = 0; i < musicians.size(); i++){
            notifyMusician("smartInst" + std::to_string(i+1), i);
            collections.at(i).clearCollection();
        }
        firstSent = false;
    }

    virtual void processPacket(inet::Packet *pk) override {
        std::vector<std::string> result = split(pk->getName(), '-');
        for(int i = 0; i < musicians.size(); i++)
            if(collections.at(i).getSmartInstName() == result.at(0)) {
                collections.at(i).addRecord(std::stoi(result.at(1)), std::stoi(result.at(2)), int(omnetpp::simTime().dbl()*1000));
                //std::cout<<"Tempo invio pacchetto: "<<result.at(2) << "    " << "Tempo ricezione pacchetto: " << int(omnetpp::simTime().dbl()*1000) << std::endl;
            }
        UdpBasicApp::processPacket(pk);
    }

private:
    bool firstCall = true;
    bool firstSent = true;

    void loadAllSmartInstruments() {
            for(int i = 1; i <= musicians.size(); i++)
                collections.push_back(SmartInstrumentCollectionRecords("smartInst" + std::to_string(i)));
        }

    void loadMusicians() {
        std::string line;
        std::ifstream myfile ("musicians.txt");
        if (myfile.is_open()) {
            while ( getline (myfile,line) ) {
                musicians.push_back(line);
            }
            myfile.close();
        }
        else
            std::cerr << "Unable to open file" << std::endl;
    }

    void buildPacket(int index) {
            msg = "-";
            msg += std::to_string(collections.at(index).getMeanBPM());
            msg += "-";
            msg += std::to_string(int(omnetpp::simTime().dbl()*1000));
            strcpy(packetName, (name + msg).c_str());
        }

    std::vector<std::string> split(const char *str, char c) {
        std::vector<std::string> result;
        do {
            const char *begin = str;
            while(*str != c && *str)
                str++;
            result.push_back(std::string(begin, str));
        }while (0 != *str++);
        return result;
    }

    void notifyMusician(std::string name, int index) {
        UdpBasicApp::destAddressStr.clear();
        UdpBasicApp::destAddresses.clear();
        const char *destAddrs = name.c_str();
        cStringTokenizer tokenizer(destAddrs);
        const char *token;
        while ((token = tokenizer.nextToken()) != nullptr) {
            UdpBasicApp::destAddressStr.push_back(token);
            inet::L3Address result;
            inet::L3AddressResolver().tryResolve(token, result);
            if (result.isUnspecified())
                EV_ERROR << "cannot resolve destination address: " << token << endl;
            UdpBasicApp::destAddresses.push_back(result);
        }
        if(!firstSent) {
            buildPacket(index);
            std::cout<<"Latenza media per "<<collections.at(index).getSmartInstName()<<": "<<collections.at(index).getMeanLatency()<<" (con "<<collections.at(index).getRecords().size()<<" records)"<<std::endl;
            UdpBasicApp::sendPacket();
        }

    }

};

Define_Module(ServerSmartInstrumentApp); //associa la classe al modulo
