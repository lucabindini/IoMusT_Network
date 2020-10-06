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
            @display("p=639.327,298.792");
        }

        smartInst2: WirelessHost {
            @display("p=652.50903,206.518");
        }

        smartInst3: WirelessHost {
            @display("p=738.192,206.518");
        }

        smartInst4: WirelessHost {
            @display("p=909.558,226.291");
        }

        smartInst5: WirelessHost {
            @display("p=909.558,331.747");
        }

        smartInst6: WirelessHost {
            @display("p=823.875,206.518");
        }

        smartInst7: WirelessHost {
            @display("p=725.01,404.24802");
        }

        smartInst8: WirelessHost {
            @display("p=823.875,421.824");
        }

        smartInst9: WirelessHost {
            @display("p=909.558,421.824");
        }

        smartInst10: WirelessHost {
            @display("p=615.16003,404.24802");
        }

        visualizer: IntegratedCanvasVisualizer {
            @display("p=125.99,272.49");
        }

        accessPointSI: AccessPoint {
            @display("p=788.723,296.595");
        }

        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=125.99,445.36");
        }

    connections:
}

