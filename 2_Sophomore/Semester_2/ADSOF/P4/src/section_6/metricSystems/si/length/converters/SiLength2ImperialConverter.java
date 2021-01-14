package section_6.metricSystems.si.length.converters;

import section_6.metricSystems.MetricSystemConverter;
import section_6.metricSystems.imperial.length.ImperialLengthMetricSystem;
import section_6.metricSystems.si.length.SiLengthMetricSystem;

/**
 * These are the functions and variables that define the
 * SiLength2ImperialConverter objects, the SiLength2ImperialConverter class.
 *
 */
public class SiLength2ImperialConverter extends MetricSystemConverter {

	/**
	 * Constructor of this class. 
	 */
	public SiLength2ImperialConverter() {
		super(SiLengthMetricSystem.SYSTEM, ImperialLengthMetricSystem.SYSTEM, 3.280839895);
	}

}

