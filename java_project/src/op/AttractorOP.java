package op;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

public class AttractorOP extends AbstractOP {
	private String clusterNodeIndexFileString;
	
	public AttractorOP(String nameIndexMapFileString,
			String outCluNodeNameFileString, String clusterNodeIndexFileString) {
		super(nameIndexMapFileString, outCluNodeNameFileString);
		this.clusterNodeIndexFileString = clusterNodeIndexFileString;
	}

	@Override
	public Map<Integer, Set<Integer>> getClusterNodeIndexMap() throws IOException{
		// TODO Auto-generated method stub
		BufferedReader bReader = new BufferedReader(
				new FileReader(clusterNodeIndexFileString));
		Map<Integer, Set<Integer>> clusterNodeIndexMap =new TreeMap<Integer, Set<Integer>>();
		while (true) {
			String lineString = bReader.readLine();
			if(lineString==null)
				break;
			if(lineString.startsWith("#"))
				continue;
			String [] strings = lineString.split("\\s");
			int nodeIndex = Integer.valueOf(strings[1]);
			int clusterName = Integer.valueOf(strings[0]);
			if(clusterNodeIndexMap.containsKey(clusterName)==false){
				TreeSet<Integer> nodesInSameClusterIntegers = new TreeSet<>();
				nodesInSameClusterIntegers.add(nodeIndex);
				clusterNodeIndexMap.put(clusterName, nodesInSameClusterIntegers);
			}
			else {
				clusterNodeIndexMap.get(clusterName).add(nodeIndex);
			}
		}
		bReader.close();
		return clusterNodeIndexMap;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new AttractorOP(args[0], args[1], args[2]);
	}

}
