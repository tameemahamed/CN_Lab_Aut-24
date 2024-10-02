#include <string.h>
#include <omnetpp.h>
#include <stdio.h>

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Bot_Builders_node3 : public cSimpleModule
{
  private:
    int counter;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Bot_Builders_node3);

void Bot_Builders_node3::initialize()
{
    counter = par("limit");
    /*if (strcmp("C213004", getName()) == 0) {
        cMessage *msg = new cMessage("tictocMsg");
        send(msg, "out");

    }*/
    if (par("sendMsgOnInit").boolValue() == true) {
            EV << "Sending initial message\n";
            cMessage *msg = new cMessage("tictocMsg");
            send(msg, "out");
        }
}

void Bot_Builders_node3::handleMessage(cMessage *msg)
{
    counter--;
    if (counter == 0) {
        EV << getName() << "'s counter reached zero, deleting message\n";
        delete msg;
    }
    else {
        EV << getName() << "'s counter is " << counter << ", sending back message\n";
        send(msg, "out");
    }

}
