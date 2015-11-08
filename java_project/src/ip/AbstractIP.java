package ip;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Map;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

public abstract class AbstractIP {
	private String edgeInputFileString;
	private String nameIndexMapFileString;
	private Map<Integer, Integer> nameIndexMap;
	private Map<Integer, Set<Integer>> nodeNeighborsMap;

	public enum StartIndex {
		Zero, One
	}

	public AbstractIP(String edgeInputFileString,
			String nameIndexMapFileString) throws Exception{
		super();
		this.edgeInputFileString = edgeInputFileString;
		this.nameIndexMapFileString = nameIndexMapFileString;
		getNodeNeighborsTreeMap();
		getNameIndexTrepNameeMap();
		write2NameIndexMapFile();
	}
	
	

	public Map<Integer, Integer> getNameIndexMap() {
		return nameIndexMap;
	}

	public Map<Integer, Set<Integer>> getNodeNeighborsMap() {
		return nodeNeighborsMap;
	}

	private void insertSecond2FirstNeighbor(int firstNode, int secondNode) {
		if (nodeNeighborsMap.containsKey(firstNode) == false) {
			Set<Integer> neighborsTreeSet = new TreeSet<Integer>();
			neighborsTreeSet.add(secondNode);
			nodeNeighborsMap.put(firstNode, neighborsTreeSet);
		} else {
			((TreeSet<Integer>) nodeNeighborsMap.get(firstNode)).add(secondNode);
		}
		return;
	}

	private void getNodeNeighborsTreeMap() throws IOException {
		this.nodeNeighborsMap = new TreeMap<Integer, Set<Integer>>();
		BufferedReader reader = new BufferedReader(new FileReader(
				edgeInputFileString));
		while (true) {
			String lineString = reader.readLine();
			if (lineString == null)
				break;
			else {
				if (lineString.startsWith("#"))
					continue;
				String[] splitStrings = lineString.split("\\s");
				int firstNode = Integer.parseInt(splitStrings[0]);
				int secondNode = Integer.parseInt(splitStrings[1]);
				insertSecond2FirstNeighbor(firstNode, secondNode);
				insertSecond2FirstNeighbor(secondNode, firstNode);
			}
		}
		reader.close();
	}
	
	private void getNameIndexTrepNameeMap() throws RuntimeException{
		this.nameIndexMap = new TreeMap<Integer, Integer>();
		Iterator<Integer> iterator = nodeNeighborsMap.keySet().iterator();
		StartIndex startIndex = setStartIndex();
		int i;
		if(startIndex.equals(StartIndex.One)){
			i=1;
		}
		else if(startIndex.equals(StartIndex.Zero)){
			i=0;
		}
		else {
			throw new RuntimeException();
		}
		while (iterator.hasNext()) {
			int name = (int) iterator.next();
			nameIndexMap.put(name, i);
			i++;
		}
	}
	
	private void write2NameIndexMapFile() throws IOException{
		BufferedWriter writer =new BufferedWriter(new FileWriter(nameIndexMapFileString));
		writer.write("# [Node Name] [Node Index]");
		writer.newLine();
		for (Map.Entry<Integer, Integer> entry : nameIndexMap.entrySet()) {
			writer.write(entry.getKey() + " " + entry.getValue());
			writer.newLine();
		}
		writer.close();
	}
	
	abstract public StartIndex setStartIndex();

}
