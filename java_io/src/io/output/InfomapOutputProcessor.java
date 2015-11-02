package io.output;

import io.TraveFile;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Collection;

public class InfomapOutputProcessor {
	File rootDir;

	public InfomapOutputProcessor(File rootDir) {
		super();
		this.rootDir = rootDir;
	}

	public void operateMclOutputs() {
		try {
			System.out.println(rootDir.getAbsolutePath());
			Collection<File> fileList = TraveFile.listFiles(rootDir, ".*tree");
			for (File file : fileList) {
				System.out.println("Now operate infomap output file:"
						+ file.getAbsolutePath());

				reorganizeFile(file);
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		return;
	}

	private void reorganizeFile(File file) throws Exception {
		// TODO Auto-generated method stub
		BufferedReader bReader = new BufferedReader(new FileReader(file));
		String outFileString = file.getAbsolutePath().replace(
				"_input_infomap.tree", "_output_measurement_infomap.csv");
		BufferedWriter bWriter = new BufferedWriter(new FileWriter(
				outFileString));

		String currentClusterNameString = "";
		int i = 0;
		while (true) {
			String lineString = bReader.readLine();
			if (lineString == null)
				break;
			if (lineString.startsWith("#"))
				continue;
			String[] tempStrings = lineString.split("\\s");
			String clusterNameString = tempStrings[0];
			String nodeNameString = tempStrings[2];
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

			bWriter.write(i+" "+nodeNameString.replace("\"", ""));
			bWriter.newLine();
		}
		bWriter.close();
		bReader.close();
		return;
	}
}
