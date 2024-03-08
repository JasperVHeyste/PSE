#include "readXML.h"
#include "DesignByContract.h"
//#include "DesignByContract_windows.h"

bool stringIsPositiveInteger(std::string s){
    for (char character : s){
        if (not isdigit(character)){
            return false;
        }
    }
    if (stoi(s) < 0){
        return false;
    }
    return true;
}

vector<map<string, string>> readXML(const char* filename, std::ostream& outputstream){
    string fname = filename;
    string ftype;
    for (unsigned int i = fname.length()-4; i < fname.length(); i++){
        ftype += fname[i];
    }
    REQUIRE(ftype == ".xml", "Inputfile has to be an xml file");
    vector<map<string, string>> output;
    TiXmlDocument doc;

    if (!doc.LoadFile(filename)) {
        outputstream << doc.ErrorDesc() << std::endl;
        doc.Clear();
        return output;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *object = root->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
        string objectType = object->Value();

        if (objectType == "DEVICE"){
            map<string, string> newdevice;
            newdevice["type"] = "device";

            bool validinfo = true;

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
                        if (not stringIsPositiveInteger(element)){
                            validinfo = false;
                        }
                    }
                    else if (specification == "speed"){
                        newdevice["speed"] = element;
                        if (not stringIsPositiveInteger(element)){
                            validinfo = false;
                        }
                    }
                    else{
                        validinfo = false;
                    }
                }
            }
            if (validinfo and newdevice.size() == 4) {
                output.push_back(newdevice);
            }
            else{
                outputstream << "Invalid information" << endl;
            }
        }

        else if (objectType == "JOB"){
            map<string, string> newjob;
            newjob["type"] = "job";

            bool validinfo = true;

            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string specification = elem->Value();

                for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                    TiXmlText* text = e->ToText();
                    if(text == NULL)
                        continue;
                    string element = text->Value();
                    if (specification == "jobNumber"){
                        newjob["jobNumber"] = element;
                        if (not stringIsPositiveInteger(element)){
                            validinfo = false;
                        }
                    }
                    else if (specification == "pageCount"){
                        newjob["pageCount"] = element;
                        if (not stringIsPositiveInteger(element)){
                            validinfo = false;
                        }
                    }
                    else if (specification == "userName"){
                        newjob["userName"] = element;
                    }
                    else{
                        validinfo = false;
                    }
                }
            }
            if (validinfo and newjob.size() == 4) {
                output.push_back(newjob);
            }
            else{
                outputstream << "Invalid information" << std::endl;
            }
        }

        else{
            outputstream << "Unrecognizable element" << std::endl;
        }
    }
    doc.Clear();
    return output;
}








