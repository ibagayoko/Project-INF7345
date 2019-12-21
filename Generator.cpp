/*
 * Generator.cpp
 *
 *  Created on: 21 déc. 2019
 *      Author: Ismail Bagayoko
 */



#include <iostream>
#include <cstring>
#include <omnetpp.h>

using namespace omnetpp;

class Generator : public cSimpleModule {



public:
     Generator();
     ~Generator();
private:
    cMessage * sendMsgEvent;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};



Define_Module(Generator);

Generator::Generator(){
    sendMsgEvent = nullptr;
}

 Generator::~Generator(){
    cancelAndDelete(sendMsgEvent);
}

void Generator::initialize(){
    sendMsgEvent = new cMessage("Creation de packet");
    scheduleAt(par("interArrivalTime"),  sendMsgEvent);
}

void Generator::handleMessage(cMessage *msg){
    // on envoie le packet sur le lien
    cMessage *pkt = new cMessage("packet");
    send(pkt, "out");

    // On prevoit un le prochain message
    simtime_t next_departure_time = simTime() + par("interArrivalTime");
    scheduleAt(next_departure_time, sendMsgEvent);

}



