/*
 * MobileStation.cpp
 *
 *  Created on: 21 d�c. 2019
 *      Author: Ismail Bagayoko
 */


#include <iostream>
#include <cstring>
#include <fstream>
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
     cDoubleHistogram delayHist;


protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    virtual simtime_t transmissionDelay();
    virtual simtime_t getSleepWindow();

};

Define_Module(MobileStation);

MobileStation::MobileStation(){}

MobileStation::~MobileStation(){}
void MobileStation::initialize(){
    scheduleAt(par("sleepCycle"), new cMessage(READY_MSG_NAME));

    delayHist.setName("OverallDelays");
}

/**
 * Service Time 
 */
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

    simtime_t Tc = par("sleepCycle");///.doubleValueInUnit("ms");
    simtime_t t = simTime() ;
    long n = floor(t) / Tc;



    EV << "n = " << n <<endl;
    return Tc- ( t - n*Tc);
}
void MobileStation::handleMessage(cMessage *msg){
    string msgName = string(msg->getName());

    if (msgName ==  EMPTY_MSG_NAME) {
            // Go to sleep
            //  We need to find the reminder time of sleep cycle to sleep
            // Tl = simtime() - awakeTime
            // Tc from parameters
            // Ts = Tc - Tl

            simtime_t sleepWindow = getSleepWindow();
            scheduleAt(simTime()+sleepWindow, new cMessage(READY_MSG_NAME));
            delete msg;
        }
        if(msgName == READY_MSG_NAME) {
            // Let BS know I am ready to receive new Packets
            send(msg, "gate$o");

        }
        if( msgName == PACKET_MSG_NAME ){
            // New Packet has arrived
            // Todo : collect stats
            simtime_t transTime = transmissionDelay();

            simtime_t endTime = simTime()+transTime;
            scheduleAt(endTime, new cMessage(READY_MSG_NAME));
            simtime_t overallDelay = endTime - msg->getCreationTime();

            // Record delay
            delayHist.collect(overallDelay);
            delete msg;

        }

}

/**
 * Exportation des valeurs pour Latex pgfplots
 */

void MobileStation::finish(){

        EV << "Overall Delay, mean: " << delayHist.getMean()  << endl;

        EV << endl;

        ofstream dout ("output/delay-0." + to_string(int(par("lambda").doubleValue())) +  ".dat", ios::out | ios::app );

        dout<<"(" <<par("sleepCycle").doubleValue() << ", " << delayHist.getMean()<< ")";


        recordScalar("delay", delayHist.getMean());
}
