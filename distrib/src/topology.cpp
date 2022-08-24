#include "topology.h"
#include <iostream>
#include <string.h>

using namespace std;

Branch::Branch(const Edge & edge) :
  pts()
{
  // reverse sense as skeleton create edge from leaf to source, we need the reverse order.
  pts.push_back(edge.second);
  pts.push_back(edge.first);
}

Branch::Branch(const vector<int> & edges) :
  pts(edges)
{
  if(edges.size() < 2) cerr << "Error - branch without any edges"<<endl;
}

Branch * Branch::clone() const{
  Branch * retVal = new Branch(this->pts);
  return retVal;
}




bool Branch::contains(int edgeIndex) const{
  for (int i = 1 ; i < pts.size() ; i++){
    if(pts[i] == edgeIndex) return true;
  }
  return false;
}

int Branch::firstPoint() const {
  return pts[0];
}

int Branch::lastPoint() const{
  return pts[pts.size() -1];
}


Branch * Branch::fromPointToEnd(int point) const{
  vector<int> lastPoints;
  bool findPt = false;

  for (int i=0; i < pts.size(); i++){
    int pt = pts[i];
    if(pt == point) findPt = true;
    if(findPt) lastPoints.push_back(pt);
  }

  return lastPoints.size()>1 ? new Branch(lastPoints) : 0;
}

Branch * Branch::fromStartToPoint(int point) const{
  vector<int> firstPoints;

  for (int i=0; i < pts.size(); i++){
    int pt = pts[i];
    firstPoints.push_back(pt);
    if(pt == point) break;

  }

  return firstPoints.size()>1 ? new Branch(firstPoints) : 0;
}

void Branch::append(const Branch & ends){
  if(this->lastPoint() != ends.firstPoint()){
    cerr << "error - mismatch in Branch::appends" << endl;
    return;
  }

  for (int i = 1 ; i < ends.pts.size() ; i++){
    pts.push_back(ends.pts[i]);
  }

}

Topology::~Topology(){

  for (int i = 0 ; i < nbBranches; i++){
    Branch * b = ptToBranch[i];
    if(b != 0){
      for (int j=0; j < b->pts.size(); j++){
	int index = b->pts[j];
	ptToBranch[index] = 0;
      }
      delete b;
    }
  }
  delete[] ptToBranch;
}

void Topology::merge(Branch * b1, Branch * b2){
  if(b1 == b2 || b1 == 0 || b2 == 0) return ;
  if(b1->distance() == 1) cerr << "error merge" << endl;

  int pt = b2->firstPoint();
  if(pt == b1->lastPoint()){
    b1->append(*b2);
    updatePtToBranch(b1);
    Branch * father = ptToBranch[b1->firstPoint()];
    delete b2;
    if(father !=0) merge(father,b1);
    return ;
  }

  Branch * b3 = b1->fromStartToPoint(pt);
  b3->append(*b2);
  if(b1->distance() >= b3->distance()){
    delete b3;
    return ; // no changes
  }				       

  Branch *b4 = b1->fromPointToEnd(pt);
  if(b4->distance() == 1) cerr << "error merge" << endl;
  updatePtToBranch(b3);
  updatePtToBranch(b4);
  delete b1;
  delete b2;
  Branch * father = ptToBranch[b3->firstPoint()];
  merge(father,b3);
  return ;
}

void Topology::updatePtToBranch(Branch *b){
  if(ptToBranch[b->firstPoint()] == 0){
    // first point can be a common point with other roads.
    ptToBranch[b->firstPoint()] = b;
  }
  for (int i = 1 ; i < b->pts.size(); i++){
    int pt = b->pts[i];
    ptToBranch[pt] = b;
  }
}

int Topology::rank(Branch * b){
  int r = 0; 

  while(b != 0){
    r++;
    Branch * b2 = ptToBranch[b->firstPoint()];
    if(b == b2) break;
    b=b2;
  }
  return r;
}

Topology::Topology(Edge * edges, int nbEdges, int ptMax){
  nbBranches = ptMax+1;
  ptToBranch = new Branch*[nbBranches];

  // memset(ptToBranch,0,nbBranches);
  // same, for valgrind check
  for (int i = 0 ; i < nbBranches; i++){
    ptToBranch[i] = 0;
  }

  for (int i = 0 ; i < nbEdges; i++){
    Branch * b1 = new Branch(edges[i]);
    
    Branch * b2 = ptToBranch[b1->lastPoint()];
    if(b2 != 0){
      b1->append(*b2);
      delete b2;
    }


    Branch * father = ptToBranch[b1->firstPoint()];

    updatePtToBranch(b1);

    merge(father, b1);

  }

}
