import networkx as nx
import community

OriginGraph = nx.Graph();
OriginGraph = nx.read_edgelist("C:\Users\ssunah\gitchina\Community-Detection\dataset\small\karate\karate_edges_input_uni.csv", encoding='utf-8')
print(OriginGraph.nodes())
