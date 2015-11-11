package op;


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

public class InfomapOP extends AbstractOP {


	private String clusterNodeIndexFileString;

	public InfomapOP(String nameIndexMapFileString,
			String outCluNodeNameFileString, String clusterNodeIndexFileString) {
		super(nameIndexMapFileString, outCluNodeNameFileString);
		this.clusterNodeIndexFileString = clusterNodeIndexFileString;
	}

	@Override
	public Map<Integer, Set<Integer>> getClusterNodeIndexMap()
			throws IOException {
		// TODO Auto-generated method stub
		BufferedReader bReader = new BufferedReader(new FileReader(clusterNodeIndexFileString));
		Map<Integer, Set<Integer>> clusterNodeIndexMap =new TreeMap<Integer, Set<Integer>>();
		
		String currentClusterNameString = "";
		int i = -1;
		while (true) {
			String lineString = bReader.readLine();
			if (lineString == null)
				break;
			if (lineString.startsWith("#"))
				continue;
			
			String[] tempStrings = lineString.split("\\s");
			String clusterNameString = tempStrings[0];
			int nodeIndex= Integer.parseInt(tempStrings[3]);
			StringBuilder sBuilder = new StringBuilder();
			tempStrings = clusterNameString.split(":");
			for (int j = 0; j < tempStrings.length -1; j++) {
				sBuilder.append(tempStrings[j]).append(":");
			}
			clusterNameString = sBuilder.toString();
			
			if(!clusterNameString.equals(currentClusterNameString)){
				i++;
				currentClusterNameString =clusterNameString;
			}
			if(clusterNodeIndexMap.containsKey(i)==false){
				TreeSet<Integer> nodesInSameClusterIntegers = new TreeSet<>();
				nodesInSameClusterIntegers.add(nodeIndex);
				clusterNodeIndexMap.put(i, nodesInSameClusterIntegers);
			}
			else {
				clusterNodeIndexMap.get(i).add(nodeIndex);
			}
		}
		bReader.close();
		return clusterNodeIndexMap;
	}
	
	public static void main(String []args) throws Exception{
		new InfomapOP(args[0], args[1], args[2]).write2ClusterNodeNameFile();
	}

}
