#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

class Config {
public:
	Config(string fileName);

	void clearSStream();

	void AssignAll();

	int returnInt(string key);
	bool returnBool(string key);
	double returnDouble(string key);
	float returnFloat(string key);
	string returnString(string key);

	map<string, string> cf_map;

private:
	fstream cf_fstream;
	stringstream cf_ss;
	bool fileOpen;
};

#endif
