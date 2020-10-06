#include "inet/applications/udpapp/UdpBasicApp.h"
#include <fstream>
#include <string.h>

using namespace omnetpp;

class AdvancedSmartInstrumentApp: public inet::UdpBasicApp {
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
            correctionLatency = int(omnetpp::simTime().dbl()*1000) - std::stoi(result.at(2));
            std::cerr<<name<<" musicista professionista ha avuto un BPM medio di: "<<result.at(1)<<" rispetto al BPM di riferimento di: "<<nominalBPM<<" con una latenza dal server di: "<<correctionLatency<<std::endl;
            UdpBasicApp::processPacket(pk);
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
        BPM = (nominalBPM-10) + (rand() % static_cast<int>((nominalBPM+10) - (nominalBPM-10) + 1));
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

Define_Module(AdvancedSmartInstrumentApp); //associa la classe al modulo
