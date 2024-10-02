/*buildings.cpp*/

//
// A collection of buildings in the Open Street Map
// 
// Helena Yuan
// Northwestern University
// CS 211
// 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "buildings.h"
#include "osm.h"
#include "tinyxml2.h"

using namespace std;

void Buildings::readMapBuildings(XMLDocument& xmldoc) {
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    XMLElement* way = osm->FirstChildElement("way");
    while (way != nullptr)
    {
        if (osmContainsKeyValue(way, "building", "university")) {
            string name = osmGetKeyValue(way, "name");

            string streetAddr = osmGetKeyValue(way, "addr:housenumber") 
            + " "
            + osmGetKeyValue(way,"addr:street");

            const XMLAttribute* attribute = way->FindAttribute("id");
            long long id = attribute->Int64Value();

            XMLElement* nd = way->FirstChildElement("nd");
            Building B(id, name, streetAddr);

            while (nd != nullptr)
            {
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref!= nullptr);

                long long id = ndref->Int64Value();
                B.add(id);

                nd = nd->NextSiblingElement("nd");
            }
            MapBuildings.push_back(B);
        }
        way = way->NextSiblingElement("way");
    }
}

int Buildings::getNumMapBuildings() const {
  return (int) this->MapBuildings.size();
}