# 3GM-D-NorthAmerica

This repository contains the model code of a variable density groundwater model for North America. 
It was created as supplemental material for the publication "" by Kretschmer et al. (2024).

The submodule "global-gradient-based-groundwater-model" contains the model framework, the files in the folder "SteadyNorthAmerica" define the specific model setup.
The input data is publicly available and needs to be adjusted to the applied grid ("./SteadyNorthAmerica/data5min/grid_na_dk.csv"). 
You may find data availability information Kretschmer et al. (2024).

## Prerequisites

clang >= 13 with openMP (currently gcc is not supported)
cmake >= 3.15.3
libboost >= 1.71
libGMP
libGtest
lcov

## How to compile
Required datasets are listed in "./SteadyNorthAmerica/CMakeLists.txt".
You need to add all datasets listed in "./SteadyNorthAmerica/CMakeLists.txt" to folder "./data5min".

For Linux: 
In your terminal, run the following commands

1. Create new folder named "build": 
	mkdir build
2. Enter new folder "build":
	cd build
3. Prepare make inside folder "build":
	cmake ../
4. Compile executable inside folder "build":
	make

Point 4. is quicker when using multiple cores (e.g., to use 4 cores: make -j 4)

## How to run

After successful compilation, you can run the executable "steady_na" by running the following command (from the folder "build"):
	./steady_na