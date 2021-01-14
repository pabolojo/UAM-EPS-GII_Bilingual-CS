package section_6.units.physicalUnit;

import section_6.magnitude.exceptions.*;
import section_6.metricSystems.IMetricSystem;
import section_6.magnitude.quantity.*;
/**
 * These are the functions and variables that define the PhysicalUnit interface.
 *
 */
public interface IPhysicalUnit {
    /**
     * Method that indicates if a unit can be transformed into other one
     * 
     * @param u
     * @return boolean true if a physical unit can be transformed into other one;
     *         false otherwise
     */
    boolean canTransformTo(IPhysicalUnit u);

    /**
     * Method that transforms the value of some unit to a different one.
     * 
     * @param d the value of the unit
     * @param u the physical unit we want to transform to
     * @return double the result
     * @throws QuantityException
     */
    double transformTo(double d, IPhysicalUnit u) throws QuantityException;

    /**
     * Enumeration type getter.
     * 
     * @return Quantity
     */
    Quantity getQuantity();

    /**
     * Abbreviation of a physical unit getter.
     * 
     * @return String
     */
    String abbrev();

    /**
     * Getter of the metric system of the physical unit.
     * 
     * @return IMetricSystem
     */
    IMetricSystem getMetricSystem();
}
