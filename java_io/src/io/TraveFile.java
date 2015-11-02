package io;

 
import io.input.MetisInputPrecessor;
import io.output.InfomapOutputProcessor;
import io.output.MCLOutputProcessor;
import io.output.MetisOutputProcessor;

import java.io.File;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
 
import java.util.regex.*;

public class TraveFile {

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		File root = new File("E:\\projects-git\\community-detection\\dataset");
		MetisInputPrecessor metisInputPrecessor= new MetisInputPrecessor(root);
		metisInputPrecessor.operateMetisInputs();
		MetisOutputProcessor metisOutputProcessor = new MetisOutputProcessor(root);
		metisOutputProcessor.operateMetisOutputs();
		MCLOutputProcessor mclOutputProcessor =new MCLOutputProcessor(root);
		mclOutputProcessor.operateMclOutputs();
		InfomapOutputProcessor infomapOutputProcessor =new InfomapOutputProcessor(root);
		infomapOutputProcessor.operateMclOutputs();
		System.out.println("finished");
	}

	public static Collection<File> listFiles(File root, String regStr) {
		List<File> files = new ArrayList<File>();
		listFiles(files, root, regStr);
		return files;
	}

	private static void listFiles(List<File> files, File dir, String regStr) {
		File[] listFiles = dir.listFiles();
		for (File f : listFiles) {
			if (f.isFile()) {
				Pattern pattern = Pattern.compile(regStr);
				Matcher mathcerMatcher = pattern.matcher(f.getAbsolutePath());
				if (mathcerMatcher.matches())
					files.add(f);
			} else if (f.isDirectory()) {
				listFiles(files, f, regStr);
			}
		}
	}
}
