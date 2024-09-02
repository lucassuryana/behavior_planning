#include "cost.h"
#include <cmath>

double goal_distance_cost(int goal_lane, int intended_lane, int final_lane, 
                          double distance_to_goal) {
  // The cost increases with both the distance of intended lane from the goal
  //   and the distance of the final lane from the goal. The cost of being out 
  //   of the goal lane also becomes larger as the vehicle approaches the goal.
    
  int delta_d_intended;
  int delta_d_final;
  delta_d_intended = std::abs(goal_lane - intended_lane);
  delta_d_final = std::abs(goal_lane - final_lane);
  double cost = 1 - std::exp(-(delta_d_intended + delta_d_final)/distance_to_goal);
    
  return cost;
}