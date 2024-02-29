#include "processXML.h"
#include "tinyxml.h"
#include <iostream>
#include <string>

#include "Printer.h"
#include "Job.h"

using namespace std;

Printer* createPrinter(string name, int emissions, int speed){
    Printer* newPrinter = new Printer(name, emissions, speed);
    return newPrinter;
}

Job* createJob(int jobnumber, int pagecount, string username){
    Job* newJob = new Job(jobnumber, pagecount, username);
    return newJob;
}

bool readXML(FILE* filename){ //change bool to void once error messages have been implemented
    TiXmlDocument doc;

    if (!doc.LoadFile(filename)) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return false; //replace with error message
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *object = root->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
        string objectType = object->Value();

        if (objectType == "DEVICE"){
            string name;
            int emission;
            int speed;

            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string specification = elem->Value();

                for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                    TiXmlText* text = e->ToText();
                    if(text == NULL)
                        continue;
                    string element = text->Value();
                    if (specification == "name"){
                        name = element;
                    }
                    else if (specification == "emissions"){
                        emission = stoi(element);
                    }
                    else if (specification == "speed"){
                       speed = stoi(element);
                    }
                }
            }
            createPrinter(name, emission, speed); //send to datastructure or something
        }

        if (objectType == "JOB"){
            int jobnumber;
            int pagecount;
            string username;

            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string specification = elem->Value();

                for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                    TiXmlText* text = e->ToText();
                    if(text == NULL)
                        continue;
                    string element = text->Value();
                    if (specification == "jobnumber"){
                        jobnumber = stoi(element);
                    }
                    else if (specification == "pagecount"){
                        pagecount = stoi(element);
                    }
                    else if (specification == "username"){
                        username = element;
                    }
                }
            }
            createJob(jobnumber, pagecount, username); //send to datastructure or something
        }
    }
    doc.Clear();
    return true; //delete once error messages in place
}






