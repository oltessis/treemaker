// variations to the environment would primarily affect the 
// leaves, like sunlight, drought, cloudiness 

#include "../meristem.h"


class Leaf {
public:
  // constructors 
  Leaf();
  ~Leaf();

  // leaf methods 

  // need some way of accumulating all leaves and comparing that to the light plane  
  // void calculate_light(); within architecture 
  float get_leaf_carbon()
  {
    return carbon_per_day;
  }

  // use this as the simplification for size 
  float leafRadius(const Leaf& leaf)
  {
      constexpr float radiusScale = 0.5f;

      return leaf.size * radiusScale;
  }
  // wind load calculations ?  


private:
  // between 0.0 - 1.0 
  float transparency = 0.3;
  // carbon per day is completely flexible, it depends on several
  // factors like hydrology and shade 
  float carbon_per_day;
  float carbon_required_for_construction;
  //Polygon leaf_shape;
  // somehow represent leaf size 
  // leaf size affects cost, transparency, carbon aquisition, 
  // spacing, etc 
  float size = 1.0;
  float canopy_level;

  //float vertices = {{ 0.0f,  0.0f},{ 0.5f,  1.0f},{ 0.0f,  2.0f},{-0.5f,  1.0f}};
  
  // potentially add hydraulic stress
  float detach_load;
  
};

/*
struct Polygon {
    std::vector<Vec2> vertices;

    // Cached geometric properties
    double area = 0.0;
    glm::Vec2 centroid{0.0, 0.0};

    // Axis-aligned bounding box
    glm::Vec2 min;
    glm::Vec2 max;
};
*/ 








