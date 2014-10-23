TestGen-IFx
===========

Automatic test cases generation from an IF specification for distributed testing


This file explains how to use the TestGenIF:

	1/ Program Requirements
	2/ The TestGenIFx Directory Contents
	3/ Edit the test purposes
	4/ Generate test cases
	
===========================================================================================================	
1/ Program Requirements
===========================================================================================================
a. IF2-0 Distribution
	- You must install libstdc++5 (e.g. by apt-get install), the package m4 
		and the last version of g++-x.y
	
	- Install IF2-0 following its instructions 
	 
b. TestGenIFx Distribution	
	- Extract the TestGen-IFx.zip to a folder, e.g., /home/nhnghia/
	 
	- You must add these lines to your ~/.bashrc:

	# TestGenIFx
	export TestGenIFx=/home/nhnghia/TestGen-IFx
	export PATH=$TestGenIFx/lib:$PATH

    and type: $ source ~/.bashrc
   
===========================================================================================================
2/ The TestGenIFx Directory Contents
===========================================================================================================



===========================================================================================================
3/ Edit the test purposes
===========================================================================================================
...


===========================================================================================================
4/ Generate Test Cases
===========================================================================================================

Run the command: testgenifx -i input -s strategy -d maxdepth -t testpurpose

- input      : is file name of IF model
- strategy   : is one of the followings: hoj, dfs, bfs, ran
- maxdepth   : is a number
- testpurpose: is file name of test purpose

Example:         testgenifx -i obu.if -s hoj -d 4 -t test-purposes.C 
  the output will be found in folder ./obu/
