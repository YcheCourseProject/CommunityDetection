package ip;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Map;
import java.util.Set;
import java.util.Map.Entry;

public class InfomapIP extends AbstractIP {

	private String edgeWithIndexFileString;

	public InfomapIP(String edgeInputFileString, String nameIndexMapFileString,
			String edgeWithIndexFileString) throws Exception {
		super(edgeInputFileString, nameIndexMapFileString);
		this.edgeWithIndexFileString = edgeWithIndexFileString;
	}

	public void write2EdgeWithIndexFile() throws IOException {
		BufferedWriter writer = new BufferedWriter(new FileWriter(
				edgeWithIndexFileString));
		Map<Integer, Set<Integer>> nodeNeighborsMap = getNodeNeighborsMap();

		Map<Integer, Integer> nameIndexMap = getNameIndexMap();
		for (Entry<Integer, Set<Integer>> entry : nodeNeighborsMap.entrySet()) {
			int firstNode = entry.getKey();
			for (Integer secondNode : entry.getValue()) {
				if (firstNode < secondNode) {
					writer.write(nameIndexMap.get(firstNode) + " " + nameIndexMap.get(secondNode));
					writer.newLine();
				} else {
					continue;
				}
			}

		}
		writer.close();
	}

	@Override
	public StartIndex setStartIndex() {
		// TODO Auto-generated method stub
		return StartIndex.One;
	}
	
	public static void main(String args[]) throws Exception{
		new InfomapIP(args[0], args[1], args[2]).write2EdgeWithIndexFile();
	}

}
