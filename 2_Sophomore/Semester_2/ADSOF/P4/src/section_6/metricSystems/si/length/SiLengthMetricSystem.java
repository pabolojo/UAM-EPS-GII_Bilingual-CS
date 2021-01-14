package section_6.metricSystems.si.length;

import section_6.units.physicalUnit.types.LengthPhysicalUnit;
import section_6.metricSystems.AbstractMetricSystem;
import section_6.metricSystems.IMetricSystemConverter;

/**
 * These are the functions and variables that define the SiLengthMetricSystem
 * object, the SiLengthMetricSystem class.
 *
 */
public class SiLengthMetricSystem extends AbstractMetricSystem {
	
	/**
     * SYSTEM constant
     * */
	public static final SiLengthMetricSystem SYSTEM = new SiLengthMetricSystem();
	/**
     * METER constant
     * */
	public static LengthPhysicalUnit METER;
	/**
     * KILOMETER constant
     * */
	public static LengthPhysicalUnit KILOMETER;
	/**
     * MILLIMETER constant
     * */
	public static LengthPhysicalUnit MILLIMETER;

	/**
	 * Constructor of this class. It is private so in can be instantiated just from
	 * inside the class.
	 */
	private SiLengthMetricSystem() {
		super();
		METER = new LengthPhysicalUnit("m", 1, this);
		KILOMETER = new LengthPhysicalUnit("km", 1000, this);
		MILLIMETER = new LengthPhysicalUnit("mm", 0.001, this);
		super.setBaseUnit(METER);
		super.addPhysicalUnit(KILOMETER);
		super.addPhysicalUnit(METER);
		super.addPhysicalUnit(MILLIMETER);
	}

	/**
	 * This function sets a converter for the SiLengthMetricSystem.
	 * 
	 * @param conver IMetricSystemConverter object.
	 */
	public static void registerConverter(IMetricSystemConverter conver) {
		AbstractMetricSystem.converter = conver;
	}
}
