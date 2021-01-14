package section_6.magnitude.quantity;

import section_6.units.composite.operator.Operator;

/**
 * These are the functions and variables that define the CompositeQuantity
 * class, the CompositeQuantity objects.
 *
 */
public class CompositeQuantity extends Quantity {

	private Quantity left;
	private Quantity right;
	private Operator operator;

	/**
	 * Constructor of this class.
	 * 
	 * @param left  value of the left quantity
	 * @param op    value of the operator
	 * @param right value of the left quantity
	 */
	public CompositeQuantity(Quantity left, Operator op, Quantity right) {
		super(left.getLetter() + op.getOperator() + right.getLetter());
		this.left = left;
		this.operator = op;
		this.right = right;

	}

	/**
	 * Operator getter
	 * 
	 * @return operator the operator of the quantity
	 */
	public Operator getOperator() {
		return this.operator;
	}

	/**
	 * Quantity getter
	 * 
	 * @return Quantity the characters that abbreviates each type of quantity
	 */
	public String getQuantity() {
		return this.left + " " + this.operator + " " + this.right;
	}

	/**
	 * This method overrides the default equal method among Composite Quantities.
	 * 
	 * @param obj. The object to be compared
	 * @return true if both Composite Quantities are equal.
	 */
	@Override
	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}
		if (!(obj instanceof CompositeQuantity)) {
			return false;
		}
		CompositeQuantity that = (CompositeQuantity) obj;
		if (!this.right.equals(that.right)) {
			return false;
		} else if (!this.left.equals(that.left)) {
			return false;
		} else if (!this.operator.equals(that.operator)) {
			return false;
		}
		return true;
	}

}

