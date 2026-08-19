// lsystem_architecture
// l-systems might not be needed, only meristems evaluating light    
//  allometry could be mainly a resource allocator and not just models  
// make properties as emergent as possible 
// you have a leaf, leaf produces carbon, part of the carbon is
// sunk into the structure, the structure need support 
// this could be responsible for the large trie data structure 
// there needs to be somesort of ambient carbon storage for dormant leaves 
// there could be the abstraction that this can maintain global carbon excess 

// this is really the branch decision engine, where all the variables are 
// compared and decisions of whether to branch are evaluated, a trie is appended if 
// decisions are greenlit 

// you could make this probabilistic with maybe specific_gravity 
// and a strength modifier applied and they can be added in a probabilistic way 
// this could behave in a clocklike fashion with a decide --> calculate --> update loop 
// if two branches were simmilar enough like having a bunch of fine branches in the trunk would 
// there be a method of combining these to simplify things, and maybe gradually decresing 
// the density of whorls accordingly, perhaps the density of whorls could have an effect of 
// removing SAM nodes 
// this is everything at a high level, the interface for all 

// here the units are metric 

#pragma once 
#define GLM_ENABLE_EXPERIMENTAL


#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "meristem.h"


// know leaf size at compile time 
constexpr int LEAF_SIZE = 100;


struct CanopyGrid {
  std::array<std::array<std::array<bool, LEAF_SIZE>, LEAF_SIZE>, LEAF_SIZE> cells{}; 
  
  float cellSize; 
  int width; 
  int height;

  bool& at(int x, int y, int z){
    return cells[x][y][z];
  }

};


struct Weights {
    float weight;
    glm::vec3 position;
};




class PlantArchitecture {
public:
  // constructors 
  PlantArchitecture();
  ~PlantArchitecture();
  //PlantArchitecture(PlantArchitecture &&) = default;
  //PlantArchitecture(const PlantArchitecture &) = default;
  //PlantArchitecture &operator=(PlantArchitecture &&) = default;
  //PlantArchitecture &operator=(const PlantArchitecture &) = default;
  
  // store all leaves in an index for fast access 
  // a packed bitset could potentially be very efficient 
  std::vector<Meristem> leaves; 
  
  int whorl_count;
  
  // the main simulations you would perform would be 
  // here order matters 
  //void evaluate_hydraulics(); 
   //void evaluate_mechanical_stability();
  void evaluate_light_field();
  float evaluate_carbon(Meristem& node);
  void evaluate_branching(Meristem& node);
  // carbon budget tells you what to add to and remove 
  // optional 
  //void evaluate_wind_load();
  
  // dummy small step would be to give a fixed carbon budget 
  // each round, create branch is probably the first thing to 
  // test 
  void create_branch(Meristem& node);
  // for later 
  //void evaluate_buttress_roots();
  
  // maybe for testing purposes make a dummy tree 

  // for later simplifying and optimizing trunks and large branches  
  //void meristem_cull();
  
  void simulation_step(Meristem& node);
  
  void render();


private:
   

};


