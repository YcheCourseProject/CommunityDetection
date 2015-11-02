package io.output;

import io.TraveFile;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Collection;
import java.util.Map;
import java.util.TreeMap;

public class MetisOutputProcessor {
	private TreeMap<Integer, Integer> nodeIndexClusterMap;
	private TreeMap<Integer, Integer> nodeIndexNameMap;

	private File rootDir;

	public MetisOutputProcessor(File rootDir) {
		super();
		this.rootDir = rootDir;
	}

	private void getNodeIndexClusterMap(File inFile) throws Exception {
		BufferedReader br = new BufferedReader(new FileReader(inFile));
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

	private void getNodeIndexNameMap(File inFile) throws Exception {
		String splitStrings[] = inFile.getAbsolutePath().split(
				"_input_metis.csv.part");
		File mapInFile = new File(splitStrings[0] + "_pname_index_map.csv");
		BufferedReader br = new BufferedReader(new FileReader(mapInFile));
		while (true) {
			String lineString = br.readLine();
			if (lineString == null)
				break;
			if (lineString.startsWith("#"))
				continue;
			splitStrings = lineString.split("\\s");
			int nodeName = Integer.parseInt(splitStrings[0]);
			int nodeIndex = Integer.parseInt(splitStrings[1]);
			nodeIndexNameMap.put(nodeIndex, nodeName);
		}
		br.close();
		return;
	}

	private void writeMetisMeasuremnetOutput(File inFile) throws Exception {
		String splitStrings[] = inFile.getAbsolutePath().split(
				"_input_metis.csv.part");
		File outFile = new File(splitStrings[0]
				+ "_output_measurement_metis.csv");
		BufferedWriter bWriter = new BufferedWriter(new FileWriter(outFile));
 
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
			System.out.println(rootDir.getAbsolutePath());
			Collection<File> fileList = TraveFile.listFiles(rootDir,
					".*csv.part.[0-9]+");
			for (File file : fileList) {
				System.out.println("Now operate metis output file:"
						+ file.getAbsolutePath());
				this.nodeIndexClusterMap = new TreeMap<Integer, Integer>();
				this.nodeIndexNameMap = new TreeMap<Integer, Integer>();
				getNodeIndexClusterMap(file);
				getNodeIndexNameMap(file);
				writeMetisMeasuremnetOutput(file);

			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return;
	}

}
