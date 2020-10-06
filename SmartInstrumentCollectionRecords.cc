#include <iostream>
#include <vector>
#include "SmartInstrumentRecord.cc"

class SmartInstrumentCollectionRecords {

private:
    std::string smartInstName;
    std::vector<SmartInstrumentRecord> records;
    int meanBPM;
    int meanLatency;

public:
    SmartInstrumentCollectionRecords(std::string smartInstName) {
            this->smartInstName = smartInstName;
        }

    const std::string& getSmartInstName() const {
        return smartInstName;
    }

    const std::vector<SmartInstrumentRecord>& getRecords() const {
            return records;
        }

    int getMeanBPM() {
        if(records.size() != 0) {
            int sum = 0;
            for(int i = 0; i < records.size(); i++)
                sum += records.at(i).getBpm();
            return sum / records.size();
        }
        else{
            return -1;
        }
    }

    int getMeanLatency() {
            if(records.size() != 0) {
                int sum = 0;
                for(int i = 0; i < records.size(); i++)
                    sum += records.at(i).getLatency();
                return sum / records.size();
            }
            else{
                return -1;
            }
        }

    void addRecord(int BPM, int sendingTime, int receivingTime){
        SmartInstrumentRecord record(BPM, sendingTime, receivingTime);
        records.push_back(record);
    }

    void clearCollection() {
        records.clear();
    }

};
