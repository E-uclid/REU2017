/*
  Three-vector class including mathematical operations and IO
 */
#pragma once
#include <cmath>   
#include <iostream> 
#include <fstream> 


class ThreeVec
{
 private:
  double coord_[3]; // Private data members e.g. r,t,z
  
 public:
  // Default constructor
  ThreeVec() 
    {
      for (int i=0;i<3;++i) coord_[i]=0.0;
    }
 
  // Cylindrical constructor
  ThreeVec(double r, double t, double z)
    {
      coord_[0] = r;
      coord_[1] = t;
      coord_[2] = z;
    }
  // Access function for r coordinate
  double getR()
  {
    return coord_[0];
  }
  
  // Access function for t coordinate
  double getT()
  {
    return coord_[1];
  }
  
  // Access function for z coordinate
  double getZ()
  {
    return coord_[2];
  }
  // Access function for ith coordinate
  double get(int i)
  {
    return coord_[i];
  }

  // Modifier method for r coordinate
  void setR(double value)
  {
    coord_[0] = value;
  }
  
  // Modifier method for t coordinate
  void setT(double value)
  {
    coord_[1] = value;
  }
  
  // Modifier method for z coordinate
  void setZ(double value)
  {
    coord_[2] = value;
  }
   // Modifier method for ith coordinate -> INSERT
  void set(int i, double value)
  {
    coord_[i] = value;
  }
  // Alternative modifier method for ith coordinate -> ADD
  void inc(int i, double value)
  {
    coord_[i] += value;
  }
 
  // Square the threevector
  double square()
  {
    double answer=0.0;
    for (int i=0;i<3;++i) answer+=coord_[i]*coord_[i];
    return answer;
  }
  
  // Magnitude of the threevector
  double mag()
  {
    return sqrt(square());
  }
  
  /*
    Overload the operators +,-,* and ^ to represent vector operations
  */
  // Addition
  ThreeVec operator+(ThreeVec vec)
  {
    ThreeVec ans(vec.getR() + coord_[0],
		 vec.getT() + coord_[1],
		 vec.getZ() + coord_[2]);
    return ans;
  }
  
  // Subtraction 
  ThreeVec operator-(ThreeVec vec)
  {
    ThreeVec ans(coord_[0]-vec.getR(),
		 coord_[1]-vec.getT(),
		 coord_[2]-vec.getZ());
    return ans;
  }
  
  
  // Increment
  ThreeVec operator+=(ThreeVec vec)
  {
    coord_[0] += vec.getR();
    coord_[1] += vec.getT();
    coord_[2] += vec.getZ();
    return *(this); //not necessary but returns modified ThreeVec
  }
  
  // Scalar multiplication
  ThreeVec operator*(double value)
    {
	  ThreeVec ans(coord_[0]*value,
		       coord_[1]*value,
		       coord_[2]*value);
	  return ans;
    }
  // Scalar division
  ThreeVec operator/(double value)
    {
	  ThreeVec ans(coord_[0]/value,
		       coord_[1]/value,
		       coord_[2]/value);
	  return ans;
    }
  // Vector multiplication - dot product
  double operator*(ThreeVec vec)
  {
    double ans=0.0;
    for (int i=0;i<3;++i) ans+=coord_[i]*vec.get(i);
    return ans;
  }
  
  // Vector multiplication - cross product
  ThreeVec operator^(ThreeVec vec)
  {
    ThreeVec ans(coord_[1]*vec.getZ() - coord_[2]*vec.getT(),
		 coord_[2]*vec.getR() - coord_[0]*vec.getZ(),
		 coord_[0]*vec.getT() - coord_[1]*vec.getR());
    return ans;
  }
  
  // Print to screen
  void print()
  {
    for (int i=0;i<3;++i) std::cout << coord_[i] << '\t';
    std::cout<<'\n';
  }
  
  // Print to file
  void print(std::ofstream &fout)
  {
    for (int i=0;i<3;++i) fout<< coord_[i] << '\t';
    fout<<'\n';
  }
}; 
