// lsystem_architecture

#include "plant_architecture.h"
#include "meristem.h"




PlantArchitecture::PlantArchitecture()
{
  printf("plant_architecture created");
}


PlantArchitecture::~PlantArchitecture()
{

}


void PlantArchitecture::simulation_step(Meristem& node)
{
  
}


/*
void PlantArchitecture::evaluate_hydraulics(Meristem meristem)
{
  Meristem& current = meristems[meristem];

  float total_length;

  Meristem child = current.next; 

  while(child != INVALID_NODE)
  {
    walk_tree(child);
    
    child.hydraulic_factor = something * total_length; 

    child = nodes[child].next;
  }

   
}
*/


// here you construct a canopy density map 
// geometry in, sunlight efficiency out for every leaf 
// represent leaves as points 
// iterate through the leaf vector and if a leaf is in a 
// higher z position than another bump it down 1 
// this is found by checking if that position of the grid is 
// true, if it is true bump it, this could be as simple as 
// grid[x][y], and iteratively grid[x][y] until you hit false 
// 1 represents the maximum light 
// keep true / false on the grid and the level variable 
// in the leaf to keep track of things
// attenuation is derrived from level 
// make grid size an effect of resolution, larger leaves means 
// coarser resolution, leaf size calculates resolution
// make the received light proportional to grid size 
// return the level of every leaf, this can be set 
// in the comparison / instantiation phase 
// need to adjust size to maximum tree size and must pay 
// attention to tree dimensions for leaf size relative to 
// transform coordinate system
// need somesort of minimum distance between leaves 
// this gets values for leaves the other get values for carbon 
void PlantArchitecture::evaluate_light_field()
{
  printf("evaluate light field called");

  CanopyGrid grid; 

  grid.at(5,5,5);
  // create a ordered vector of greatest to least   
  std::vector<int> order(leaves.size());

  for (int i=0; i<leaves.size(); ++i) 
    order[i] = i;
  
  std::sort(order.begin(), order.end(), [&](int a, int b)
        {
          return leaves[a].transforms.position.z > leaves[b].transforms.position.z;
        }
      );


  // iterate through all members  
  for(Meristem& leaf : leaves)
  {
    // seek out the first available level 
    int x = static_cast<int>(
      std::floor(leaf.transforms.position.x / grid.cellSize)
    );

    int y = static_cast<int>(
      std::floor(leaf.transforms.position.y / grid.cellSize)
    );
  
    // check if horizontal is an invalid position
    if (x < 0 || x >= grid.width || y < 0 || y >= grid.height)
    {
        return;
    }

    
    int level = 0;

    while (
        level < grid.height &&
        grid.at(x, y, level) 
    )
    {
        ++level;
    }

    // this would be so far down i dont know why it would not be pruned 
    if(level >= grid.height)
    {
      return; 
    }

    grid.at(x, y, level) = true; 

    leaf.transforms.position.z = level;

  }
}

/*
void PlantArchitecture::evaluate_mechanical_stability()
{
  Meristem& current = meristems[meristem];

  float total_length;

  Meristem child = current.next; 

  while(child != INVALID_NODE)
  {
    walk_tree(child);
    
    // make a tree of weights and sum them up, check structural elements 
    // relative to this tree
    weights.weight = child.weight;
    weights.position = child.transform;
    
    //momments can be determined via 

    for (NodeID child : children(node))
    {
        Vec3 r = nodes[child].position -
                 nodes[node].position;

        nodes[node].force += nodes[child].force;

        nodes[node].moment +=
            nodes[child].moment +
            cross(r, nodes[child].force);
    }

    // axial forces could be found like this 
    Vec3 F = accumulated_force;
    Vec3 axis = branch.axis;

    float N = dot(F, axis);

    Vec3 F_axial = N * axis;
    Vec3 F_lateral = F - F_axial;

}

    child = nodes[child].next;
  }


}
*/


// what does carbon look like for every leaf load path 
// in the model, trace the path from each leaf down every branch 
// evenly pooling the leaves at every branch 
// determine what every leaf individually contributes to the tree
// START 
// start the program with a simple carbon budget of income - construction - maintenance

// use post order traversal 
// add to the sum when you hit a leaf and subtract from  
// the sum when you hit a branch, or keep massive sums 
// for each branch and leaf and only do calculations once 
// traversal is finished, in a pooled kind of fashion 
// Accumulate carbon / maintenance / whatever
// call this from the root 

float PlantArchitecture::evaluate_carbon(Meristem& node)
{
  printf("evaluate_carbon called");

  float total = 0.0f; 
  
  // at every node exhaust every child first
  for (Meristem& child : node.get_children())
  {
    total += evaluate_carbon(child);
  }

  // once every child is exhausted, 
  // evaluate this node 
  if (node.get_organ_type() == OrganType::Leaf)
  {
    total += node.get_carbon_balance(); 
  }

  total -= node.get_carbon_balance();
  
  node.set_carbon_balance(total); 

  return total;  
}

/*
if (node.organ_type == OrganType::Leaf)
{
    carbon = node.carbon_produced;
}
else if (node.organ_type == OrganType::Stem)
{
    for (Meristem& child : node.children)
    {
        carbon += evaluate_carbon(child);
    }

    carbon -= node.maintenance_cost;
}
*/

// branching 
  // have a probability of a random branch near the SAM to produce  
  // older phyllotaxis could possibly produce epicormic shoots  
  // contribute a thickening of the diameter as a response 
  // if a branch has enough carbon it can continue to apex 
  // if all leaves on a branch are equal do it randomly
  // for a branch there could be a mechanism for having the 
  // number of branches produced to be based off of carbon abundance 
  // otherwise do the most productive leaf if it passes a threshold 
  // carbon goes through a safety factor 
  // hydraulics light field and that just affect carbon everything 
  // is the carbon budget 
  // need a way to evaluate damage and damage based branching 
  // perhaps there is a fixed excess, like x excess after said turn  
  // also factor in the cost for new construction 
  // an excess based model with tunable parameters could make 
  // sense, carbon surplus could have locality with local areas  
  // spending locally 
  // you could even have a fixed excess where it tries to maintain a 
  // fixed excess, where only after a fixed excess can it branch 
  // the fixed excess could even be proportional, a fixed excess 
  // could tell the branch whether or not to branch if over the 
  // fixed excess branch, if under do not, carbon surplus might 
  // be the best mechanism
  // with each meristem having a single float, value gradients could be found 
  // you could progressively follow the most profitable branches, progressively follow C 
  // follow gradients, capture values in time, look for increases in the gradient 
  // it might be possible to calculate change of carbon if a decision is made before making it 
  // you could have a locality parameter, carbon cannot travel
  // for free parameter(num hops) could affect it, dispoportionate vertical  
  // locallity is more natural 



  // construction of the gradient graphs 
  // excess determines build decisions 
  // start with all leaves in the leaf index and walk to root 
  // for any branch you encounter take its cost evenly from all 
  // branches 
  // this visits every node in the tree 
  // or you could do a branch first search with addition 
  // to get a locality gradient 
  // walk the entire tree 
  // store value in a struct with distance added, sum struct at 
  // every point, vertical vs lateral is simply how much distance 
  // to add 
  // each leaf and path only needs to know all the nodes below it to 
  // make decisions, those would be weighted 
  // loss depends on physical distance not number of nodes 
  // this travels down 

  // get premade safety factor for total excess exhausted 
  // follow largest gradient value in a branch until you hit a leaf 
  // keep locality and each time you traverse upwards take a penalty, 
  // make this a branch
  // perhaps calculate all the way down its complete carbon 
  // consequences, mechanical, hydraulic, etc 
  // ranking canidates by gain vs cost might be a good idea 
  // do a full subtraction for each branch going down to root 
  // if profitable keep 
  // keep doing this until all (excess * safety) factor is gone 
  // this travels up 

  // pruning algorithm 
  // search entire tree 
  // gradient OR constant are bad 
  // travel down to ther nearest point that good 
  // set that meristem to false 
  // locality could potentially influence pruning 

  // apex behaviour
  // if a branch is an apex and the full path has an excess 
  // continue 
  
  // have a mechanism where if there is enough excess for long enough it 
  // becomes trunk bulking, so just a thickening biased towards the base 

  // start by just checking if a branch is over a construction cost threshold 


void PlantArchitecture::create_branch(Meristem& node)
{
  printf("create_branch called");

  if (node.get_organ_type() != OrganType::Leaf)
    return; 

  if (node.get_carbon_balance() < node.branching_threshold)
    return; 

  // else this node has enough surplus to initiate branching  
  node.make_phyllotaxis();

  // traverse this specific node after to determine which 
  // nodes are leaves and add them to the leaf index 
  //leaves.push_back(nodeid)
}


void PlantArchitecture::evaluate_branching(Meristem& node)
{
  printf("evaluate_branching called");
  // check if current node qualifies for branching 
  create_branch(node); 

  for (Meristem& child : node.get_children())
  {
    evaluate_branching(child);
  }

}


/*
void PlantArchitecture::meristem_cull()
{
  // take large swaths of inactive meristem incorporating 
  // geometry and cull it 
  // keep three states, active, dormant, virtual / culled 
  // dormant meristem only holds position and connection 
  // on big stems make a dormant bud field struct object 
  // make the distance between dormant buds greater than phyllotaxis 
  // check bottom node, if everything above is inactive up 
  // to say 4cm from any active meristems, cull them, 
  // only retain inactive outwards facing buds at a set density
  // like 1 set every meter, this could scale with trunk thickness 
  // add removed dimensions to the bottom meristem like all 
  // the length segments removed 
  // do not remove all apical segments, use them to determine 
  // momments localized along the trunk for buttress roots 
  // but keep a set realistic length for keeping these 
  // apices for buttress roots 
  
}
*/


void PlantArchitecture::render()
{
  // traverse the entire tree 
  // get render info from meristem 
  // draw it 
  
  const int screenWidth = 1280;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Tree Simulator Debug View");
  SetTargetFPS(60);

  // 3D camera
  Camera3D camera = { 0 };
  camera.position = { 8.0f, 6.0f, 8.0f };
  camera.target = { 0.0f, 2.0f, 0.0f };
  camera.up = { 0.0f, 1.0f, 0.0f };
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  while (!WindowShouldClose())
  {
      // Camera controls
      UpdateCamera(&camera, CAMERA_ORBITAL);

      BeginDrawing();

      ClearBackground(RAYWHITE);

      BeginMode3D(camera);

      // Floor
      DrawPlane(
          { 0.0f, 0.0f, 0.0f },
          { 20.0f, 20.0f },
          LIGHTGRAY
      );

      // Vertical cylinder
      DrawCylinder(
          { 0.0f, 0.0f, 0.0f },  // center
          0.5f,                   // radius
          0.5f,                   // radius
          4.0f,                   // height
          16,                     // sides
          BROWN
      );

      // Coordinate axes
      DrawLine3D(
          { 0, 0, 0 },
          { 3, 0, 0 },
          RED
      );

      DrawLine3D(
          { 0, 0, 0 },
          { 0, 3, 0 },
          GREEN
      );

      DrawLine3D(
          { 0, 0, 0 },
          { 0, 0, 3 },
          BLUE
      );

      EndMode3D();

      DrawText(
          "Tree Simulator Debug View",
          20, 20,
          20,
          DARKGRAY
      );

      DrawText(
          "WASD / mouse: camera",
          20, 50,
          16,
          GRAY
      );

      EndDrawing();
  }

  CloseWindow();

}



/*
void PlantArchitecture::evaluate_buttress_roots()
{
  // you would need to simulate soil type and bearings 
  // to evaluate this 
  // a good genetic range would be 4-8 
  // angles could depend on actual loading of the tree 
  // buttress tendency, common number, angular regularity 
  // mechanical response, could be factors affecting buttressing 
  // they are creates because buttress roots are placed as a 
  // star below the soil when the tree is created 
  // the centre of said star can move up the trunk with mechanical 
  // stresses 

}
*/














