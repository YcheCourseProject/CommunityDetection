#Community Detection
This is a probject of Community Detection.
  
##Dataset 
We have collected or generated datasets, wihch are in /dataset.
>>**/dataset/big** : Amazon, Friendship, Collaboration and Road(with poor clique structure)  
>>**/dataset/small** : Football, Karate, Polbooks  
>>**/dataset/synthetic** : Synthtic graph data generated from networkx including Gaussian Random Partition Graph, Random Partition Graph and Relaxed Caveman Graph.  

##Implementation
We implmented Attractor algorithm mentioned in a KDD2015 paper Community Detection based on Distance Dynamics[1], which adopts an distance dynamic converging method and we improved the perfomance of it in two ways.  
1. Use cached virtual edge and apply **vertex influence**  
2. Use sliding window to **remove long tailor**  

We developed tools on Java(/src/Java) to process input and output of graphs with Louvain, Infomap, MCL and Metis(src/Compared_Algorithms), developed tools on CSharp(src/CSharp) to automatically generate graph with different parameters, developed tools on Python(src/Python) to visualize the analysis of experiments and write shell scripts(src/Shell) to automatically test different datasets.

##Comparison Algorithms
We include **Louvain, Infomap, MCL, Metis** in src/Compared_Algorithms for the use of comparison with Attractor(Dynamic Distance)algorithm

##Others
Some results of our experiments are kept in /results.
Some documents are kept in /presentation.
Some questions for future analysis are kept in /questions.

[1]Shao J, Han Z, Yang Q, et al. **[Community Detection based on Distance Dynamics[C]](http://delivery.acm.org/10.1145/2790000/2783301/p1075-shao.pdf)**//Proceedings of the 21th ACM SIGKDD International Conference on Knowledge Discovery and Data Mining. ACM, 2015: 1075-1084.