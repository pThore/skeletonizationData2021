#include "testSkeleton.h"
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;

void TestSkeleton::readProperty(char * property_file){
  ifstream infile(property_file);
  
  // read header
  string line ;
  getline( infile,line);
  istringstream splitter (line);
  
  splitter >> nI;
  splitter >> nJ;
  splitter >> nullValue;
  
  property = new float[nI * nJ];
  
  
  // read array
  int index = 0;
  float value;
  while(infile >> value){
    property[index++] = value;
  }
  if(index != nI*nJ) {
    cerr << "wrong file "<< property_file << " read " << index << " lines " << " instead of " << nI*nJ <<  endl;
    exit(0);
  }
  if(getenv("DEBUG")) {
    cerr<< "read " << property_file << " ni "<< nI << " nj " << nJ << " nullValue " << nullValue << endl;
  }
}

void TestSkeleton::write(Skeleton & skeleton) {
  int index = 1;
  for (int p=0; p<skeleton.getNbPoints(); p++) {
    cout << index++ << " " << skeleton.getCoords()[p][0] << " "<< skeleton.getCoords()[p][1]<< endl;
  }
  cout << "SEGMENT"<<endl;
  for (int e=0; e<skeleton.getNbPoints()-1; e++) {
    cout << skeleton.getEdges()[e].first << " " << skeleton.getEdges()[e].second <<endl;
  }
}





int main(int c, char* argv[]){
  
  if(c < 3){
    cerr << "Usage: testSkeleton grid_file threshold [seed] >  outputFile" << endl;
    cerr << "seed [optional] with format 'i,j'" << endl;
    cerr << "example: testSkeleton ../data/input/DTMap.prop 50 2,2 > ../data/output/skeleton.skel" << endl;
    exit(0);
  }
  int seed_i=2;
  int seed_j=2;
  
  if(c == 4){
    istringstream splitter (argv[3]);
    string token;
    getline(splitter,token,',');
    seed_i = atoi(token.c_str());
    getline(splitter,token);
    seed_j = atoi(token.c_str());
  }
  {
    if(getenv("DEBUG")) {
      cerr << "parameters seed i " << seed_i << " j " << seed_j << endl;
    }
    
    TestSkeleton reader;
    reader.readProperty(argv[1]);
    Propagation prop(reader.getProperty(), reader.getNullValue(),  reader.getNI(), reader.getNJ(), seed_i, seed_j);
    prop.propagate();
    
    Skeleton skeleton (prop);
    skeleton.followPoints(atoi(argv[2]));
    reader.write(skeleton);
  }
  exit(1);
}
