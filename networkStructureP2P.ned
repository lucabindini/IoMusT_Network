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

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.Eth1G;
import inet.node.ethernet.Eth100M;
import inet.node.ethernet.Eth10M;
import inet.node.ethernet.EtherSwitch;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import inet.node.wireless.AccessPoint;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;


network networkStructureP2P
{
    @display("bgb=1592.8251,626.145");

    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=125.99,90.829994");
        }

        smartInst1: WirelessHost {
            @display("p=683.07697,280.76923");
        }

        smartInst2: WirelessHost {
            @display("p=713.07697,216.92308");
        }

        smartInst3: WirelessHost {
            @display("p=779.2308,191.53847");
        }

        smartInst4: WirelessHost {
            @display("p=848.46155,206.92308");
        }

        smartInst5: WirelessHost {
            @display("p=896.1539,260");
        }

        smartInst6: WirelessHost {
            @display("p=900.7693,326.15387");
        }

        smartInst7: WirelessHost {
            @display("p=843.07697,377.69232");
        }

        smartInst8: WirelessHost {
            @display("p=778.46155,387.69232");
        }

        smartInst9: WirelessHost {
            @display("p=720,377.69232");
        }

        smartInst10: WirelessHost {
            @display("p=683.07697,333.07693");
        }

        visualizer: IntegratedCanvasVisualizer {
            @display("p=125.99,272.49");
        }

        accessPointSI: AccessPoint {
            @display("p=795.38464,298.46155");
        }

        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=125.99,445.36");
        }

    connections:
}

