package section_6.magnitude.exceptions;

import section_6.magnitude.exceptions.QuantityException;
import section_6.units.physicalUnit.IPhysicalUnit;

/**
 * These are the functions and variables that define the UnknownUnitException
 * methods, the UnknownUnitException class.
 *
 */
public class UnknownUnitException extends QuantityException {

	private static final long serialVersionUID = 1L;

	/**
     * Constructor for this class.
     * 
     * @param u1 the first physical unit
     * @param u2 the second physical unit
     */
    public UnknownUnitException(IPhysicalUnit u1, IPhysicalUnit u2) {
        super("Cannot transform " + u1 + " to " + u2);

    }
}

