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


simple Bot_Builders_node
{
    gates:
        input in;
        output out;
}

//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Bot_Builders_net
{
    @display("bgb=523,264");
    submodules:
        C213019: Bot_Builders_node {
            @display("i=device/pc2;p=59,174");
        }
        C213029: Bot_Builders_node {
            @display("i=device/pc;p=414,198");
        }
        C213004: Bot_Builders_node {
            @display("p=262,51;i=device/pc");
        }
    connections:
        C213019.out --> {  delay = 100ms; } --> C213029.in;
        C213029.out --> {  delay = 100ms; } --> C213004.in;
        C213004.out --> {  delay = 100ms; } --> C213019.in;
}
