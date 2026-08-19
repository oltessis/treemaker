// this is modelled as just a cylinder made of wood 
// with infailable boundary conditons 
// all stems are apical meristem and will continue to 
// produce stems unless the carbon budget is too low 


#include "../meristem.h"


class Stem {
public:
  Stem();
  ~Stem();

  // treat this as a black rectangle that blocks out the sun 
  // depending on its projection to the sun axis 
  float get_sunlight_rectangle();
  // take its projection relative to the wind plane, perhaps allow for blocking 
  // like with light 
  float get_weight(); 
  // calculates carbon required this turn 
  float get_carbon_required();

  // globally calculate factors 
  float max_experienced_bending;
  float max_expreienced_axial;
  // this is basically gravity but enhanced 
  float get_wind_load();
  float get_local_excess(float carbon){
    // everything in the graph above me - me 
    float remaining_carbon = maintenance_carbon - carbon;
    return remaining_carbon;
  }
  float diameter_increase;
  float diameter;
  float length;
  // this is very important for constructing the optimization value fields  
  float local_excess;
  // computed from previous turn 
  float local_excess_gain_gradient;
  float local_excess_loss_gradient;

  //std::vector<float> local_excess_throughout_time;
  
  // permiability is the ease at which liquids move through the 
  // cylinder this could potentially affect locality 



  // potentially other value fields could be included
  // breaks abstraction 
  //float photosynthesis;
  //float maintenance;
  //float hydraulic_cost;
  //float construction_cost;
  //float mechanical_cost;


  float safety_factor;


private:
  // geometry 

  // based off of the physical dimensions of the stem 
  float weight;
  float bend_strength;
  // model trunk thickening 
  float axial_loading;
  float maintenance_carbon; 
  // need some way of figuring out buckling 

  glm::vec3 position;

};


// this gets passed to the stem from architecture 
/*
struct Wood {
    float specific_gravity;
    float carbon_cost;
    float modulus_of_rupture;
    float compression_strength;
    float tensile_strength;
    float bending_strength;
};
*/ 


/*
float get_carbon_required()
{
  // calculate current diameter max bending stress 
  // compare to the max experienced variable 
  // work equations back to get new diameter 
  float bending_diameter =
      current_diameter *
      std::cbrt(max_bending_stress / allowable_bending);

  float axial_diameter =
      current_diameter *
      std::sqrt(max_axial_stress / allowable_axial);

  float required_diameter =
      std::max(bending_diameter, axial_diameter);


  float additional_volume(
      float old_diameter,
      float new_diameter,
      float length)
  {
      return (M_PI * length / 4.0f) *
            (new_diameter * new_diameter -
              old_diameter * old_diameter);
  }

  float dV = additional_volume(0.20f, 0.22f, 10.0f);
}


// potential wood properties 
// maybe even include an engineering-level one that 
// modifies things like cell wall thickness and traechids 

 * struct WoodGenetics {
    float density;
    float modulus;
    float bending_strength;
    float compression_strength;

    float carbon_per_volume;

    float cambial_growth_rate;
    float secondary_wall_investment;

    float vessel_conductivity;
    float heartwood_rate;
};
*/ 


// later it might be a good idea to add other materials 
/*
density
tensile_strength
compressive_strength
Youngs_modulus
shear_strength
fracture_toughness
fatigue_resistance
*/ 










