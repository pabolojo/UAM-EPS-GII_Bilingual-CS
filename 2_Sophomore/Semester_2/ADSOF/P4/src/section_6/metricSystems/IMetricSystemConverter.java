package section_6.metricSystems;

import section_6.magnitude.IMagnitude;
import section_6.units.physicalUnit.IPhysicalUnit;
import section_6.magnitude.exceptions.*;

/**
 * These are the functions and variables that define the MetricSystemConverter
 * interface.
 *
 */
public interface IMetricSystemConverter {

	/**
	 * sourceSystem getter.
	 * 
	 * @return sourceSystem
	 */
	IMetricSystem sourceSystem();

	/**
	 * targetSystem getter.
	 * 
	 * @return targetSystem
	 */
	IMetricSystem targetSystem();

	/**
	 * Method that transforms a Magnitude into a magnitude of a different system.
	 * 
	 * @param from IMagnitude that we want to transform.
	 * @param to   IPhysicalUnit in which we want our Magnitude to be at the end.
	 * @return mag IMagnitude.
	 * @throws UnknownUnitException if the metric systems do not have a converter or
	 *                              there is a Quantity Exception.
	 */
	IMagnitude transformTo(IMagnitude from, IPhysicalUnit to) throws UnknownUnitException;

	/**
	 * Function that modifies the actual converter to return a converter that goes
	 * from the target to source.
	 * 
	 * @return reverse IMetricSystemConverter
	 */
	IMetricSystemConverter reverse();
}
