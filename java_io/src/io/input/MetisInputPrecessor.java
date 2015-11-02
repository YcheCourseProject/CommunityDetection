package io.input;

import io.TraveFile;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;
import java.util.TreeSet;

public class MetisInputPrecessor {
	private TreeMap<Integer, TreeSet<Integer>> pNeighborsTreeMap;
	private TreeMap<Integer, Integer> pNameIndexTreeMap;
	private int edgeNum;
	private File rootDir;

	public MetisInputPrecessor(File rootDir) {
		super();
		this.rootDir = rootDir;

	}

	private void insertMap(int pBegin, int pEnd) {
		if (pNeighborsTreeMap.containsKey(pBegin) == false) {
			TreeSet<Integer> neighborsTreeSet = new TreeSet<Integer>();
			neighborsTreeSet.add(pEnd);
			pNeighborsTreeMap.put(pBegin, neighborsTreeSet);
		} else {
			((TreeSet<Integer>) pNeighborsTreeMap.get(pBegin)).add(pEnd);
		}
		return;
	}

	private TreeMap<Integer, TreeSet<Integer>> getNodeNeighborsTreeMap(
			File inFile) throws Exception {
		TreeMap<Integer, TreeSet<Integer>> pNeighborsTreeMap = new TreeMap<Integer, TreeSet<Integer>>();
		BufferedReader reader = new BufferedReader(new FileReader(inFile));
		while (true) {
			String lineString = reader.readLine();
			if (lineString == null)
				break;
			else {
				if (lineString.startsWith("#"))
					continue;
				String[] splitStrings = lineString.split("\\s");
				int pBegin = Integer.parseInt(splitStrings[0]);
				int pEnd = Integer.parseInt(splitStrings[1]);
				insertMap(pBegin, pEnd);
				insertMap(pEnd, pBegin);
				this.edgeNum++;
			}

		}
		reader.close();
		return pNeighborsTreeMap;
	}

	private TreeMap<Integer, Integer> getNodeNameIndexTreeMap() {
		Iterator<Integer> iterator = pNeighborsTreeMap.keySet().iterator();
		int i = 1;
		while (iterator.hasNext()) {
			int pName = (int) iterator.next();
			pNameIndexTreeMap.put(pName, i);
			i++;
		}
		return pNameIndexTreeMap;
	}

	private void operateMetisModifiedInputFiles(File originalFile)
			throws Exception {
		String metisInputFile = originalFile.getAbsolutePath().replace(
				"input.csv", "input_metis.csv");
		String metisMapFIleString = originalFile.getAbsolutePath().replace(
				"input.csv", "pname_index_map.csv");

		BufferedWriter bw = new BufferedWriter(new FileWriter(metisInputFile));

		Iterator<Map.Entry<Integer, TreeSet<Integer>>> iterator = pNeighborsTreeMap
				.entrySet().iterator();
		bw.write(pNameIndexTreeMap.size() + " " + edgeNum);
		bw.newLine();
		while (iterator.hasNext()) {
			Map.Entry<Integer, TreeSet<Integer>> entry = iterator.next();
			for (Integer integer : entry.getValue()) {
				bw.write(integer + " ");
			}
			bw.newLine();
		}
		bw.close();

	
		bw = new BufferedWriter(new FileWriter(metisMapFIleString));
		bw.write("# [Node Name] [Node Index]");
		bw.newLine();
		for (Map.Entry<Integer, Integer> entry : pNameIndexTreeMap.entrySet()) {
			bw.write(entry.getKey() + " " + entry.getValue());
			bw.newLine();
		}
		bw.close();

	}

	public void operateMetisInputs() {
		try {
			System.out.println(rootDir.getAbsolutePath());
			Collection<File> fileList = TraveFile.listFiles(rootDir,
					".*input.csv");
			for (File file : fileList) {
				System.out.println("Now operate file:"+file.getAbsolutePath());
				this.pNeighborsTreeMap = new TreeMap<Integer, TreeSet<Integer>>();
				this.pNameIndexTreeMap = new TreeMap<Integer, Integer>();
				this.edgeNum = 0;
				getNodeNeighborsTreeMap(file);
				getNodeNameIndexTreeMap();
				operateMetisModifiedInputFiles(file);
				
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
