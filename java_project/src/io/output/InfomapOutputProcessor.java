package io.output;


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

public class InfomapOutputProcessor {
	private String inFileString;
	private String outFileString;
	public InfomapOutputProcessor(String inFileString, String outFileString) {
		super();
		this.inFileString = inFileString;
		this.outFileString = outFileString;
	}

	public void operateMclOutputs() {
		try {
				System.out.println("Now operate infomap output file:"
						+ inFileString);
				reorganizeFile();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return;
	}

	private void reorganizeFile() throws Exception {
		// TODO Auto-generated method stub
		BufferedReader bReader = new BufferedReader(new FileReader(inFileString));
		BufferedWriter bWriter = new BufferedWriter(new FileWriter(outFileString));

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
