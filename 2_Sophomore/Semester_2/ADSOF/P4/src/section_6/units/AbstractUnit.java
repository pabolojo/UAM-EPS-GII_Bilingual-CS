package section_6.units;

import section_6.metricSystems.IMetricSystem;
/**
 * These are the functions and variables that define the AbstractUnit class. 
 * 
 */
public abstract class AbstractUnit {

    protected String abbrev;
    protected double value;
    protected IMetricSystem metricSystem;

    /**
     * Constructor of this class.
     * 
     * @param abbrev       the abbreviation of the physical unit
     * @param value        value of the unit compared with the base unit of its
     *                     system
     * @param metricSystem the type of metricSystem
     */
    public AbstractUnit(String abbrev, double value, IMetricSystem metricSystem) {
        this.abbrev = abbrev;
        this.value = value;
        this.metricSystem = metricSystem;

    }

    /**
     * Metric System type getter.
     * 
     * @return metricSystem
     */
    public IMetricSystem getMetricSystem() {
        return metricSystem;
    }

    /**
     * Abbreviation of a physical unit getter.
     * 
     * @return abbrev
     */

    public String abbrev() {
        return this.abbrev;
    }

    /**
     * Value getter.
     * 
     * @return value
     */
    public double getValue() {
        return value;
    }

    /**
     * This method outputs a string with information about the object.
     * 
     * @return String containing all the information of the object.
     */
    @Override
    public String toString() {
        return abbrev;
    }
}

