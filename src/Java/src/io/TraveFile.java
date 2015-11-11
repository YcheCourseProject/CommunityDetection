package io;

import java.io.File;
import java.lang.invoke.ConstantCallSite;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import java.util.regex.*;

public class TraveFile {
	public static final String METIS = "metis";
	public static final String INFOMAP = "infomap";
	public static final String MCL = "mcl";
	public static final String INPUT = "input";
	public static final String OUTPUT = "output";

	public static void printHints() {
		System.out
				.println("1st arg metis|infomap|mcl; 2nd arg infile|outfile ; 3rd infilepath; others");
	}

	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		boolean isRightArgs = true;
		if (args.length < 2) {
			isRightArgs = false;
		} else {
			String algTypeString = args[0];
			String ioTypeString = args[1];
			switch (algTypeString) {
			case METIS:
				if (ioTypeString.equals("input")) {
					
				} else if (ioTypeString.equals("output"))
					System.out.println("output metis");
				else {
					isRightArgs = false;
				}
				break;
			case INFOMAP:
				if (ioTypeString.equals("output"))
					System.out.println("output infomap");
				else {
					isRightArgs = false;
				}
				break;
			case MCL:
				if (ioTypeString.equals("output"))
					System.out.println("output metis");
				else {
					isRightArgs = false;
				}
				break;
			default:
				break;
			}
		}

		if (isRightArgs == false) {
			printHints();
		}
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
