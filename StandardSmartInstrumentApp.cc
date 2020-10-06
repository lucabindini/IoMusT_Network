#include "inet/applications/udpapp/UdpBasicApp.h"
#include <fstream>
#include <string.h>


using namespace omnetpp;

class StandardSmartInstrumentApp: public inet::UdpBasicApp {

protected:
    std::string name;
    std::string msg;
    int BPM;
    int nominalBPM;
    int correctionLatency;

    virtual void initialize(int stage) override {
        UdpBasicApp::initialize(stage);
        if(firstCall) {
            name = std::string(packetName);
            acquireNominalBPM();
            BPM = nominalBPM;
            firstCall = false;
        }
    }

    virtual void sendPacket() override {
        buildPacket();
        UdpBasicApp::sendPacket();
    }

    virtual void processPacket(inet::Packet *pk) override {
            //std::cout << name <<" riceve un pacchetto ricevuto dal server: " + std::string(pk->getName()) << std::endl;
            std::vector<std::string> result = split(pk->getName(), '-');
            UdpBasicApp::processPacket(pk);
            BPM -= (std::stoi(result.at(1))-nominalBPM);
            correctionLatency = int(omnetpp::simTime().dbl()*1000) - std::stoi(result.at(2));
            std::cout<<name<<" musicista principiante ha avuto un BPM medio di: "<<result.at(1)<<" BPM attuali: "<<BPM<<" con una latenza dal server di: "<<correctionLatency<< std::endl;
        }

private:
    bool firstCall = true;

    void acquireNominalBPM() {
        std::string line;
        std::ifstream myfile ("nominal_BPM.txt");
        if (myfile.is_open()) {
            while ( getline (myfile,line) )
            myfile.close();
        }
        else
            std::cerr << "Unable to open file" << std::endl;
        nominalBPM = std::stoi(line);
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
        if(a <= 25) {
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

Define_Module(StandardSmartInstrumentApp); //associa la classe al modulo
