package sections_1_to_5.test;

import sections_1_to_5.units.IPhysicalUnit;
import sections_1_to_5.magnitude.exceptions.QuantityException;
import sections_1_to_5.metricSystems.si.length.SiLengthMetricSystem;
import sections_1_to_5.metricSystems.si.time.SiTimeMetricSystem;

public class PhysicalUnitTest {
	public static void main(String[] args) throws QuantityException {
		IPhysicalUnit meter = SiLengthMetricSystem.METER;
		System.out.println(meter);   				// This is how a meter is printed (abrev + Quantity)
		System.out.println(meter.canTransformTo(SiLengthMetricSystem.KILOMETER));   // Yes, we can
		System.out.println(meter.canTransformTo(SiTimeMetricSystem.SECOND));  		// No, we don't
		System.out.println("1000 m in km: "+meter.transformTo(1000, SiLengthMetricSystem.KILOMETER));
		try {
			System.out.println("1000 m in s: "+meter.transformTo(1000, SiTimeMetricSystem.SECOND)); // Exception!
		} catch (QuantityException e) {
			System.out.println(e);
		}
	}
}
