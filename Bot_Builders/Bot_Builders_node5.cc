#include <string.h>
#include <omnetpp.h>
#include <stdio.h>

using namespace omnetpp;
class Bot_Builders_node5 : public cSimpleModule
{
  private:
    int limit;
    int src,dst;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void forwardMessage(cMessage *msg);
};

// The module class needs to be registered with OMNeT++
Define_Module(Bot_Builders_node5);

void Bot_Builders_node5::initialize()
{
    limit = par("limit");
    src= par("source");
    dst=par("destination");
    if(getIndex() == src) {
        char msgname[20];
        sprintf(msgname,"Lab5Msg");
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0.0, msg);

    }/*
    if (par("sendMsgOnInit").boolValue() == true) {
            EV << "Sending initial message\n";
            cMessage *msg = new cMessage("tictocMsg");
            send(msg, "out");
        }*/
    // Set a timer to delete this message after 3 seconds

}

void Bot_Builders_node5::handleMessage(cMessage *msg)
{
    // Check if the message is the delete timer
    if(getIndex()==dst){
        EV << "Message " << msg << " arrived.\n";
        delete msg;
    }
    else{
        forwardMessage(msg);
    }

}

void Bot_Builders_node5::forwardMessage(cMessage *msg)
{/*
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `gate[]'.
    int n = gateSize("gate");
    // Get the index of the arrival gate
    int incomingGateIndex = msg->getArrivalGate()->getIndex();
    EV << "Forwarding message " << msg << " to all gates except gate[" << incomingGateIndex << "]\n";
    bool sent = false;

    // Forward the message to all gates except the incoming gate
    for (int k = 0; k < n; ++k) {
        if (k != incomingGateIndex) {
            cMessage *copy = msg->dup();  // Create a duplicate of the message
            send(copy, "gate$o", k);
            sent = true;
        }
    }
    if (!sent) {
        delete msg;
    }*/
    int n = gateSize("gate");

        // Check if the message arrived through a gate or was scheduled
        cGate *arrivalGate = msg->getArrivalGate();
        int incomingGateIndex = (arrivalGate != nullptr) ? arrivalGate->getIndex() : -1;

        EV << "Forwarding message " << msg->getName() << " to all gates except gate[" << incomingGateIndex << "]\n";

        // Send the message to all gates except the incoming gate
        for (int k = 0; k < n; ++k) {
            if (k != incomingGateIndex) {
                // Create a duplicate for each outgoing gate
                cMessage *copy = msg->dup();
                send(copy, "gate$o", k);  // Send the copy to gate[k]
            }
        }

        // Delete the original message after forwarding
        delete msg;
}
