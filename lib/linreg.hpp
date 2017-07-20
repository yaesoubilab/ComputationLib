#pragma once
#include <Eigen/Core>

namespace linreg {
  typedef Eigen::MatrixXd mat;
  typedef Eigen::VectorXd vec;
  class LinearRegression {
  public:
	
    // θ = (X'WX)^-1 X'WY, where W(i, i) is λ^(n-i-1); n is the number of observations
    inline static vec runRegression(double l, const mat &xs, const vec &ys) {
      return(runRegression(l, 0, xs, ys));
    }

    // θ = (X'X)^-1 X'Y
    inline static vec runRegression(const mat &xs, const vec &ys) {
      return(runRegression(1, 0, xs, ys));
    }
    
    // θ = (X'WX + ωI)^-1 X'WY, where ω > 0 is the L2 regularization factor
    static vec runRegression(double, double, const mat &, const vec &);
    
    // constructor to use the training algorithm to estimate coefficient
    // ω ≥ 0 is the L2 regularization factor
    inline LinearRegression(int dim, double omeg = 0) : theta(dim),
      yvec(dim), xmat(dim, dim), points(dim), dim(dim),
      omega(omeg) {
      	b.setIdentity(dim, dim);
      }

    // update theta based on new x' and y using forgetting factor λ
    bool updateCoefficients(const vec &, double, double = 1);

    // get θ
    inline const vec &getCoefficients() const {
      return(theta);
    }

    const int dim; // mumber of columns of X
    const double omega; // L2 regularization factor

  private:
    vec theta, yvec;
    mat b, xmat;
    int points;
  };
}
