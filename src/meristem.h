// meristem 
// meristem can be thought of as a ball with a vector  
// and thousands of these will be placed in the tree  
// this is the fundemental unit 
// whorls can be represented by a special collection class of these  
// array made of linked lists with each having a unique head  O(V) + N 
// this is responsible for simulation and scoring not connection, 
// architecture affect connections, geometry and scoring is here  
// where are transforms imposed?, somehow via phyllotaxis 
// when calculating global fields is needed like for momments specialized fields do that 
// all that meristem needs to know about a branch is the carbon consumed by said branch 
// it says how viable is it for me to branch and larger systems take care of the rest  
// meristem does not simulate anything 
// responsible for organizing architecture

#pragma once

#include <cstdint>
#include <limits>
#include <vector>

#include <cstdio>
#include "parameters.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


enum class OrganType {
  Leaf, 
  Stem 
};


struct Transforms 
{
  glm::vec3 position; 
  glm::quat rotation; 
};


class Meristem {

  public:
   
    Meristem(
        Transforms transform,
        OrganType type,
        const TreeParameters& params
    );
    ~Meristem();

    using MeristemID = uint32_t; 
    static constexpr MeristemID INVALID_MERISTEM = std::numeric_limits<MeristemID>::max();

    void set_parent(Meristem* p)
    {
        parent = p;
    }

    std::vector<Meristem>& get_children()
    {
        return children;
    }

    const std::vector<Meristem>& get_children() const
    {
        return children;
    }

    OrganType get_organ_type() const
    {
        return organ_type;
    }

    float get_carbon_balance() const 
    {
      return carbon_balance;
    }

    void set_carbon_balance(float carbon) 
    {
      carbon_balance = carbon;
    }

    void make_phyllotaxis();

    bool get_is_active();
    char get_type();
    
    // here all the calculations will be performed and a normalized_score 
    // will be passed to the architecture for branch decisions 
    // perhaps subclass will return the normalized_score because only it knows its exact variables 
    float normalized_score();

    Transforms transforms;
    // if thresholds no longer work out the node can be pruned, set to false 
    // senesce means go dormant prune means remove, for later trunk optimization prune could be used 
    void prune();
    void senesce();
    bool is_apical;
    float branching_threshold;
    
    // if a leaf has taken a certain threshold of carbon create branching, ideally find a way to not cause branching 
    // to its neighbours

  protected: 
    Meristem* parent = nullptr; 
    std::vector<Meristem> children;
    const TreeParameters& params; 

  private:
    // not included in constructor because i dont know why you would create dead meristem
    bool is_active;
    OrganType organ_type;
    float carbon_balance;
    // if the meristem is apical that could be a huge 
    // weight in its favor 
    //uint8_t growth_cycle_number;
    //float hydraulic_factor;
    
    // keep track of node position 
    //MeristemID id; 
    //MeristemID parent;
    //char prev_branch;
    //std::vector<Meristem> children;

};





    // constantly read nodes for sunlight 
    // if above a sunlight threshold keep producing  
    // below terminate, have a ratio of phyllotaxis deployed  
    // vs sunlight received, something like a maintence cost 
    // wood could come into this maintence cost, there could be a 
    // set carbon cost for wood and mechanical properties could come from that 
    // branch size is determined by this, photosynthesis affects carbon  
    // how does wood hardness affect the distance between buds on the phyllotaxis? 
    // a tree that does not need to extend too much but rather to live a long time 
    // prefers harder wood 
    // you could make the phyllotaxis have a set diameter with diameter and wood type affecting 
    // growth speed, maintanence is the radial growth, mechanical loading like compression resistance can also affect this  
    // euler buckling somehow 
    // the size of the sam affects the intial size of the tree 
    // 1kg of wood takes about 1.83kg of co2 from the atmosphere 
    // one leaf produces about 0.1g-0.5g co2 absorbed per day 







