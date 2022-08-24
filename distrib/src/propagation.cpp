#include "propagation.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include <string.h>
#include <memory>
#include <math.h>

using namespace std;

#define nbBorderPoint  4
int  border[nbBorderPoint][2] = { { -1,0}, {1,0}, {0,1}, {0,-1 } };
int countCells = 0;
bool CellCompare::operator()(const Cell & left,const  Cell & right){
  // reverse order: first value of queue is largest one.
  return left.value < right.value;
}

Cell::Cell(){
}

Cell::Cell(const Cell & src) :
  index(src.index),
  value(src.value){
}

Propagation::Propagation(float * prop,double nullV, int ni, int nj, int _seed_i, int _seed_j)
  : nullValue(nullV),
    seed_i(_seed_i),
    seed_j(_seed_j),
    nI(ni),
    nJ(nj),
    parentIndex(NULL),
    slowness(prop),
    narrowBand(),
    endCells()
{

  parentIndex=new int[nI * nJ];
  memset(parentIndex,-1,nI*nJ*sizeof(int));
  Cell cell;
  cell.index= coord1D(seed_i , seed_j);
  parentIndex[cell.index] = nI*nJ;
  narrowBand.push(cell);
}

Propagation::~Propagation(){
  delete[] parentIndex;
  delete[] slowness;
}



int * Propagation::coord2D(int index) const{
  int* out = new int[2];
  out[0] = index / nI;
  out[1] = index % nI;
  return out;
}


int Propagation::coord1D(int i,int j) const{
  return i * nI + j ;
}

bool Propagation::coordExists(int i,int j) const{
  return i >=0 && j >= 0 && i < nI && j < nJ;
}

vector<int> * Propagation::neighbors(int position1D) const{
  vector<int>* retVal = new vector<int>();

  int* coord= coord2D(position1D);
  for(int u = 0 ; u < nbBorderPoint ; u++){
    int* delta = border[u];
    int i = delta[0] + coord[0];
    int j =  delta[1] + coord[1];
    int pos2D = coord1D(i,j);
    if (coordExists(i,j) && parentIndex[pos2D] < 0 && slowness[pos2D] != nullValue){
      retVal->push_back(pos2D);
    }
  }
  delete[] coord;
  return retVal;
}

void Propagation::propagate(){

  while(! narrowBand.empty()){
    countCells++;
    int pos1D = narrowBand.top().index;
    narrowBand.pop();
    auto_ptr<vector<int> > voisins(neighbors(pos1D) );
    if(voisins->empty()){
      endCells.push_back(pos1D);
    }
    for (int i = 0 ; i < voisins->size(); i++){
      int index = (*voisins)[i];
      parentIndex[index] = pos1D;
      Cell cell;
      cell.index = index;
      cell.value = slowness[index];
      narrowBand.push(cell);
    }
    
  }
}

int * Propagation::computeDensity() const{
  int * density = new int[nI * nJ];
  bzero(density, nI*nJ*sizeof(int));
  for (int i = 0 ; i < nI*nJ ; i++){
    int parent = parentIndex[i];
    while(parent >= 0 && parent != nI * nJ){
      density[parent]++;
      parent = parentIndex[parent];
    }
  }
  return density;

}
