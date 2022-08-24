This folder contains the source code for testing the skeletonization algorithm proposed by Pierre Thore and Antoine Lucas (2021).

to generate the executable type "make" in this folder.
to run the algorithm type: "testSkeleton 50 ../data/input/DTMap.prop 50  > ../data/output/skeleton.skel" in this folder. The output skeleton file is generated in the folder "data/output" under the name "skeleton.skel".

the format of the skeleton file is the following: files are in ascii format 
set of nodes
"SEGMENTS" line separator
set of segments


nodes are in grid coordinates, one node per line, each line contains: node index, column coordinate, line coordinate
segments are in node index, one segment per line: start node index, end node index

for example a skeleton of the 201,201 grid with 3 branches:
 main branch with 3 points on the first diagonal 
 second branch with 3 points on the third line 
 third branch with 2 points on the third column 
would look like:
1 0 0 	//1st branch: [ vertex index, coord i, coord j ]
2 1 1 	//1st branch
3 2 2 	//1st branch
6 2 3 	//3rd branch
4 3 2 	//2nd branch
5 4 2 	//2nd branch
SEGMENT
1 2 1 1	//1st branch: [ vertex index, vertex index, rank (topology), branch index ]  
2 3 1 1	//1st branch
3 4 2 2	//2nd branch
4 5 2 2	//2nd branch
3 6 2 3	//3rd branch


x	x	x	x	x	x
x	x	o	x	x	x
x	x	o	o	o	x
x	o	x	x	x	x
o	x	x	x	x	x

beware that nodes are not always in increasing index order

