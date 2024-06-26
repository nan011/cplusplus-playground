## Create solution
1. Create folder to store solution
```
mkdir <folder-name>
```

2. Create CMakeLists.txt
```
# CMake minimum required version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(<project-name> VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(<project-name> <solution-file-name>)
```

2. Run command
```
cmake . && make && ./run < ./input.txt
```

## Start codes
```
#include <iostream>
#include <vector> 
#include <map>

using namespace std;

typedef long long ll;
using ll = long long;

int main() {
    return 0;
}
```