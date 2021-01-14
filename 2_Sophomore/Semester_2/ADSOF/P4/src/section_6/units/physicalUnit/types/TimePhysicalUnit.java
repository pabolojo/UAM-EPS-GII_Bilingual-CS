package section_6.units.physicalUnit.types;

import section_6.magnitude.exceptions.*;
import section_6.units.physicalUnit.*;
import section_6.metricSystems.IMetricSystem;
import section_6.magnitude.quantity.*;
/**
 * These are the functions and variables that define the TimePhysicalUnit
 * objects, the TimePhysicalUnit class.
 *
 */
public class TimePhysicalUnit extends PhysicalUnit {

    /**
     * Constructor of this class.
     * 
     * @param abbrev       the abbreviation of the physical unit
     * @param value        of the unit compared with the base unit of its system
     * @param metricSystem the type of metricSystem
     */
    public TimePhysicalUnit(String abbrev, double value, IMetricSystem metricSystem) {
        super(abbrev, value, Quantity.TIME, metricSystem);
    }

    /**
     * Method that transforms the value of some unit to a different one.
     * 
     * @param d the value of the unit
     * @param u the physical unit we want to transform to
     * @return double the result
     * @throws QuantityException
     */
    @Override
    public double transformTo(double d, IPhysicalUnit u) throws QuantityException {
        double transform;
        if (!this.canTransformTo(u)) {
            throw new QuantityException(super.getQuantity(), u.getQuantity());
        }

        TimePhysicalUnit t = (TimePhysicalUnit) u;

        if (super.getValue() < t.getValue()) {
            transform = t.getValue() / super.getValue();
        } else {
            transform = super.getValue() / t.getValue();
        }
        return d / transform;
    }
}
