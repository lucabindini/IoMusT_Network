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


network networkStructureCS
{
    @display("bgb=3000,2000");

    submodules:
        configurator: Ipv4NetworkConfigurator {
            @display("p=178.22063,96.53617");
        }

        smartInst1: WirelessHost {
            @display("p=780.0001,1782.3003");
        }

        smartInst2: WirelessHost {
            @display("p=808.6001,1732.9003");
        }

        smartInst3: WirelessHost {
            @display("p=875.42004,1733.9402");
        }

        smartInst4: WirelessHost {
            @display("p=925.6001,1740.7002");
        }

        smartInst5: WirelessHost {
            @display("p=925.6001,1814.8003");
        }

        smartInst6: WirelessHost {
            @display("p=893.1001,1797.9003");
        }

        smartInst7: WirelessHost {
            @display("p=893.1001,1857.7002");
        }

        smartInst8: WirelessHost {
            @display("p=795.6001,1862.9003");
        }

        smartInst9: WirelessHost {
            @display("p=851.5001,1825.2002");
        }

        smartInst10: WirelessHost {
            @display("p=780.0001,1814.8003");
        }

        routerSI: Router {
            @display("p=850.26086,1217.841");
        }

        backbone: Router {
            @display("p=827.98334,152.23012;i=abstract/router2");
        }

        switchSI: EtherSwitch {
            @display("p=851.7601,1553.1101");
        }

        visualizer: IntegratedCanvasVisualizer {
            @display("p=189.3594,337.8766");
        }

        routerServer: Router {
            @display("p=2082.9536,152.23012;b=106.9275,54.4725");
        }

        serverSmartInst: StandardHost {
            @display("p=2669.5964,152.23012");
        }

        accessPointSI: AccessPoint {
            @display("p=859.3001,1781.0002");
        }

        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=189.3594,579.21704");
        }

    connections:
        switchSI.ethg++ <--> Eth100M <--> routerSI.ethg++;
        routerSI.ethg++ <--> Eth100M <--> backbone.ethg++;
        routerServer.ethg++ <--> Eth100M <--> backbone.ethg++;
        serverSmartInst.ethg++ <--> Eth100M <--> routerServer.ethg++;
        accessPointSI.ethg++ <--> Eth100M <--> switchSI.ethg++;
}

