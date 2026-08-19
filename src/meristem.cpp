// meristem

#include "meristem.h"
#include "organs/leaf.h"
#include "organs/stem.h"



Meristem::Meristem(
    Transforms transform,
    OrganType type,
    const TreeParameters& params
)
    : transforms(transform),
      organ_type(type),
      params(params)
{
  printf("meristem made");
}


Meristem::~Meristem()
{
  printf("meristem destroyed");
}


void Meristem::make_phyllotaxis()
{

    Transforms transforms = this->transforms;
    
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

      Transforms child_transform; 

      child_transform.position = child_position; 
      child_transform.rotation = child_rotation; 
      //MeristemID = static_cast<MeristemID>(children.size());

      Meristem child(transforms, OrganType::Stem, params); 
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
    Meristem child(transforms, OrganType::Stem, params);
    child.set_parent(this);
    children.push_back(std::move(child));

}

