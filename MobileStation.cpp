/*
 * MobileStation.cpp
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

class MobileStation : public cSimpleModule {

public:
    MobileStation();
     ~MobileStation();
private:


protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual simtime_t transmissionDelay();
    virtual simtime_t getSleepWindow();

};

Define_Module(MobileStation);

MobileStation::MobileStation(){}

MobileStation::~MobileStation(){}
void MobileStation::initialize(){
    scheduleAt(par("sleepCycle").doubleValue(), new cMessage(READY_MSG_NAME));
}

simtime_t MobileStation::transmissionDelay(){
    double U = uniform(0., 1.);
    double H = par("higherBound");
    double L = par("lowerBound");
    double alpha = par("alpha");


    double x = pow((-(U*pow(H,alpha) - U* pow(L, alpha) - pow(H, alpha))/ (pow(H, alpha )* pow(L,alpha))),(-1/alpha));

    return x;
}

/**
 * Get the remind time in a sleep cycle after listening window
 *
 */
simtime_t MobileStation::getSleepWindow(){
    simtime_t t = simTime();
    simtime_t Tc = par("sleepCycle").doubleValue();
    long n = floor(t) / Tc;
    return t - n*Tc;
}
void MobileStation::handleMessage(cMessage *msg){
    string msgName = string(msg->getName());

    if (msgName ==  EMPTY_MSG_NAME) {
            // Go to sleep
            //  We need to find the reminder time of sleep cycle to sleep
            // Tl = simtime() - awakeTime
            // Tc from parameters
            // Ts = Tc - Tl

            simtime_t transTime = getSleepWindow();
            scheduleAt(simTime()+transTime, new cMessage(READY_MSG_NAME));


        }
        if(msgName == READY_MSG_NAME) {
            // Let BS know I am ready to receive new Packets
            send(msg, "gate$o");

        }
        if( msgName == PACKET_MSG_NAME ){
            // New Packet has arrived
            // Todo : collect stats
            simtime_t transTime = transmissionDelay();
            scheduleAt(simTime()+transTime, new cMessage(READY_MSG_NAME));

        }



}
