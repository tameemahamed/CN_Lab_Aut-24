#include <string.h>
#include <omnetpp.h>
#include <stdio.h>


using namespace omnetpp;

#include "frame_BB_m.h"

class Bot_Builders_node5 : public cSimpleModule
{
  private:
    int energy;
    int counter;
    int src,dst;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void forwardMessage(frame_BB *msg);
    virtual frame_BB *generateMessage();
};

// The module class needs to be registered with OMNeT++
Define_Module(Bot_Builders_node5);

void Bot_Builders_node5::initialize()
{
    counter = par("limit");
    int src = par("source");
    if(getIndex() == src) {
        frame_BB *msg = generateMessage();
        scheduleAt(0.0, msg);

    }
}

void Bot_Builders_node5::handleMessage(cMessage *msg)
{
    frame_BB *ttmsg = check_and_cast<frame_BB *>(msg);

        if (ttmsg->getDestination() == getIndex()) {
            // Message arrived.
            EV << "Message " << ttmsg << " arrived after " << ttmsg->getHopCount() << " hops.\n";
            bubble("ARRIVED, starting new one!");
            delete ttmsg;

            // Generate another one.
            EV << "Generating another message: ";
            frame_BB *newmsg = generateMessage();
            EV << newmsg << endl;
            forwardMessage(newmsg);
        }
        else {
            // We need to forward the message.
            forwardMessage(ttmsg);
        }

}

void Bot_Builders_node5::forwardMessage(frame_BB *msg)
{
    // In this example, we just pick a random gate to send it on.
    // We draw a random number between 0 and the size of gate `gate[]'.
    msg->setHopCount(msg->getHopCount()+1);


    int n = gateSize("gate");
    int k = intuniform(0, n-1); //random forwarding

    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    // $o and $i suffix is used to identify the input/output part of a two way gate
    send(msg, "gate$o", k);
}

frame_BB *Bot_Builders_node5::generateMessage()
{
    char frameName[20];
    int src = par("source");
    int dest=par("destination");
    sprintf(frameName, "tic-%d-to-%d", src, dest);

    // Create message object and set source and destination field.
    frame_BB *msg = new frame_BB(frameName);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}
