package io.output;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Map;
import java.util.TreeMap;

public class MetisOutputProcessor {
	private TreeMap<Integer, Integer> nodeIndexClusterMap;
	private TreeMap<Integer, Integer> nodeIndexNameMap;

	private String inFileString;
	private String outFileString;
	private String mapFileString;

	public MetisOutputProcessor(String inFileString, String outFileString,
			String mapFileString) {
		super();
		this.inFileString = inFileString;
		this.outFileString = outFileString;
		this.mapFileString = mapFileString;
	}

	private void getNodeIndexClusterMap() throws Exception {
		BufferedReader br = new BufferedReader(new FileReader(inFileString));
		int i = 1;
		while (true) {
			String lineString = br.readLine();
			if (lineString == null)
				break;
			if (lineString.startsWith("#"))
				continue;
			nodeIndexClusterMap.put(i, Integer.parseInt(lineString));
			i++;
		}
		br.close();
		return;
	}

	private void getNodeIndexNameMap() throws Exception {
		File mapInFile = new File(mapFileString);
		BufferedReader br = new BufferedReader(new FileReader(mapInFile));
		while (true) {
			String lineString = br.readLine();
			if (lineString == null)
				break;
			if (lineString.startsWith("#"))
				continue;
			String[] splitStrings = lineString.split("\\s");
			int nodeName = Integer.parseInt(splitStrings[0]);
			int nodeIndex = Integer.parseInt(splitStrings[1]);
			nodeIndexNameMap.put(nodeIndex, nodeName);
		}
		br.close();
		return;
	}

	private void writeMetisMeasuremnetOutput() throws Exception {
		BufferedWriter bWriter = new BufferedWriter(new FileWriter(outFileString));

		for (Map.Entry<Integer, Integer> entry : this.nodeIndexClusterMap
				.entrySet()) {
			int index = entry.getKey();
			int name = this.nodeIndexNameMap.get(index);
			int clusterNum = entry.getValue();
			bWriter.write(clusterNum + " " + name);
			bWriter.newLine();
		}
		bWriter.close();
		return;
	}

	public void operateMetisOutputs() {
		try {
			System.out.println("Now operate metis output file:" + inFileString);
			this.nodeIndexClusterMap = new TreeMap<Integer, Integer>();
			this.nodeIndexNameMap = new TreeMap<Integer, Integer>();
			getNodeIndexClusterMap();
			getNodeIndexNameMap();
			writeMetisMeasuremnetOutput();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return;
	}

}
