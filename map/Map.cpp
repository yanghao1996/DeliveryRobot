#include "Map.h"
#include <fstream>
#include <vector>
using namespace std;

void Map::insertPoint(pair<int, int> point) {
	if (point.first >= -20 && point.first <= 20 &&
		point.second >= -20 && point.second <= 20) {
			
    	this->sparseMap.insert(pair<pair<int, int>, bool>(point, true));
    }
}

void Map::savePGM(string filepath) {
    fstream pgmFile;
    pgmFile.open(filepath, fstream::out);
    pgmFile << "P1" << endl
            << "201 201" << endl
            << "1" << endl;
    
    vector<vector<int> > denseMap(201, vector<int>(201, 0));
    for (auto iter = this->sparseMap.begin(); iter != this->sparseMap.end(); ++iter) {
        int xAxis = iter->first.first + 100;
        int yAxis = iter->first.second + 100;
        denseMap[xAxis][yAxis] = 1;
    }

    for (int i=0; i<denseMap.size(); ++i) {
        for (int j=0; j<denseMap[0].size(); ++j) {
            pgmFile << denseMap[i][j] << " ";
        }
        pgmFile << endl;
    }
    pgmFile.close();
}

