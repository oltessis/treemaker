// phyllotaxis
// this pretty much controls all geometry  
// architecture just controls graphs and relationships 
// collision avoidance somehow? 
// pruning on mature forms can be caused by setting an  
// established meristem to false which would delete all childs  
// the phyllotaxis runs indefinitely with no set length 
// for annuals everything SAM produces is a leaf, after a year they can branch  
// chance events of branching can happen near the SAM if conditions are favorable  
// the number of whorls a phyllotaxis makes is not fixed in a season, it is based off of productivity 
// make it continuous not discrete, its job is to intantiate meristem objects 
// phyllotaxis is almost entirely geometric 
// meristem owns this 
// orientation is z-up
// this is meristems create more method

/*
class Phyllotaxis : public Meristem
{

  public:
    
    // create a phyllotaxis of variable activity 
    Phyllotaxis();
    ~Phyllotaxis();


    // environmental 
    // an interesting one would be to calculate total leaf are with interception above 
    // perhaps convert the entire phyllotaxis into a plane of its geometry vs the light 
    // direction plane and a method in architecture could stack those up based off of position 
    // to determine such a thing 
    // potential variable could be leaf transparency as a leaf does not intercept 100% of the light  
    // type autos to leaf when first instantiated 
    
    //Meristem(vec3 transforms, char type);
    
    void make_phyllotaxis();
    float get_axial_growth_rate(float target_diameter ,Wood wood_type) const;
    //float get_carbon_per_length() const;

  private:
    
    // making the spacing based off of timing means that environment can 
    // affect spacing, like how a pine tree grown in a cliff basically becomes a bonsai 
    float axial_growth_rate; 
    float angle_between_whorls;
    int num_meristem_per_whorl; 
    float target_diameter;
    float carbon_cost;
    float carbon_per_length; 
    const TreeParameters params; 
};  


 
float Phyllotaxis::get_axial_growth_rate(float target_diameter ) const
{
  //return carbon_available / carbon_per_length;
  return 1.0f;
}


float get_carbon_per_length() const
{
  float cross_sectional_area = M_PI * 0.25f * target_diameter * target_diameter; 
  return cross_sectional_area * wood_density * carbon_per_mass; 
}


// this is for side meristem, for this model there are no 
// apical leaves, all leaves are side meristem leaves 
// this is implicit it acts upon the current meristem
// this makes a ranchis 
void Phyllotaxis::make_phyllotaxis()
{

    Transform transforms = this->transforms;
    
    // get angles 
    const uint32_t meristems_per_node = 
      params.phyllotaxis.meristems_per_node; 

    const float whorl_angle = 
      glm::radians(360.0 / meristems_per_node);
   
    const float branch_angle = 
      glm::radians(params.phyllotaxis.branch_angle_deg); 

    const float internode_length = 
      params.phyllotaxis.internode_length_m;
 
    glm::vec3 parent_position = this->transforms.position; 
    glm::quat parent_rotation = this->transforms.rotation;

    // set rotations 
    for(uint32_t i = 0; i < meristems_per_node; ++i) 
    {
      float azimuth = i * whorl_angle; 
      
      // stem rotation 
      glm::quat whorl_rotation = glm::angleAxis(azimuth, glm::vec3(0.0f, 0.0f, 1.0f));

      glm::quat branch_rotation = glm::angleAxis(branch_angle, glm::vec3(1.0f, 0.0f, 0.0f));

      glm::quat local_rotation = whorl_rotation * branch_rotation;

      glm::vec3 local_offset(0.0f, 0.0f, internode_length); 

      glm::vec3 child_position = 
        parent_position + 
        parent_rotation * local_offset;

      glm::quat child_rotation = 
        parent_rotation * local_rotation;

      Transform child_transform; 

      child_transform.position = child_position; 
      child_transform.rotation = child_rotation; 
      //MeristemID = static_cast<MeristemID>(children.size());

      Meristem child(transforms, OrganType::Leaf); 
      child.set_parent(this);
      children.push_back(std::move(child));

      //leaves.push_back(child);
    }
 
    // for the meristem branch 
    glm::quat stem_rotation = glm::angleAxis(
        glm::radians(params.phyllotaxis.node_rotation_deg),
        glm::vec3(0.0f, 0.0f, 1.0f));
         
    transforms.rotation = this->transforms.rotation * stem_rotation; 

    // adjust the transforms 
    glm::vec3 local_offset(0.0f, 0.0f, internode_length);

    transforms.position = 
      this->transforms.position + 
      this->transforms.rotation * 
      local_offset;

    // make a stem
    Meristem child(transforms, OrganType::Stem); 
    child.set_parent(this);
    children.push_back(std::move(child));

}


// might not be needed 
enum class BranchKey : uint8_t
{
    A = 0,
    B = 1,
    C = 2,
    D = 3, 
    E = 4, 
    F = 5, 
    G = 6, 
    H = 7, 
    I = 8, 
    J = 9, 
    K = 10, 
    L = 11, 
    M = 12, 
    N = 13, 
    O = 14, 
    P = 15, 
    Q = 16, 
    R = 17, 
    S = 18, 
    T = 19, 
    U = 20, 
    V = 21, 
    W = 22, 
    x = 23, 
    y = 24,
    Z = 25
};
*/





