package sections_1_to_5.magnitude.exceptions;

import sections_1_to_5.magnitude.*;

/**
 * These are the functions and variables that define the QuantityException
 * methods, the QuantityException class.
 *
 */
public class QuantityException extends Exception {

	private static final long serialVersionUID = 1L;
	private String error;

    /**
     * Constructor for this class.
     * 
     * @param q1 the first quantity enum type
     * @param q2 the second quantity enum type
     */
    public QuantityException(Quantity q1, Quantity q2) {
        this.error = "Quantities " + q1.getLetter() + " and " + q2.getLetter() + " are not compatible";
    }
    /**
     * Error string setter.
     * @param error
     */
    public QuantityException(String error) {
        this.error = error;
    }

    /**
     * This method outputs the error string
     * 
     * @return String containing all the information of the error.
     */
    @Override
    public String toString() {
        return error;
    }
}
