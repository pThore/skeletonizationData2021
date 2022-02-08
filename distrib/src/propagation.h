
#ifndef _PROPAGATION_
#define _PROPAGATION_ 1

#include <queue>
#include <vector>
#define HEADER_1 "DIM"
#define HEADER_2 "NULL_VALUE"

class Cell{
 public:
  int index;
  float value;
  Cell();
  Cell(const Cell & src);
};

class CellCompare{
 public:
  bool operator()(const Cell  & left,const Cell  & right);

};

class Propagation {
 public:
  Propagation(float * prop,double nullV, int ni, int nj, int seed_i, int seed_j);
  ~Propagation();
  double nullValue;
  int seed_i;
  int seed_j;
  int nI;
  int nJ;
  int* parentIndex;
  float * slowness;
  std::priority_queue<Cell,std::vector<Cell>,CellCompare> narrowBand;
  std::vector<int> endCells;

  int* coord2D(int index) const;
  int coord1D(int i , int j) const;
  bool coordExists(int i,int j) const;

  void readSlowness(char * file);

  std::vector<int> * neighbors(int position1D) const;

  void propagate();
  int * computeDensity() const;

  inline int getNumCells() const{
    return nI * nJ;
  }

  inline const std::vector<int> getEndCells() const{
    return endCells;
  }
 private:
  Propagation(const Propagation & src);
};






#endif
