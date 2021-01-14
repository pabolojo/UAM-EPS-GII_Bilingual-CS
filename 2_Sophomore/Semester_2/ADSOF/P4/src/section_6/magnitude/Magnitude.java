package section_6.magnitude;

import section_6.magnitude.IMagnitude;
import section_6.magnitude.exceptions.*;
import section_6.metricSystems.AbstractMetricSystem;
import section_6.units.physicalUnit.*;
import java.util.Locale;

/**
 * These are the functions and variables that define the Magnitude objects, the
 * Magnitude class.
 *
 */
public class Magnitude implements IMagnitude {
    private double value;
    private IPhysicalUnit unit;

    /**
     * Constructor of this class.
     * 
     * @param value
     * @param unit
     */
    public Magnitude(double value, IPhysicalUnit unit) {
        this.value = value;
        this.unit = unit;
    }

    /**
     * Method that adds two magnitudes.
     * 
     * @param m IMagnitude
     * @return IMagnitude
     * @throws QuantityException
     */
    @Override
    public IMagnitude add(IMagnitude m) throws QuantityException {
        this.value += m.getUnit().transformTo(m.getValue(), this.unit);
        return this;
    }

    /**
     * Method that subtract two magnitudes.
     * 
     * @param m IMagnitude
     * @return IMagnitude
     * @throws QuantityException
     */
    @Override
    public IMagnitude subs(IMagnitude m) throws QuantityException {
        this.value -= m.getUnit().transformTo(m.getValue(), this.unit);
        return this;
    }

    /**
     * Method that transforms a Physical Unit into a different magnitude.
     * 
     * @param c the physical unit we are going to transform
     * @return m IMagnitude
     * @throws QuantityException
     */
    @Override
    public IMagnitude transformTo(IPhysicalUnit c) throws QuantityException {
        if (this.unit.getMetricSystem().base().equals(c.getMetricSystem().base())) {
            this.value = this.unit.transformTo(this.value, c);
            this.unit = c;
            return this;
        }
        if (AbstractMetricSystem.getConverter() == null) {
            throw new UnknownUnitException(this.unit, c);
        }
        return AbstractMetricSystem.getConverter().transformTo(this, c);
    }

    /**
     * Unit getter
     * 
     * @return value of the unit
     */
    @Override
    public IPhysicalUnit getUnit() {
        return this.unit;
    }

    /**
     * Value getter.
     * 
     * @return value of the unit
     */
    @Override
    public double getValue() {
        return this.value;
    }

    /**
     * This method outputs the error string
     * 
     * @return String containing all the information of the magnitude.
     */
    @Override
    public String toString() {
        return String.format(Locale.ROOT, "%f [", this.value) + this.unit + "]";
    }

    /**
     * Value setter.
     * 
     * @param value of the unit
     */
    public void setValue(double value) {
        this.value = value;
    }

    /**
     * Unit setter.
     * 
     * @param unit IPhysicalUnit of the unit
     */
    public void setUnit(IPhysicalUnit unit) {
        this.unit = unit;
    }
}
