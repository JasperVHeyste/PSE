#include "readXML.h"
#include "tinyxml.h"
#include <iostream>

vector<map<string, string>> readXML(const char* filename){
    vector<map<string, string>> output;
    TiXmlDocument doc;

    if (!doc.LoadFile(filename)) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return output; //replace with error message
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *object = root->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
        string objectType = object->Value();

        if (objectType == "DEVICE"){
            map<string, string> newdevice;
            newdevice["type"] = "device";

            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string specification = elem->Value();

                for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                    TiXmlText* text = e->ToText();
                    if(text == NULL)
                        continue;
                    string element = text->Value();
                    if (specification == "name"){
                        newdevice["name"] = element;
                    }
                    else if (specification == "emissions"){
                        newdevice["emissions"] = element;
                    }
                    else if (specification == "speed"){
                        newdevice["speed"] = element;
                    }
                }
            }
            output.push_back(newdevice);
        }

        if (objectType == "JOB"){
            map<string, string> newjob;
            newjob["type"] = "job";

            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string specification = elem->Value();

                for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                    TiXmlText* text = e->ToText();
                    if(text == NULL)
                        continue;
                    string element = text->Value();
                    if (specification == "jobnumber"){
                        newjob["jobnumber"] = element;
                    }
                    else if (specification == "pagecount"){
                        newjob["pagecount"] = element;
                    }
                    else if (specification == "username"){
                        newjob["username"] = element;
                    }
                }
            }
            output.push_back(newjob);
        }
    }
    doc.Clear();
    return output;
}






