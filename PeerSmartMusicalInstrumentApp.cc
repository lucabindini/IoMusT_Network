#include "inet/applications/udpapp/UdpBasicApp.h"
#include <fstream>
#include <string.h>


using namespace omnetpp;

class PeerSmartInstrumentApp: public inet::UdpBasicApp {

protected:
    std::string name;
    std::string msg;
    int BPM;
    int correctionLatency;

    virtual void initialize(int stage) override {
        UdpBasicApp::initialize(stage);
        if(firstCall) {
            name = std::string(packetName);
            initBPM();
            firstCall = false;
        }
    }

    virtual void sendPacket() override {
        buildPacket();
        UdpBasicApp::sendPacket();
    }

    virtual void processPacket(inet::Packet *pk) override {
            std::vector<std::string> result = split(pk->getName(), '-');
            UdpBasicApp::processPacket(pk);
            if(result.at(1) == "sub")
                BPM -= std::stoi(result.at(2));
            else
                BPM += std::stoi(result.at(2));
            correctionLatency = int(omnetpp::simTime().dbl()*1000) - std::stoi(result.at(4));
            std::cout<<name<<" ha avuto un BPM medio di: "<<result.at(3)<<" BPM attuali: "<< BPM <<" con una latenza dal nodo sink di: " <<correctionLatency<< std::endl;
        }

private:
    bool firstCall = true;

    void initBPM() {
        std::string line;
        std::ifstream myfile ("nominal_BPM.txt");
        if (myfile.is_open()) {
            while ( getline (myfile,line) )
            myfile.close();
        }
        else
            std::cerr << "Unable to open file" << std::endl;
        BPM = std::stoi(line);
    }

    void buildPacket() {
        msg = "-";
        acquireBPMFromSI();
        msg+= std::to_string(BPM);
        msg+= "-";
        msg += std::to_string(int(omnetpp::simTime().dbl()*1000));
        strcpy(packetName, (name + msg).c_str());
    }

    void acquireBPMFromSI() {
        int a = (rand() % 1000 + 1);
        //std::cout<<a<<std::endl;
        if(a <= 16) {
            BPM++;
        }
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
};

Define_Module(PeerSmartInstrumentApp); //associa la classe al modulo
