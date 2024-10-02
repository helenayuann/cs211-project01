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

    cout << endl;
    cout << "** Done **" << endl;

    cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
    cout << "# of Nodes created: " << Node::getCreated() << endl;
    cout << "# of Nodes copied: " << Node::getCopied() << endl;

    // all building things
    Buildings buildings;
    buildings.readMapBuildings(xmldoc);
    cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;

    return 0;
}