class SmartInstrumentRecord {

private:
    int BPM;
    int sendingTime;
    int receivingTime;
    int latency;

public:
    SmartInstrumentRecord(int BPM, int sendingTime, int receivingTime) {
        this->BPM = BPM;
        this->sendingTime = sendingTime;
        this->receivingTime = receivingTime;
        latency = this->receivingTime - this->sendingTime;
    }

    int getBpm() const {
        return BPM;
    }

    int getLatency() const {
        return latency;
    }

    int getReceivingTime() const {
        return receivingTime;
    }

    int getSendingTime() const {
        return sendingTime;
    }
};
