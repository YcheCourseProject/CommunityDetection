package ip;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Map;
import java.util.Set;
import java.util.Map.Entry;

/**
 * @author cheyulin NeighborsFile must have double edges i.e (a,b) (b,a)
 */
public class MetisIP extends AbstractIP {
	private String neighborsFileString;

	public MetisIP(String edgeInputFileString, String nameIndexMapFileString,
			String neighborsFileString) throws Exception {
		super(edgeInputFileString, nameIndexMapFileString);
		this.neighborsFileString = neighborsFileString;
	}

	public void write2NeighborsFile() throws IOException {
		BufferedWriter writer = new BufferedWriter(new FileWriter(
				neighborsFileString));
		Map<Integer, Set<Integer>> nodeNeighborsMap = getNodeNeighborsMap();
		int edgeNum = 0;
		for (Entry<Integer, Set<Integer>> entry : nodeNeighborsMap.entrySet()) {
			edgeNum += entry.getValue().size();
		}
		writer.write(nodeNeighborsMap.size() + " " + edgeNum/2);
		writer.newLine();
		
		Map<Integer, Integer> nameIndexMap = getNameIndexMap();
		for (Entry<Integer, Set<Integer>> entry : nodeNeighborsMap.entrySet()) {
			for (Integer integer : entry.getValue()) {
					writer.write(nameIndexMap.get(integer) + " ");
			}
			writer.newLine();
		}
		writer.close();
	}

	@Override
	public StartIndex setStartIndex() {
		// TODO Auto-generated method stub
		return StartIndex.One;
	}

	public static void main(String []args) throws Exception{
		new MetisIP(args[0], args[1],args[2]).write2NeighborsFile();
	}
}
