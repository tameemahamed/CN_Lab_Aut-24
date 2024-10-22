//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2003 Ahmet Sekercioglu
// Copyright (C) 2003-2015 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


simple Bot_Builders_node5
{
    parameters:
        bool sendMsgOnInit = default(false); // whether the module should send out a message on initialization
        int limit = default(2);   // another parameter with a default value
        int source = default(0);
        int destination = default(5);
        @display("i=block/routing");
    gates:
        inout gate[];
}

//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Bot_Builders_net5
{
    @display("bgb=615,604");
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }
    submodules:
        node_Bot_Builders[10]: Bot_Builders_node4 {
            @display("i=abstract/router");
        }
    connections:
        node_Bot_Builders[0].gate++ <--> Channel <--> node_Bot_Builders[1].gate++;
        node_Bot_Builders[1].gate++ <--> Channel <--> node_Bot_Builders[2].gate++;
        node_Bot_Builders[1].gate++ <--> Channel <--> node_Bot_Builders[4].gate++;
        node_Bot_Builders[3].gate++ <--> Channel <--> node_Bot_Builders[4].gate++;
        node_Bot_Builders[4].gate++ <--> Channel <--> node_Bot_Builders[5].gate++;

        node_Bot_Builders[5].gate++ <--> Channel <--> node_Bot_Builders[6].gate++;
		node_Bot_Builders[5].gate++ <--> Channel <--> node_Bot_Builders[7].gate++;
        node_Bot_Builders[5].gate++ <--> Channel <--> node_Bot_Builders[8].gate++;
        node_Bot_Builders[8].gate++ <--> Channel <--> node_Bot_Builders[9].gate++;
}
