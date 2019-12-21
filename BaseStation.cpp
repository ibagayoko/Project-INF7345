/*
 * BaseStation.cpp
 *
 *  Created on: 21 déc. 2019
 *      Author: Ismail Bagayoko
 */


#include <iostream>
#include <cstring>
#include <omnetpp.h>

#define PACKET_MSG_NAME "packet"
#define READY_MSG_NAME "ready"
#define EMPTY_MSG_NAME "empty"

using namespace std;
using namespace omnetpp;

class BaseStation : public cSimpleModule {

public:
    BaseStation();
     ~BaseStation();
private:
    cQueue buffer;
    cMessage * endServiceEvent;
    simtime_t service_time;


protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

};

Define_Module(BaseStation);

BaseStation::BaseStation(){}

BaseStation::~BaseStation(){}

void BaseStation::initialize() {}

void BaseStation::handleMessage(cMessage *msg){
    // Nouveau message a ajouter a la file
    string msgName = string(msg->getName());
    if(msgName == PACKET_MSG_NAME){
        buffer.insert(msg);
        EV << "New Packet" << endl;
    }
    // Listenning Window
    else if (msgName ==  READY_MSG_NAME){
        cMessage* pkt;
        if(!buffer.isEmpty()){
            // We got some Message
            pkt = (cMessage *) buffer.pop();
        } else {
            // No more Message go Back to sleep
            pkt = new cMessage(EMPTY_MSG_NAME);
        }
        // Message to Mobile
        send(pkt, "gate$o");

        delete msg;
    }

    // MS is sleeping Here
}

