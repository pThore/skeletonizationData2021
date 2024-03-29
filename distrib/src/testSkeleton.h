#include "propagation.h"
#include "skeleton.h"
#include "topology.h"
class TestSkeleton {
 public:
  double nullValue;
  int nI;
  int nJ;
  float * property;

  void readProperty(char * file);
  void write(Skeleton& skeleton, bool withEdges);

  void write(Topology& topology);

  TestSkeleton(){};

  
  inline int getNumCells() const{
    return nI * nJ;
  }
  
  inline int getNI() const{
    return nI;
  }
  
  inline int getNJ() const{
    return nJ;
  }
  
  inline float* getProperty() const{
    return property;
  }
  inline double getNullValue() {
    return nullValue;
  }

 private:
  TestSkeleton(const TestSkeleton &src);

};
