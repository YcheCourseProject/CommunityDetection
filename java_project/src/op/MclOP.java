package op;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

public class MclOP {
	private String inFileString;
	private String outFileString;

	public MclOP(String inFileString, String outFileString) {
		super();
		this.inFileString = inFileString;
		this.outFileString = outFileString;
	}

	public void operateMclOutputs() {
		try {
			reorganizeFile();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return;
	}

	private void reorganizeFile() throws Exception {
		// TODO Auto-generated method stub
		BufferedReader bReader = new BufferedReader(
				new FileReader(inFileString));
		BufferedWriter bWriter = new BufferedWriter(new FileWriter(
				outFileString));

		int i = 1;
		while (true) {
			String lineString = bReader.readLine();
			if (lineString == null)
				break;
			if (lineString.startsWith("#"))
				continue;
			String[] nodeNameStrings = lineString.split("\\s");
			for (String string : nodeNameStrings) {
				bWriter.write(i + " " + string);
				bWriter.newLine();
			}
			i++;
		}
		bWriter.close();
		bReader.close();
		return;
	}
	
	public static void main(String []args){
		MclOP mclOutputProcessor=new MclOP(args[0], args[1]);
		mclOutputProcessor.operateMclOutputs();
	}
}
