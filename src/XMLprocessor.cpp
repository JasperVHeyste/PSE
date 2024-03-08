#include "XMLprocessor.h"
#include "DesignByContract.h"
//#include "DesignByContract_windows.h"

XMLprocessor::XMLprocessor() {
    initializecheck = this;
    ENSURE(properlyinitialized(), "constructor must end in properlyInitialized state");
}

bool XMLprocessor::properlyinitialized() {
    return initializecheck == this;
}

bool XMLprocessor::checkStringIsPositiveInt(std::string s){
    REQUIRE(properlyinitialized(), "XMLprocessor is not properly initialized");
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

vector<map<string, string>> XMLprocessor::readXML(const char* filename, std::ostream& outputstream){
    string fname = filename;
    string ftype;
    for (unsigned int i = fname.length()-4; i < fname.length(); i++){
        ftype += fname[i];
    }
    REQUIRE(properlyinitialized(), "XMLprocessor is not properly initialized");
    REQUIRE(ftype == ".xml", "Inputfile has to be an xml file");
    previousjobnumbers.clear();
    vector<map<string, string>> output;
    vector<map<string, string>> emptyoutput;
    TiXmlDocument doc;

    if (!doc.LoadFile(filename)) {
        outputstream << doc.ErrorDesc() << std::endl;
        doc.Clear();
        return emptyoutput;
    }

    TiXmlElement *root = doc.FirstChildElement();

    for (TiXmlElement *object = root->FirstChildElement(); object != NULL; object = object->NextSiblingElement()) {
        string objectType = object->Value();

        if (objectType == "DEVICE"){
            map<string, string> newobject;
            newobject["type"] = "device";

            bool validinfo = true;

            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string specification = elem->Value();

                for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                    TiXmlText* text = e->ToText();
                    if(text == NULL)
                        continue;
                    string element = text->Value();
                    if (specification == "name"){
                        newobject["name"] = element;
                    }
                    else if (specification == "emissions"){
                        newobject["emissions"] = element;
                        if (not checkStringIsPositiveInt(element)){
                            validinfo = false;
                        }
                    }
                    else if (specification == "speed"){
                        newobject["speed"] = element;
                        if (not checkStringIsPositiveInt(element)){
                            validinfo = false;
                        }
                    }
                    else{
                        validinfo = false;
                    }
                }
            }

            if (validinfo and newobject.size() == 4){
                output.push_back(newobject);
            }
            else{
                outputstream << "Invalid information" << std::endl;
            }
        }

        else if (objectType == "JOB"){
            map<string, string> newobject;
            newobject["type"] = "job";

            bool validinfo = true;

            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string specification = elem->Value();

                for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                    TiXmlText* text = e->ToText();
                    if(text == NULL)
                        continue;
                    string element = text->Value();
                    if (specification == "jobNumber"){
                        newobject["jobNumber"] = element;
                        if (not checkStringIsPositiveInt(element)){
                            validinfo = false;
                        }
                        else {
                            int jn = stoi(element);
                            for (unsigned int i = 0; i < previousjobnumbers.size(); i++){
                                if (jn == previousjobnumbers[i]){
                                    outputstream << "Inconsistent printing system" << std::endl;
                                    doc.Clear();
                                    return emptyoutput;
                                }
                            }
                            previousjobnumbers.push_back(jn);
                        }
                    }
                    else if (specification == "pageCount"){
                        newobject["pageCount"] = element;
                        if (not checkStringIsPositiveInt(element)){
                            validinfo = false;
                        }
                    }
                    else if (specification == "userName"){
                        newobject["userName"] = element;
                    }
                    else{
                        validinfo = false;
                    }
                }
            }

            if (validinfo and newobject.size() == 4){
                output.push_back(newobject);
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








