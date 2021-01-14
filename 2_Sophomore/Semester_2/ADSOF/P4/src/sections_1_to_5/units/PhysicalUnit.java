package sections_1_to_5.units;

import sections_1_to_5.metricSystems.IMetricSystem;
import sections_1_to_5.magnitude.Quantity;

/**
 * These are the functions and variables that define the PhysicalUnit class. It
 * implements the interface IPhysicalUnit.
 * 
 */
public abstract class PhysicalUnit implements IPhysicalUnit {

    private String abbrev;
    private double value;
    private Quantity quant;
    private IMetricSystem metricSystem;

    /**
     * Constructor of this class.
     * 
     * @param abbrev       the abbreviation of the physical unit
     * @param value        value of the unit compared with the base unit of its
     *                     system
     * @param q            the type of quantity
     * @param metricSystem the type of metricSystem
     */
    public PhysicalUnit(String abbrev, double value, Quantity q, IMetricSystem metricSystem) {
        this.abbrev = abbrev;
        this.value = value;
        this.quant = q;
        this.metricSystem = metricSystem;
    }

    /**
     * Enumeration type getter.
     * 
     * @return quant
     */
    @Override
    public Quantity getQuantity() {
        return quant;
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
    @Override
    public String abbrev() {
        return this.abbrev;
    }

    /**
     * This method outputs a string with information about the object.
     * 
     * @return String containing all the information of the object.
     */
    @Override
    public String toString() {
        return abbrev + " " + quant.getLetter();
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
     * Method that indicates if a unit can be transformed into other one
     * 
     * @param u
     * @return boolean true if a physical unit can be transformed into other one;
     *         false otherwise
     */
    @Override
    public boolean canTransformTo(IPhysicalUnit u) {
        if (this.quant.equals(u.getQuantity())) {
            return true;
        }
        return false;
    }
}
