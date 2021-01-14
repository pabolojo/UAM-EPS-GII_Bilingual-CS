package part6.ads.assignment3;
import java.io.*;
import java.util.*;

/**
 * ApplianceReader for Part 2 of lab assignment 3.
 */

public abstract class  ApplianceReader{
	
	/**
	 * Creates appliances from the information read in a file.
	 * Receives the file name through the argument "filename".
	 * @param filename The argument must be the name of the text file describing products
	 */
	public static List<Appliance> readAppliances (String filename){

		List<Appliance> result = new ArrayList<Appliance>();
		Appliance read = null;

		BufferedReader buffer = null;
		try {
			buffer = new BufferedReader(
					new InputStreamReader(
							new FileInputStream(filename)));
		} catch (FileNotFoundException e2) {
			e2.printStackTrace();
		}
		String line;

		try {
			while ((line = buffer.readLine()) != null) {
				String[] data = line.split("=");
				switch(data.length) {
				case 5:
					read = new Television(data[0], data[1], Double.parseDouble(data[2]), EnergyEfficiency.valueOf(data[3]),  Double.parseDouble(data[4]));
					break;
				case 8:
					read = new Washer(data[0], data[1], Double.parseDouble(data[2]), EnergyEfficiency.valueOf(data[3]),  new Dimension(Double.parseDouble(data[4]), Double.parseDouble(data[5]), Double.parseDouble(data[6])), Double.parseDouble(data[7]));
					break;
				case 9:
					read = new Refrigerator(data[0], data[1], Double.parseDouble(data[2]), EnergyEfficiency.valueOf(data[3]),  new Dimension(Double.parseDouble(data[4]), Double.parseDouble(data[5]), Double.parseDouble(data[6])), Double.parseDouble(data[7]), Boolean.parseBoolean(data[8]));
					break;
				case 10:
					read = new Washer(data[0], data[1], Double.parseDouble(data[2]), EnergyEfficiency.valueOf(data[3]),  new Dimension(Double.parseDouble(data[4]), Double.parseDouble(data[5]), Double.parseDouble(data[6])), Double.parseDouble(data[7]), Double.parseDouble(data[8]), Integer.parseInt(data[9]));
					break;
				}

				if(!result.contains(read)) {
					result.add(read);
				}
				else {
					System.out.println("Duplicated not added:");
					System.out.println(read);
				}
			}
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		try {
			buffer.close();
		} catch (IOException e) {
			e.printStackTrace();
		}

		return result;
	}
}
