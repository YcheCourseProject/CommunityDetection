package op;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class NameIndexMapReader {
	private String nameIndexMapFileString;
	private Map<Integer, Integer> indexNameMap;
	public NameIndexMapReader(String nameIndexMapFileString) {
		super();
		this.nameIndexMapFileString = nameIndexMapFileString;
		this.indexNameMap = null;
	}
	
	private void readNameIndexFile2IndexNameMap() throws IOException{
		this.indexNameMap = new HashMap<Integer, Integer>();
		BufferedReader reader = new BufferedReader(new FileReader(
				nameIndexMapFileString));
		while (true) {
			String lineString = reader.readLine();
			if (lineString == null)
				break;
			else {
				if (lineString.startsWith("#"))
					continue;
				String[] splitStrings = lineString.split("\\s");
				int name = Integer.parseInt(splitStrings[0]);
				int index = Integer.parseInt(splitStrings[1]);
				// one to one mapping
				if(indexNameMap.containsKey(index) == false){
					indexNameMap.put(index, name);
				}
			}
		}
		reader.close();
	}
	
	public  Map<Integer, Integer> getIndexNameMap() throws IOException {
		if(indexNameMap == null || indexNameMap.size() ==0){
			readNameIndexFile2IndexNameMap();
		}
		return indexNameMap;
	}
}
