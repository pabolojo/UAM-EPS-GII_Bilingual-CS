package section_6.metricSystems.imperial.length;

import section_6.metricSystems.*;
import section_6.units.physicalUnit.types.*;

/**
 * These are the functions and variables that define the
 * ImperialLengthMetricSystem object, the ImperialLengthMetricSystem class.
 *
 */
public class ImperialLengthMetricSystem extends AbstractMetricSystem {
	/**
     * SYSTEM constant
     * */
	public static final ImperialLengthMetricSystem SYSTEM = new ImperialLengthMetricSystem();
	/**
     * INCH constant
     * */
	public static LengthPhysicalUnit INCH;
	/**
     * FOOT constant
     * */
	public static LengthPhysicalUnit FOOT;
	/**
     * YARD constant
     * */
	public static LengthPhysicalUnit YARD;
	/**
     * MILE constant
     * */
	public static LengthPhysicalUnit MILE;

	/**
	 * Constructor of this class. It is private so in can be instantiated just from
	 * inside the class.
	 */
	private ImperialLengthMetricSystem() {
		super();
		INCH = new LengthPhysicalUnit("in", 1 / 12, this);
		FOOT = new LengthPhysicalUnit("ft", 1, this);
		YARD = new LengthPhysicalUnit("yd", 3, this);
		MILE = new LengthPhysicalUnit("ml", 5280, this);
		super.setBaseUnit(FOOT);
		super.addPhysicalUnit(INCH);
		super.addPhysicalUnit(FOOT);
		super.addPhysicalUnit(YARD);
		super.addPhysicalUnit(MILE);
	}
}
