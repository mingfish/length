//
//  main.cpp
//  Length
//
//  Created by rjwwq1991@sina.com on 13-8-4.
//  Copyright (c) 2013年 rjwwq1991@sina.com. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

void readDataIntoVectors(vector<string> &tmpRulesVec, vector<string> &tmpPolysVec);
void convertRulesIntoMap(map<string, double> &tmpRulesMap, vector<string> &tmpRulesVec);
void calculatePolys(map<string, double> &tmpRulesMap,vector<string> &tmpPolysVec, vector<double> &tmpResults);
void writeResultsIntoFile(vector<double> &tmpResults);

int main(int argc, const char * argv[])
{
  //read data into vectors
	vector<string> rulesVec; //vector for Conversion Rules
	vector<string> polysVec; //vector for Polynomial
	readDataIntoVectors(rulesVec, polysVec);

	map<string, double> rulesMap;
	convertRulesIntoMap(rulesMap, rulesVec);

	vector<double> results;
	calculatePolys(rulesMap, polysVec, results);

	writeResultsIntoFile(results);

	return 0;
}

void readDataIntoVectors(vector<string> &tmpRulesVec, vector<string> &tmpPolysVec)
{
	string tmpLine;
	ifstream inStream;
	inStream.open("input.txt", ios::in);

	if (!inStream) {
		cerr << "can not open input file " << endl;
		exit(1);
	}

	bool rulesDataFinish = false; //Reading Data of Conversion Rules has finished

	while (!getline(inStream, tmpLine).eof())
	{
		printf("%s\n", tmpLine.c_str());

		if (tmpLine.length() == 0)
		{
			rulesDataFinish = true;
			getline(inStream, tmpLine);
		}

		if (!rulesDataFinish)
		{
			tmpRulesVec.push_back(tmpLine);
		}
		else
		{
			tmpPolysVec.push_back(tmpLine);
		}
	}
	tmpPolysVec.push_back(tmpLine);
	inStream.close();
}

void convertRulesIntoMap(map<string, double> &tmpRulesMap, vector<string> &tmpRulesVec)
{
	for (vector<string>::iterator it = tmpRulesVec.begin(); it != tmpRulesVec.end(); ++it)
	{
		stringstream ssRules(*it);
		string tmpWord;

		vector<string> wordsInRule;
		while (ssRules >> tmpWord)
		{
			wordsInRule.push_back(tmpWord);	
		}
		tmpRulesMap[wordsInRule[1]] = atof(wordsInRule[3].c_str());
		tmpRulesMap[wordsInRule[1]+"s"] = atof(wordsInRule[3].c_str());
		tmpRulesMap[wordsInRule[1]+"es"] = atof(wordsInRule[3].c_str());

		string tmpSubStr("oo");
		string::size_type pos = wordsInRule[1].find(tmpSubStr);
		if (std::string::npos != pos)
		{
			wordsInRule[1].replace(pos,tmpSubStr.length(),"ee");
			tmpRulesMap[wordsInRule[1]] = atof(wordsInRule[3].c_str());
		}
	}
}

void calculatePolys(map<string, double> &tmpRulesMap,vector<string> &tmpPolysVec, vector<double> &tmpResults)
{
	for (vector<string>::iterator it = tmpPolysVec.begin(); it != tmpPolysVec.end(); ++it)
	{
		stringstream ssPolys(*it);
		string tmpWord;

		vector<string> wordsInPolys;
		while (ssPolys >> tmpWord)
		{
			wordsInPolys.push_back(tmpWord);	
		}


		for(vector<string>::iterator wordIter = wordsInPolys.begin(); wordIter != wordsInPolys.end(); ++wordIter)
		{
			map<string, double>::iterator mapIter = tmpRulesMap.find(*wordIter);
			if(mapIter != tmpRulesMap.end())
			{
				double value = (mapIter->second) * (atof((*(wordIter-1)).c_str()));

				std::ostringstream strs;
				strs << value;
				*(wordIter-1) = strs.str();
			}
		}

		for(vector<string>::iterator wordIter = wordsInPolys.begin(); wordIter != wordsInPolys.end(); ++wordIter)
		{

			if ((*wordIter).compare("+")==0)
			{
				double value = (atof(wordsInPolys[0].c_str())) + (atof((*(wordIter+1)).c_str()));

				std::ostringstream strs;
				strs << value;
				wordsInPolys[0] = strs.str();
			}
			else if((*wordIter).compare("-")==0)
			{
				double value = (atof(wordsInPolys[0].c_str())) - (atof((*(wordIter+1)).c_str()));

				std::ostringstream strs;
				strs << value;
				wordsInPolys[0] = strs.str();
			}
		}

		tmpResults.push_back(atof(wordsInPolys[0].c_str()));
	}
}

void writeResultsIntoFile(vector<double> &tmpResults)
{
	ofstream outStream;
	outStream.open ("output.txt",ios::out);

	if (!outStream) {
		cerr << "can not open output file " << endl;
		exit(1);
	}

	outStream << "rjwwq1991@sina.com" << endl << endl;

	for (vector<double>::iterator it = tmpResults.begin(); it != tmpResults.end(); ++it)
	{
		outStream << std::fixed << std::setprecision(2) << *it << " m" <<endl;
	}

	outStream.close();
}
