package section_6.metricSystems.si.time;

import section_6.metricSystems.AbstractMetricSystem;
import section_6.units.physicalUnit.types.TimePhysicalUnit;

/**
 * These are the functions and variables that define the SiTimeMetricSystem
 * object, the SiTimeMetricSystem class.
 *
 */
public class SiTimeMetricSystem extends AbstractMetricSystem {
	/**
     * SYSTEM constant
     * */
    public static final SiTimeMetricSystem SYSTEM = new SiTimeMetricSystem(); 
    /**
     * SECOND constant
     * */
    public static TimePhysicalUnit SECOND;
    /**
     * HOUR constant
     * */
    public static TimePhysicalUnit HOUR;
    /**
     * MILLISECOND constant
     * */
    public static TimePhysicalUnit MILLISECOND;
    /**
     * Constructor of this class. It is private so in can be instantiated just from
     * inside the class.
     */
    private SiTimeMetricSystem() {
        super();
        SECOND = new TimePhysicalUnit("s", 1, this);
        HOUR = new TimePhysicalUnit("h", 3600, this);
        MILLISECOND = new TimePhysicalUnit("ms", 0.001, this);
        super.setBaseUnit(SECOND);
        super.addPhysicalUnit(SECOND);
        super.addPhysicalUnit(HOUR);
        super.addPhysicalUnit(MILLISECOND);
    }
}
