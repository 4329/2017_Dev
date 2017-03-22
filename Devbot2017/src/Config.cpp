#include "Config.h"

//do error handling when file can't open
Config::Config(string fileName) {	//the constructor opens the file, assigns all of the necessary configurations, and closes the file at the end
	cf_fstream.open(fileName.c_str());

	if (cf_fstream.is_open()) {
		AssignAll();
	}
	else {
		AssignDefault();
	}

	cf_fstream.close();

	//print all map values
	cout << "Config Values: (key - value)" << endl;
	for ( map<string, string>::iterator it = cf_map.begin() ; it != cf_map.begin() ; ++it ) {
		cout << it->first << " - " << it->second << endl;
	}
}

void Config::clearSStream() {	//the stringstream becomes empty
	cf_ss.str("");
	cf_ss.clear();
}

void Config::AssignAll() {	//assigns all for the values for every subsystem
	string key;
	string value;

	while ( !cf_fstream.eof() ) {	//continue until end of file is reached
		//gets values
		string line;
		std::getline(cf_fstream, line);
		cf_ss << line;

		//sets values
		cf_ss >> key;
		cf_ss >> value;

		if (key.empty() or key == "//") {	//the config file may have something like: // arcadeDirve TankDrive or a blank line
			clearSStream();	//clears values before going to next iteration
			key = "";
			value = "";

			continue;					//this skips this line	( the key would be "//" or "")
		}

		cf_map[key] = value;	//sets value in map (make way to check if a key name is being already in the map)

		//resets stringstream and key and value variables
		clearSStream();
		key = "";
		value = "";
	}
}

void Config::AssignDefault() {
	//auto1
	cf_map["auto1::1st_timeout"] = "2.25";
	cf_map["auto1::1st_output"] = "0.6";
	cf_map["auto1::rotation"] = "60.0";
	cf_map["auto1::2nd_timeout"] = "2.5";
	cf_map["auto1::2nd_output"] = "0.3";
	cf_map["auto1::gear_place_delay"] = "0.5";

	//auto2
	cf_map["auto2::timeout"] = "4.75";
	cf_map["auto2::output"] = "0.3";
	cf_map["auto2::gear_place_delay"] = "1.0";

	//auto3
	cf_map["auto3::1st_timeout"] = "2.25";
	cf_map["auto3::1st_output"] = "0.6";
	cf_map["auto3::rotation"] = "-60.0";
	cf_map["auto3::2nd_timeout"] = "2.5";
	cf_map["auto3::2nd_output"] = "0.3";
	cf_map["auto3::gear_place_delay"] = "0.5";
}

int Config::returnInt(string key) {
	clearSStream();

	cf_ss << cf_map[key];	//gets the value from map
	int value;
	cf_ss >> value;			//string stream converts the string to the correct value

	clearSStream();

	return value;

}

bool Config::returnBool(string key) {
	clearSStream();

	cf_ss << cf_map[key];	//gets the value from map
	string value;
	cf_ss >> value;			//string stream converts the string to the correct value

	clearSStream();

	if (value == "true" or value == "True" or value == "TRUE") {
		return true;
	}
	else {
		return false;
	}

}

double Config::returnDouble(string key) {
	clearSStream();

	cf_ss << cf_map[key];	//gets the value from map
	double value;
	cf_ss >> value;			//string stream converts the string to the correct value

	clearSStream();

	return value;

}

float Config::returnFloat(string key) {
	clearSStream();

	cf_ss << cf_map[key];	//gets the value from map
	float value;
	cf_ss >> value;			//string stream converts the string to the correct value

	clearSStream();

	return value;

}

string Config::returnString(string key) {
	return cf_map[key].c_str();	//no need to convert as the map values are already strings
}
