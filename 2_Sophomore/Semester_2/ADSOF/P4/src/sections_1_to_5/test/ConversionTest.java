package sections_1_to_5.test;

import sections_1_to_5.magnitude.IMagnitude;
import sections_1_to_5.magnitude.Magnitude;
import sections_1_to_5.magnitude.exceptions.QuantityException;
import sections_1_to_5.metricSystems.imperial.length.ImperialLengthMetricSystem;
import sections_1_to_5.metricSystems.si.length.SiLengthMetricSystem;
import sections_1_to_5.metricSystems.si.length.converters.SiLength2ImperialConverter;

public class ConversionTest {

	public static void main(String[] args) throws QuantityException {
		Magnitude m = new Magnitude(10, SiLengthMetricSystem.KILOMETER);

		IMagnitude inMiles = null;

		try {
			inMiles = m.transformTo(ImperialLengthMetricSystem.MILE);
		} catch (QuantityException e) {
			System.out.println(e);
		}
		SiLengthMetricSystem.registerConverter(new SiLength2ImperialConverter()); // This register the converter and the
																					// reverse
		inMiles = m.transformTo(ImperialLengthMetricSystem.MILE);

		System.out.println("In miles = " + inMiles);
		System.out.println("In m = " + inMiles.transformTo(SiLengthMetricSystem.METER));
	}

}
