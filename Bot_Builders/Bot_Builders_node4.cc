#include <string.h>
#include <omnetpp.h>
#include <stdio.h>

using namespace omnetpp;

class Bot_Builders_node4 : public cSimpleModule
{
  private:
    int counter;
    int src,dst;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void forwardMessage(cMessage *msg);
};

// The module class needs to be registered with OMNeT++
Define_Module(Bot_Builders_node4);

void Bot_Builders_node4::initialize()
{
    counter = par("limit");
    src= par("source");
    dst=par("destination");
    if(getIndex() == src) {
        char msgname[20];
        sprintf(msgname,"Lab4Msg");
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0.0, msg);

    }/*
    if (par("sendMsgOnInit").boolValue() == true) {
            EV << "Sending initial message\n";
            cMessage *msg = new cMessage("tictocMsg");
            send(msg, "out");
        }*/
}

void Bot_Builders_node4::handleMessage(cMessage *msg)
{
    if(getIndex()==dst || counter == 0){
        EV << "Message " << msg << " arrived.\n";
        delete msg;
    }
    else{
        forwardMessage(msg);
    }

}

void Bot_Builders_node4::forwardMessage(cMessage *msg)
{
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `gate[]'.
    int n = gateSize("gate");
    int k = intuniform(0, n-1); //random forwarding

    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    // $o and $i suffix is used to identify the input/output part of a two way gate
    send(msg, "gate$o", k);
}
