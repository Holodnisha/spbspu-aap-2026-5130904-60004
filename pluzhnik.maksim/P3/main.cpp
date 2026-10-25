#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>

namespace pluzhnik {
  int countLocalMinima(const int *matrix, int rows, int cols);
}
int main()
{
  int mode;
  if (!(std::cin >> mode) || (mode != 1 && mode != 2)) {
    std::cerr << "Error: mode" << std::endl;
    return 1;
  }

  if (std::freopen("input.txt", "r", stdin) == nullptr) {
    std::cerr << "Error: input file" << std::endl;
    return 2;
  }
  if (std::freopen("output.txt", "w", stdout) == nullptr) {
    std::cerr << "Error: output file" << std::endl;
    return 2;
  }

  int rows, cols;
  if (!(std::cin >> rows >> cols) || rows <= 0 || cols <= 0) {
    std::cerr << "Error: size" << std::endl;
    return 2;
  }
  int totalElements = rows * cols;
  int result = 0;
  if (mode == 1) {
    if (totalElements > 10000) {
      std::cerr << "Error: limit rows * cols" << std::endl;
      return 2;
    }

    int staticBuffer[10000];

    for (int i = 0; i < totalElements; ++i) {
      if (!(std::cin >> staticBuffer[i])) {
        std::cerr << "Error: input data" << std::endl;
        return 2;
      }
    }

    result = pluzhnik::countLocalMinima(staticBuffer, rows, cols);
  } else {
    int *dynamicBuffer = new (std::nothrow) int[totalElements];
    if (dynamicBuffer == nullptr) {
      std::cerr << "Error: memory" << std::endl;
      return 2;
    }

    for (int i = 0; i < totalElements; ++i) {
      if (!(std::cin >> dynamicBuffer[i])) {
        std::cerr << "Error: data" << std::endl;
        delete[] dynamicBuffer;
        return 2;
      }
    }

    result = pluzhnik::countLocalMinima(dynamicBuffer, rows, cols);
    delete[] dynamicBuffer;
  }
  std::cout << result << std::endl;

  return 0;
}

namespace pluzhnik {

  int countLocalMinima(const int *matrix, int rows, int cols)
  {
    int count = 0;
    for (int i = 1; i < rows - 1; ++i) {
      for (int j = 1; j < cols - 1; ++j) {
        int number = matrix[i * cols + j];

        int top = matrix[(i - 1) * cols + j];
        int under = matrix[(i + 1) * cols + j];
        int left = matrix[i * cols + (j - 1)];
        int right = matrix[i * cols + (j + 1)];
        if (number < top && number < under && number < left && number < right) {
          count++;
        }
      }
    }

    return count;
  }
}
