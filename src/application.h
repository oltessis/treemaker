
#include "plant_architecture.h"
#include "raylib.h"


class Application
{

public:
    void initialize();
    void run(const TreeParameters& parameters);
    void shutdown();
    void simulation_step(Meristem& initial_node);

private:
    PlantArchitecture architecture;
};


void Application::initialize()
{

}


void Application::run(const TreeParameters& parameters)
{
   PlantArchitecture plant;

   Meristem step1(
      {glm::vec3(0.0f), glm::identity<glm::quat>()},
      OrganType::Leaf, 
      parameters);

  /*
  for (int step = 0; step < 1000; ++step)
  {   
      simulation_step(step1);
  }
  */

}


void Application::shutdown()
{

}


void Application::simulation_step(Meristem& initial_node)
{   
  printf("simulation_step");
  architecture.evaluate_light_field();
  //float root_carbon = architecture.evaluate_carbon(initial_node);
  architecture.evaluate_branching(initial_node);
}



