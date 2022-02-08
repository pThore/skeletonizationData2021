This folder contains the grid file "DTMap.prop" used to test the skeletonization algorithm proposed by Thore & Lucas (2021). The code is in the the folder "../../src". The command to compute the skeleton.skel file is: 
"testSkeleton ../data/input/DTMap.prop  > ../data/output/skeleton.skel 50" 
in the src folder. 



the format of the grid file is the following:
nbRows, nbColumns, noData-Value  //first line
grid value // grid index 1,1
grid value // grid index 1,2
.....
grid value // grid index 1, nbColumns
grid value // grid index 2,1
grid value // grid index 1,2
.....
grid value // grid index nbRows, nbColumns

the folder contains also a crisp version (0,1 value) of the model: "binaryMap.prop"
