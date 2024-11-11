#include <string.h>
#include <omnetpp.h>
#include <stdio.h>

using namespace omnetpp;
#include "frame_BB_m.h"

class Bot_Builders_node7 : public cSimpleModule
{
  private:
    int energy;
    int counter;
    int src, dst;
    simsignal_t arrivalSignal;
    int messagesSent;
    int messagesReceived;
    simsignal_t sentSignal;
    simsignal_t receivedSignal;
    cOutVector hopCountVector;
    cOutVector messageArrivalsVector;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void forwardMessage(frame_BB *msg);
    virtual frame_BB *generateMessage();
};

// Register the module with OMNeT++
Define_Module(Bot_Builders_node7);

void Bot_Builders_node7::initialize()
{
    counter = par("limit");
    src = par("source");
    dst = par("destination");
    messagesSent = 0;
    messagesReceived = 0;

    // Register signals for statistics
    sentSignal = registerSignal("messagesSent");
    receivedSignal = registerSignal("messagesReceived");

    // Initialize output vectors.
    hopCountVector.setName("HopCount");            // Stores hop counts
    messageArrivalsVector.setName("MessageArrivals");  // Tracks arrivals


    if (getIndex() == src) {
        // Schedule the first periodic message
        scheduleAt(simTime() + 1.0, new cMessage("PeriodicMessage"));
    }
}

void Bot_Builders_node7::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        // Periodic message generation
        frame_BB *newMsg = generateMessage();
        forwardMessage(newMsg);
        messagesSent++;
        emit(sentSignal, messagesSent); // Emit the sent signal
        scheduleAt(simTime() + 1.0, msg); // Reschedule for the next periodic message
    } else {
        frame_BB *ttmsg = check_and_cast<frame_BB *>(msg);

        if (ttmsg->getDestination() == getIndex()) {
            // Message arrived
            messagesReceived++;
            emit(receivedSignal, messagesReceived); // Emit the received signal
            EV << "Message " << ttmsg << " arrived after " << ttmsg->getHopCount() << " hops.\n";
            bubble("ARRIVED, starting new one!");

            // Record the hop count to the vector.
            hopCountVector.record(ttmsg->getHopCount());

            // Track the arrival in the message arrivals vector.
            messageArrivalsVector.record(1);


            delete ttmsg;

            // Generate another one if necessary...
            if (messagesReceived < counter) {
                frame_BB *newMsg = generateMessage();
                forwardMessage(newMsg);
                messagesSent++;
                emit(sentSignal, messagesSent);
            }
        } else {
            // Forward the message
            forwardMessage(ttmsg);
        }
    }
}

void Bot_Builders_node7::forwardMessage(frame_BB *msg)
{
    msg->setHopCount(msg->getHopCount() + 1);
    int n = gateSize("gate");
    int k = intuniform(0, n - 1); // Random forwarding
    EV << "Forwarding message " << msg << " on gate[" << k << "]\n";
    send(msg, "gate$o", k);
}

frame_BB *Bot_Builders_node7::generateMessage()
{
    char frameName[20];
    sprintf(frameName, "tic-%d-to-%d", src, dst);
    frame_BB *msg = new frame_BB(frameName);
    msg->setSource(src);
    msg->setDestination(dst);
    return msg;
}


