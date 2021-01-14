package section_6.magnitude;

import section_6.magnitude.exceptions.QuantityException;
import section_6.units.physicalUnit.*;

/**
 * These are the functions and variables that define the Magnitude interface.
 *
 */
public interface IMagnitude {
    /**
     * Method that adds two magnitudes.
     * 
     * @param m IMagnitude
     * @return IMagnitude
     * @throws QuantityException
     */
    IMagnitude add(IMagnitude m) throws QuantityException;

    /**
     * Method that subtract two magnitudes.
     * 
     * @param m IMagnitude
     * @return IMagnitude
     * @throws QuantityException
     */
    IMagnitude subs(IMagnitude m) throws QuantityException;

    /**
     * Method that transforms a Physical Unit into a different magnitude.
     * 
     * @param c the physical unit we are going to transform
     * @return IMagnitude
     * @throws QuantityException
     */
    IMagnitude transformTo(IPhysicalUnit c) throws QuantityException;

    /**
     * Unit getter
     * 
     * @return value of the unit
     */
    IPhysicalUnit getUnit();

    /**
     * Value getter.
     * 
     * @return value of the unit
     */
    double getValue();
}
