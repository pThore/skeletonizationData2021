#include "skeleton.h"
#include <sstream>
#include <iostream>
#include <string.h>
using namespace std;

Skeleton::Skeleton(const Propagation & prop) :
  propagation(prop),
  knownPoints(new bool[prop.getNumCells()])
{
  bzero(knownPoints,prop.getNumCells()*sizeof(bool));
}

Skeleton::~Skeleton(){
  delete[] knownPoints;
}

void Skeleton::followPoints(int densityThreshold){
  int * density = propagation.computeDensity();
  int nij = propagation.getNumCells();
  int* mapIndex = new int[nij];
  memset(mapIndex,-1, nij*sizeof(int));
  nbPoints = 0;

  for (int i = 0 ; i < nij; i++)
    if (density[i] >= densityThreshold)
      nbPoints++;
    
  edges = new Edge[nbPoints-1];
  coords = new int*[nbPoints];
  
  int index = 0;
  for (int i = 0 ; i < nij; i++){
    if (density[i] >= densityThreshold){
      int* coord = propagation.coord2D(i);
      coords[index++] = coord;
      mapIndex[i] = index;
    }
  }

  

  const std::vector<int> endCells = propagation.getEndCells();
  string val;
  //  cin>> val;
  int k=0;
  for(int i = 0 ; i < nij; i++){
    int startPoint =i;
    int nextPoint = propagation.parentIndex[startPoint];
    while(nextPoint != nij && nextPoint >=0 && !knownPoints[startPoint] ){
      knownPoints[startPoint] = true;
      if (density[startPoint] >= densityThreshold) {
        edges[k++] = Edge(mapIndex[startPoint], mapIndex[nextPoint]);
      }
      startPoint = nextPoint;
      nextPoint = propagation.parentIndex[startPoint];
    }
  }
  nbEdges = k;
  delete[] mapIndex;
  delete[] density;
}


