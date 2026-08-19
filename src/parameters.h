
// parameters header 

#pragma once

struct WoodProperties {
    float specific_gravity;
    // eventually calculate carbon cost off of specific gravity
    // this is a complex calculation 
    float carbon_cost_m3;
    float modulus_of_rupture_Pa;
    float compression_strength_Pa;
};


struct PhyllotaxisVariables {
    float internode_length_m; 
    float node_rotation_deg; 
    uint32_t meristems_per_node; 
    float branch_angle_deg; 
};


struct TreeParameters {
  WoodProperties wood; 
  PhyllotaxisVariables phyllotaxis; 
};


