/*
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
    int src,dst;
    simsignal_t arrivalSignal;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void forwardMessage(frame_BB *msg);
    virtual frame_BB *generateMessage();
};

// The module class needs to be registered with OMNeT++
Define_Module(Bot_Builders_node7);

void Bot_Builders_node7::initialize()
{
    counter = par("limit");
    int src = par("source");
    dst = par("destination");
    if(getIndex() == src) {
        frame_BB *msg = generateMessage();
        scheduleAt(simTime() + 5.0, new cMessage("PeriodicMessage"));
        //scheduleAt(0.0, msg);

    }
}

void Bot_Builders_node7::handleMessage(cMessage *msg)
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
        if (msg->isSelfMessage()) {
            // Check if it's a periodic message
            frame_BB *newMsg = generateMessage();
            forwardMessage(newMsg);
            // Reschedule next periodic message
            scheduleAt(simTime() + 5.0, msg); // Reschedule itself
        } else {
            frame_BB *ttmsg = check_and_cast<frame_BB *>(msg);
            // (Rest of the original handleMessage logic remains unchanged)
        }
        if (ttmsg->getDestination() == getIndex()) {
            // Message arrived
            EV << "Message " << ttmsg << " arrived after " << ttmsg->getHopCount() << " hops.\n";
            bubble("ARRIVED, starting new one!");

            // Increment received messages counter
            int receivedCount = par("receivedCount");
            receivedCount++;
            // Update parameter (or use a signal for better tracking)
            getDisplayString().setTagArg("t", 0, std::to_string(receivedCount).c_str());

            delete ttmsg;
            // Generate another one...
        }

}

void Bot_Builders_node7::forwardMessage(frame_BB *msg)
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

frame_BB *Bot_Builders_node7::generateMessage()
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
*/
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
    cOutVector hopcntvec;
    cOutVector msgarrivalvec;

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
    hopcntvec.setName("HopCount");
    msgarrivalvec.setName("MessageArrivals");

    // Register signals for statistics
    sentSignal = registerSignal("messagesSent");
    receivedSignal = registerSignal("messagesReceived");

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

            hopcntvec.record(ttmsg->getHopCount());
            msgarrivalvec.record(1);

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


