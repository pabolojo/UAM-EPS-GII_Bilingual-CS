package section_6.units.composite;

import section_6.units.composite.operator.*;
import section_6.units.physicalUnit.IPhysicalUnit;

/**
 * These are the functions and variables that define the CompositeUnit
 * interface. It extends IPhysicalUnit
 *
 */
public interface ICompositeUnit extends IPhysicalUnit {
    /**
     * Operator getter.
     * 
     * @return operator
     */
    Operator getOperator();

    /**
     * Left IPhysicalUnit getter.
     * 
     * @return right
     */
    IPhysicalUnit getLeftUnit();

    /**
     * Right IPhysicalUnit getter.
     * 
     * @return right
     */
    IPhysicalUnit getRightUnit();
}
