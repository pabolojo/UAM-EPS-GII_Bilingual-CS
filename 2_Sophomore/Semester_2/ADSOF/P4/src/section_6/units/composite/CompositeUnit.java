package section_6.units.composite;

import section_6.magnitude.Magnitude;
import section_6.magnitude.quantity.*;
import section_6.magnitude.exceptions.QuantityException;
import section_6.units.AbstractUnit;
import section_6.units.composite.operator.Operator;
import section_6.units.physicalUnit.IPhysicalUnit;
import section_6.units.physicalUnit.PhysicalUnit;

/**
 * These are the functions and variables that define the CompositeUnit class. It
 * implements the interface ICompositeUnit and extends AbstractUnit
 * 
 */
public class CompositeUnit extends AbstractUnit implements ICompositeUnit {

    private IPhysicalUnit left;
    private Operator operator;
    private IPhysicalUnit right;
    private CompositeQuantity cquant;

    /**
     * Constructor of this class.
     * 
     * @param left  value of the left physical unit
     * @param op    value of the operator
     * @param right value of the left physical unit
     */
    public CompositeUnit(PhysicalUnit left, Operator op, PhysicalUnit right) {
        super(left.abbrev() + " " + op.getOperator() + " " + right.abbrev(),
                op.getOperator().equals("*") ? left.getValue() * right.getValue() : left.getValue() / right.getValue(),
                left.getMetricSystem());

        this.cquant = new CompositeQuantity(left.getQuantity(), op, right.getQuantity());
        this.left = left;
        this.operator = op;
        this.right = right;
    }

    /**
     * Operator getter.
     * 
     * @return operator
     */
    @Override
    public Operator getOperator() {
        return this.operator;
    }

    /**
     * Left IPhysicalUnit getter.
     * 
     * @return right
     */
    @Override
    public IPhysicalUnit getLeftUnit() {
        return this.left;
    }

    /**
     * Right IPhysicalUnit getter.
     * 
     * @return right
     */
    @Override
    public IPhysicalUnit getRightUnit() {
        return this.right;
    }

    /**
     * Quantity class getter.
     * 
     * @return cquant
     */
    @Override
    public Quantity getQuantity() {
        return this.cquant;
    }

    /**
     * Method that indicates if a composite unit can be transformed into other one
     * 
     * @param u
     * @return boolean true if a physical unit can be transformed into other one;
     *         false otherwise
     */
    @Override
    public boolean canTransformTo(IPhysicalUnit u) {
        if (this.cquant.equals(u.getQuantity())) {
            return true;
        }
        return false;
    }

    /**
     * Method that transforms the value of some composite unit to a different one.
     * 
     * @param d the value of the unit
     * @param u the physical unit we want to transform to
     * @return double the result
     * @throws QuantityException
     */
    @Override
    public double transformTo(double d, IPhysicalUnit u) throws QuantityException {
        if (!this.canTransformTo(u)) {
            throw new QuantityException(u.getQuantity(), this.getQuantity());
        }
        Magnitude l = new Magnitude(d, this.left);
        Magnitude r = new Magnitude(1, this.right);
        CompositeUnit c = (CompositeUnit) u;

        double l_value = l.transformTo(c.left).getValue();
        double r_value = r.transformTo(c.right).getValue();

        if (this.operator.getOperator().equals("*")) {
            return l_value * r_value;
        }
        return l_value / r_value;
    }

}
