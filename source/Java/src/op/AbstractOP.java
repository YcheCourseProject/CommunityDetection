package op;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Map;
import java.util.Set;

public abstract class AbstractOP {
	String nameIndexMapFileString;
	String outCluNodeNameFileString;
	Map<Integer, Set<Integer>> clusterNodeIndexMap;
	Map<Integer, Integer> nodeIndexNameMap;
	
	
	public AbstractOP(String nameIndexMapFileString,
			String outCluNodeNameFileString) {
		super();
		this.nameIndexMapFileString = nameIndexMapFileString;
		this.outCluNodeNameFileString = outCluNodeNameFileString;
	}

	public void write2ClusterNodeNameFile() throws IOException{
		clusterNodeIndexMap = getClusterNodeIndexMap();
		BufferedWriter writer = new BufferedWriter(new FileWriter(
				outCluNodeNameFileString));
		NameIndexMapReader nameIndexMapReader =new NameIndexMapReader(nameIndexMapFileString);
		nodeIndexNameMap=nameIndexMapReader.getIndexNameMap();
		for(Map.Entry<Integer, Set<Integer>> entry : clusterNodeIndexMap.entrySet()){
			int clusterNum = entry.getKey();
			Set<Integer> nodesInSameCluster = entry.getValue();
			for(Integer nodeIndex : nodesInSameCluster){
				writer.write(clusterNum+" "+ nodeIndexNameMap.get(nodeIndex));
				writer.newLine();
			}
		}
		writer.close();
	}
	
	abstract public Map<Integer, Set<Integer>> getClusterNodeIndexMap() throws IOException;
}
