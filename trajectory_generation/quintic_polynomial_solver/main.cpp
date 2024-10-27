#include <cmath>
#include <iostream>
#include <vector>

#include <Eigen/Dense>
#include "grader.h"

using std::vector;
using Eigen::MatrixXd;
using Eigen::VectorXd;

vector<double> JMT( vector<double> &start,
                    vector<double> &end,
                    double T) {
    double alpha_0 = start[0];
    double alpha_1 = start[1];
    double alpha_2 = .5* start[2];

    MatrixXd A = MatrixXd(3, 3);
    A << T*T*T, T*T*T*T, T*T*T*T*T,
        3*T*T, 4*T*T*T,5*T*T*T*T,
        6*T, 12*T*T, 20*T*T*T;
        
    MatrixXd B = MatrixXd(3,1);     
    B << end[0]-(start[0]+start[1]*T+.5*start[2]*T*T),
        end[1]-(start[1]+start[2]*T),
        end[2]-start[2];
            
    MatrixXd Ai = A.inverse();
    
    MatrixXd C = Ai*B;

    vector<double> result = {alpha_0, alpha_1, alpha_2};

    for(int i = 0; i < C.size(); ++i) {
        result.push_back(C.data()[i]);
    }

    return result;
                    }

int main() {

  // create test cases
  vector< test_case > tc = create_tests();

  bool total_correct = true;

  for(int i = 0; i < tc.size(); ++i) {
    vector<double> jmt = JMT(tc[i].start, tc[i].end, tc[i].T);
    bool correct = close_enough(jmt, answers[i]);
    total_correct &= correct;
  }

  if(!total_correct) {
    std::cout << "Try again!" << std::endl;
  } else {
    std::cout << "Nice work!" << std::endl;
  }

  return 0;
}