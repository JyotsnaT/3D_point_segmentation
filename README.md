# 3D_point_segmentation

The above code segments out the trees from the 3d points cloud. The code is written in C++ and uses openncv for basic image reading and writing. 

The dataset used is Oakland 3-D Point Cloud Dataset - CVPR 2009 subset available at http://www.cs.cmu.edu/~vmr/datasets/oakland_3d/cvpr09/doc/

The key algorithm used is finding K nearest neighbours using KD Tree. 

Input : oakland_part2_ak.xyz_label_conf
Output : 
            


To execute the code
- In the src directory, type 'make' in the command line to compile.
- type './segment FILENAME', where FILENAME is the name of the .xyz_label_conf file from the 'original' folder without extension.
