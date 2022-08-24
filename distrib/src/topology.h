#ifndef TOPOLOGY
#define TOPOLOGY 1
#include "skeleton.h"

class Branch {

 public:
  std::vector<int> pts;

  Branch(const Edge & edge);
  Branch(const std::vector<int> & edges);
  ~Branch(){};

  
  /** contains point that is not first point */
  bool contains(int edgeIndex) const;
  
  int firstPoint() const;
  int lastPoint() const;

  /** extract this branch from point to the end of branch */
  Branch * fromPointToEnd(int point) const;

  Branch * fromStartToPoint(int point) const;

  Branch * clone() const ;

  void append(const Branch & ends);

  /** return branch distance: here : number of points */
  inline int distance(){
    return pts.size();
  }

 private:
  Branch(const Branch & src);

};


class Topology {
 public:

  // map pt -> branch
  Branch** ptToBranch;
  int nbBranches;
  Topology(Edge * edges, int nbEdges, int ptMax);
  ~Topology();
  /** merge b1 and b2 if b2.firstPoint() in b1 
   */
  void merge(Branch * b1, Branch * b2);
  
  void updatePtToBranch(Branch * b);


  /** find a branch that constains point, not as first point */
  Branch * findBranchContains(int point);


  int rank(Branch * b);
};






#endif
