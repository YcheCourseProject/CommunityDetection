package op;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

public class MetisOP extends AbstractOP{

	private String clusterNodeIndexFileString;
	
	
	public MetisOP(String nameIndexMapFileString,
			String outCluNodeNameFileString, String clusterNodeIndexFileString) {
		super(nameIndexMapFileString, outCluNodeNameFileString);
		this.clusterNodeIndexFileString = clusterNodeIndexFileString;
	}


	@Override
	public Map<Integer, Set<Integer>> getClusterNodeIndexMap()
			throws IOException {
		// TODO Auto-generated method stub
		BufferedReader bReader = new BufferedReader(
				new FileReader(clusterNodeIndexFileString));
		Map<Integer, Set<Integer>> clusterNodeIndexMap =new TreeMap<Integer, Set<Integer>>();
		int nodeIndex=0;
		while (true) {
			String lineString = bReader.readLine();
			if (lineString == null)
				break;
			if (lineString.startsWith("#"))
				continue;
			nodeIndex++;
			int clusterNum = Integer.parseInt(lineString);
			if(clusterNodeIndexMap.containsKey(clusterNum)==false){
				TreeSet<Integer> nodesInSameClusterIntegers = new TreeSet<>();
				nodesInSameClusterIntegers.add(nodeIndex);
				clusterNodeIndexMap.put(clusterNum, nodesInSameClusterIntegers);
			}
			else {
				clusterNodeIndexMap.get(clusterNum).add(nodeIndex);
			}
		}
		bReader.close();
		return clusterNodeIndexMap;
	}


	public static void main(String[]args) throws IOException{
		new MetisOP(args[0], args[1], args[2]).write2ClusterNodeNameFile();
	}

}
