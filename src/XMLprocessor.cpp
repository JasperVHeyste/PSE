#include "XMLprocessor.h"

/**
 * Initialize XMLprocessor:
 * create pointer to self to check for proper initialization
 */
XMLprocessor::XMLprocessor() {
    initcheck = this;
    ENSURE(properlyInitialized(), "constructor must end in properlyInitialized state");
}

/**
 * Check if the XMLprocessor is properly inialized by checking if the pointer assigned in the constructor points to itself
 * @return true if properly initialzed, false if not
 */
bool XMLprocessor::properlyInitialized() const {
    return initcheck == this;
}

/**
 * Checks if an input string can be converted to a positive integer
 * @param s input string that will be checked
 * @return true if the string is a positive integer, false if not
 */
bool XMLprocessor::checkStringIsPositiveInt(std::string s) const{
    REQUIRE(properlyInitialized(), "XMLprocessor is not properly initialized");
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

/**
 * Read an XML file and convert it into a vector of maps containing pairs of keywords and values (eg. "type" = "scanner")
 * @param filename the filename of the xml that needs to be read
 * @param outputstream the outputstream in which any errors will be written
 * @return the vector containing maps
 */
vector<map<string, string>> XMLprocessor::readXML(const char* filename, std::ostream& outputstream){
    string fname = filename;
    string ftype;
    for (unsigned int i = fname.length()-4; i < fname.length(); i++){
        ftype += fname[i];
    }
    REQUIRE(properlyInitialized(), "XMLprocessor is not properly initialized");
    REQUIRE(ftype == ".xml", "Inputfile has to be an xml file");
    previousjobnumbers.clear();
    previouscompnumbers.clear();
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
            newobject["objecttype"] = "device";

            bool validinfo = true;
            string invalidinfomessage = "Invalid information DEVICE: ";

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
                            invalidinfomessage += "The value of the emissions element is not a positive integer. ";
                        }
                    }
                    else if (specification == "speed"){
                        newobject["speed"] = element;
                        if (not checkStringIsPositiveInt(element)){
                            validinfo = false;
                            invalidinfomessage += "The value of the speed element is not a positive integer. ";
                        }
                    }
                    else if (specification == "type"){
                        if (element == "bw" or element == "color" or element == "scan"){
                            newobject["type"] = element;
                        }
                        else{
                            validinfo = false;
                            invalidinfomessage += "The type of the device is not a valid option. ";
                        }
                    }
                    else if (specification == "cost"){
                        newobject["cost"] = element;
                        if (not checkStringIsPositiveInt(element)){
                            validinfo = false;
                            invalidinfomessage += "The value of the cost element is not a positive integer. ";
                        }
                    }
                    else{
                        validinfo = false;
                        invalidinfomessage += "Contains unrecognizeable parameter. ";
                    }
                }
            }

            if (not newobject.count("name")){
                validinfo = false;
                invalidinfomessage += "Missing name. ";
            }
            if (not newobject.count("speed")){
                validinfo = false;
                invalidinfomessage += "Missing speed value. ";
            }
            if (not newobject.count("emissions")){
                validinfo = false;
                invalidinfomessage += "Missing emissions value. ";
            }

            if (validinfo){
                output.push_back(newobject);
            }
            else{
                outputstream << invalidinfomessage << std::endl;
            }
        }

        else if (objectType == "JOB"){
            map<string, string> newobject;
            newobject["objecttype"] = "job";

            bool validinfo = true;
            string invalidinfomessage = "Invalid information JOB: ";

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
                            invalidinfomessage += "The value of the jobnumber element is not a positive integer. ";
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
                            invalidinfomessage += "The value of the pagecount element is not a positive integer. ";
                        }
                    }
                    else if (specification == "userName"){
                        newobject["userName"] = element;
                    }
                    else if (specification == "type"){
                        if (element == "bw" or element == "color" or element == "scan"){
                            newobject["type"] = element;
                        }
                        else{
                            validinfo = false;
                            invalidinfomessage += "The type of the job is not a valid option. ";
                        }
                    }
                    else if (specification == "compNumber") {
                        newobject["compNumber"] = element;
                        if (not checkStringIsPositiveInt(element)) {
                            validinfo = false;
                            invalidinfomessage += "The value of the compnumber element is not a positive integer. ";
                        }
                    }
                    else{
                        validinfo = false;
                        invalidinfomessage += "Contains unrecognizeable parameter. ";
                    }
                }
            }

            if (not newobject.count("jobNumber")){
                validinfo = false;
                invalidinfomessage += "Missing jobnumber. ";
            }
            if (not newobject.count("pageCount")){
                validinfo = false;
                invalidinfomessage += "Missing pagecount value. ";
            }
            if (not newobject.count("userName")){
                validinfo = false;
                invalidinfomessage += "Missing username. ";
            }

            if (validinfo){
                output.push_back(newobject);
            }
            else{
                outputstream << invalidinfomessage << std::endl;
            }
        }

        else if (objectType == "COMPENSATION"){
            map<string, string> newobject;
            newobject["objecttype"] = "compensation";

            bool validinfo = true;
            string invalidinfomessage = "Invalid information COMPENSATION: ";

            for (TiXmlElement *elem = object->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
                string specification = elem->Value();

                for(TiXmlNode* e = elem->FirstChild(); e != NULL; e = e->NextSibling()){
                    TiXmlText* text = e->ToText();
                    if(text == NULL)
                        continue;
                    string element = text->Value();
                    if (specification == "compNumber"){
                        newobject["compNumber"] = element;
                        if (not checkStringIsPositiveInt(element)){
                            validinfo = false;
                            invalidinfomessage += "The value of the compnumber element is not a positive integer. ";
                        }
                        else {
                            int cn = stoi(element);
                            for (unsigned int i = 0; i < previouscompnumbers.size(); i++){
                                if (cn == previouscompnumbers[i]){
                                    outputstream << "Inconsistent printing system" << std::endl;
                                    doc.Clear();
                                    return emptyoutput;
                                }
                            }
                            previouscompnumbers.push_back(cn);
                        }
                    }
                    else if (specification == "name"){
                        newobject["name"] = element;
                    }
                    else{
                        validinfo = false;
                        invalidinfomessage += "Contains unrecognizeable parameter. ";
                    }
                }
            }

            if (not newobject.count("compNumber")){
                validinfo = false;
                invalidinfomessage += "Missing compnumber. ";
            }
            if (not newobject.count("name")){
                validinfo = false;
                invalidinfomessage += "Missing name. ";
            }

            if (validinfo){
                output.push_back(newobject);
            }
            else{
                outputstream << invalidinfomessage << std::endl;
            }
        }

        else{
            outputstream << "Unrecognizable element" << std::endl;
        }
    }
    doc.Clear();
    return output;
}

/**
 * Let an XML be read in and then process the output
 * @param filename the filename of the XML
 * @param ps the system where the input needs to be sent to
 */
void XMLprocessor::implementXML(const char* filename, PrintingSystem& ps) {
    string fname = filename;
    string ftype;
    for (unsigned int i = fname.length()-4; i < fname.length(); i++){
        ftype += fname[i];
    }
    REQUIRE(ps.properlyInitialized(), "Printingsystem is not properly initialized");
    REQUIRE(properlyInitialized(), "XMLprocessor is not properly initialized");
    REQUIRE(ftype == ".xml", "Inputfile has to be an xml file");

    vector<map<string,string>> input = readXML(filename);

    for (unsigned int i = 0; i < input.size(); i++){
        map<string, string> object = input[i];
        int compensation = -1;

        if (object["objecttype"] == "device"){
            string name = object["name"];
            int cost = stoi(object["cost"]);
            int emissions = stoi(object["emissions"]);
            int speed = stoi(object["speed"]);
            string type = object["type"];

            ps.createDevice(name, emissions, speed, type, cost);
        }

        if (object["objecttype"] == "job"){
            int jobnumber = stoi(object["jobNumber"]);
            int pagecount = stoi(object["pageCount"]);
            string username = object["userName"];
            string type = object["type"];

            if (input[i].count("compNumber")){
                compensation = stoi(object["compNumber"]);
            }

            ps.createJob(jobnumber, pagecount, username, type, compensation);
        }

        if (object["objecttype"] == "compensation"){
            int compnumber = stoi(object["compNumber"]);
            string name = object["name"];

            ps.createCompensation(compnumber, name);
        }
    }
}







