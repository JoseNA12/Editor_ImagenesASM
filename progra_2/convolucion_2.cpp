#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

double gaussian (double x, double mu, double sigma) {
  return std::exp( -(((x-mu)/(sigma))*((x-mu)/(sigma)))/2.0 );
}

typedef std::vector<double> kernel_row;
typedef std::vector<kernel_row> kernel_type;

kernel_type produce2dGaussianKernel (int kernelRadius) {
  double sigma = kernelRadius/2.;
  kernel_type kernel2d(2*kernelRadius+1, kernel_row(2*kernelRadius+1));
  double sum = 0;
  // compute values
  for (int row = 0; row < kernel2d.size(); row++)
    for (int col = 0; col < kernel2d[row].size(); col++) {
      double x = gaussian(row, kernelRadius, sigma)
               * gaussian(col, kernelRadius, sigma);
      kernel2d[row][col] = x;
      sum += x;
    }
  // normalize
  for (int row = 0; row < kernel2d.size(); row++)
    for (int col = 0; col < kernel2d[row].size(); col++)
      kernel2d[row][col] /= sum;
  return kernel2d;
}

int main() {
  kernel_type kernel2d = produce2dGaussianKernel(3);
  std::cout << std::setprecision(5) << std::fixed;
  for (int row = 0; row < kernel2d.size(); row++) {
    for (int col = 0; col < kernel2d[row].size(); col++)
      std::cout << kernel2d[row][col] << ' ';
    std::cout << '\n';
  }
}
