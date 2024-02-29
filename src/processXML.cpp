#include "processXML.h"
/*#include <iostream>
#include "tinyxml.h"
#include "CD.h"
#include "Catalog.h"
#include <string>
using namespace std;

CD* createCD(string t, string a, int y, float p){
    CD* newcd = new CD();
    newcd->setTitle(t);
    newcd->setArtist(a);
    newcd->setYear(y);
    newcd->setPrice(p);
    return newcd;
}

CD* xmlToCD(){
    TiXmlDocument doc;
    string title = "";
    string artist = "";
    int year = 0;
    float price = 0;

    if (!doc.LoadFile("eenCD.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return nullptr;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *elem = root->FirstChildElement(); elem != NULL;
         elem = elem->NextSiblingElement()) {
        string elemName = elem->Value();

        for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
            TiXmlText* text = e->ToText();
            if(text == NULL)
                continue;
            string element = text->Value();
            if (elemName == "TITLE"){
                title = element;
            }
            else if (elemName == "ARTIST"){
                artist = element;
            }
            else if (elemName == "YEAR"){
                year = stoi(element);
            }
            else if (elemName == "PRICE"){
                price = stof(element);
            }
        }
    }
    doc.Clear();
    return createCD(title, artist, year, price);
}

void xmlToCatalog(Catalog* c){
    TiXmlDocument doc;
    string title = "";
    string artist = "";
    int year = 0;
    float price = 0;

    if (!doc.LoadFile("cdCatalog.xml")) {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement* cd = root->FirstChildElement(); cd != NULL;
         cd = cd->NextSiblingElement()) {

        for (TiXmlElement *elem = cd->FirstChildElement(); elem != NULL;
             elem = elem->NextSiblingElement()) {
            string elemName = elem->Value();

            for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                TiXmlText* text = e->ToText();
                if(text == NULL)
                    continue;
                string element = text->Value();
                if (elemName == "TITLE"){
                    title = element;
                }
                else if (elemName == "ARTIST"){
                    artist = element;
                }
                else if (elemName == "YEAR"){
                    year = stoi(element);
                }
                else if (elemName == "PRICE"){
                    price = stof(element);
                }
            }
        }
        c->addCD(createCD(title, artist, year, price));
    }
}

int main() {
    CD cd = *xmlToCD();
    cd.printCDData();

    Catalog c;
    xmlToCatalog(&c);
    c.printCatalog();
}*/





