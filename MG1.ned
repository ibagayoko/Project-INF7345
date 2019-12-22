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


simple Generator
{
    parameters:
        volatile double interArrivalTime;
        @display("i=block/source");

    gates:
        output out;

}


simple BaseStation
{
    parameters:
        
		
        @display("i=device/antennatower");
    gates:
        input in;  // INput du generateur
        inout gate; // Input/ Output du Mobile divice.
}

simple MobileStation
{
    parameters:
        // PARETO DISTRIBUTION PARAMS
        double higherBound = default(4);
        double lowerBound = default(1);
        double alpha = default(2);
        
        
        double sleepCycle = default(20);
        @display("i=device/cellphone");
    gates:
        inout gate; // Input/Ouput du Base stattion.
}

network MG1
{
    @display("bgb=405.6,234.86667");
    submodules:
        generator: Generator {
            @display("p=46,113");
        }
        BS: BaseStation {
            @display("p=172,113");
        }

        MS: MobileStation {
            @display("p=340,113");
        }

    connections:
        generator.out --> BS.in;
        BS.gate <--> MS.gate;
}
