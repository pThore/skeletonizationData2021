#ifndef SKELETON_H
#define SKELETON_H


#include "propagation.h"
class Edge {
public:
  int first;
  int second;
  Edge(int f, int s) {
    first = f;
    second = s;
  }
  Edge() {
    first = 0;
    second = 0;
  }
};

class Skeleton {
  const Propagation & propagation;
  bool * knownPoints;
  Edge * edges;
  int ** coords;
  int nbPoints;
 public:
  Skeleton(const Propagation& propagation);
  ~Skeleton();

  void followPoints(int dentityThreshold);
  inline int getNbPoints() const{
    return nbPoints;
  }
  inline int** getCoords() {
    return coords;
  }
  inline Edge* getEdges() {
    return edges;
  }
 private:
  Skeleton(const Skeleton& propagation);


};




#endif
