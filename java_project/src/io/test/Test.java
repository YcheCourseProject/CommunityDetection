package io.test;

import io.input.MetisInputPrecessor;

public class Test {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MetisInputPrecessor metisInputPrecessor =new MetisInputPrecessor(args[0], args[1], args[2]);
		metisInputPrecessor.operateMetisInputs();
	}

}
