#include <iostream>
#include <string>
#include <fstream>

#include "building.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "buildings.h"

using namespace std;
using namespace tinyxml2;

int main () 
{   
    cout << "** NU Open Street Map **" << endl;
    cout << endl;
    string filename;
    XMLDocument xmldoc;

    cout << "Enter map filename>" << endl;
    getline(cin, filename);

    osmLoadMapFile(filename, xmldoc);

    // all node things
    Nodes nodes;

    nodes.readMapNodes(xmldoc);
    cout << "# of nodes: " << nodes.getNumMapNodes() << endl;

    // all building things
    Buildings buildings;
    buildings.readMapBuildings(xmldoc);
    cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;

    // promts user for commands
    string command;
    while (command != "$") {
        cout << "Enter building name (partial or complete), or * to list, or $ to end" << endl;
        getline(cin, command);

        if (command == "*") {
            for (Building& building : buildings.MapBuildings) {
                cout << building.ID << ": " << building.Name << ", " << building.StreetAddress << endl;
            }
        } 
        else {
            bool found = false;
            for (Building& building : buildings.MapBuildings) {
                if (building.Name.find(command) != string::npos) {
                    found = true;
                    cout << building.Name << endl;
                    cout << "Address: " << building.StreetAddress << endl;
                    cout << "Building ID: " << building.ID << endl;
                    cout << "Nodes:" << endl;

                    double lat;
                    double lon;
                    bool isEntrance;
                    for (long long id : building.NodeIDs) {
                        if (nodes.find(id, lat, lon, isEntrance)) {
                            cout << "  " << id << ": " << "(" << lat << ", " << lon << ")";
                            if (isEntrance) {
                                cout << ", is entrance";
                            }
                            cout << endl;
                        }
                        else {
                            cout << "  " << id << ": " << "** NOT FOUND **" << endl;
                        }
                    }
                }
            }
            if (found != true) {
                cout << "No such building" << endl;
            }
        }
    }

    // ending output
    cout << endl;
    cout << "** Done **" << endl;

    cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
    cout << "# of Nodes created: " << Node::getCreated() << endl;
    cout << "# of Nodes copied: " << Node::getCopied() << endl;

    return 0;
}