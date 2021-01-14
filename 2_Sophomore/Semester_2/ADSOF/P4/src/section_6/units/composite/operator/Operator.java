package section_6.units.composite.operator;

/**
 * These are the functions and variables that define the Operator enumeration
 *
 */
public enum Operator {
    MUL("*"), DIV("/");

    private String operator;

    /**
     * Constructor of this enumeration
     * 
     * @param operator
     */
    private Operator(String operator) {
        this.operator = operator;
    }

    /**
     * Letter getter
     * 
     * @return letter the character that abbreviates each type of quantity
     */
    public String getOperator() {
        return this.operator;
    }
}
