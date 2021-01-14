package section_6.units.physicalUnit;

import section_6.metricSystems.IMetricSystem;
import section_6.units.AbstractUnit;
import section_6.magnitude.quantity.*;
/**
 * These are the functions and variables that define the PhysicalUnit class. It
 * implements the interface IPhysicalUnit.
 * 
 */
public abstract class PhysicalUnit extends AbstractUnit implements IPhysicalUnit {

    protected Quantity quant;

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

        super(abbrev, value, metricSystem);

        this.quant = q;
    }

    /**
     * Quantity class getter.
     * 
     * @return quant
     */
    @Override
    public Quantity getQuantity() {
        return quant;
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
