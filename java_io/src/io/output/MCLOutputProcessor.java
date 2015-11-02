package io.output;

import io.TraveFile;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Collection;

public class MCLOutputProcessor {
	private File rootDir;

	public MCLOutputProcessor(File rootDir) {
		super();
		this.rootDir = rootDir;
	}

	public void operateMclOutputs() {
		try {
			System.out.println(rootDir.getAbsolutePath());
			Collection<File> fileList = TraveFile.listFiles(rootDir,
					".*output_mcl.csv");
			for (File file : fileList) {
				System.out.println("Now operate mcl output file:"
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
		String outFileString =file.getAbsolutePath().replace("_mcl.csv", "_measurement_mcl.csv");
		BufferedWriter bWriter =new BufferedWriter(new FileWriter(outFileString));
 
		int i=1;
		while (true) {
			String lineString = bReader.readLine();
			if(lineString ==null)
				break;
			if(lineString.startsWith("#"))
				continue;
			String [] nodeNameStrings =lineString.split("\\s");
			for(String string :nodeNameStrings){
				bWriter.write(i+" "+string);
				bWriter.newLine();
			}
			
			i++;
		}
		bWriter.close();
		bReader.close();
		return;
	}
}
