package section_6.magnitude.quantity;

/**
 * These are the functions and variables that define the Quantity class, the
 * Quantity objects.
 *
 */
public class Quantity {
    public static final Quantity LENGTH = new Quantity("L");
    public static final Quantity TIME = new Quantity("t");

    private String letter;

    /**
     * Constructor of this class
     * 
     * @param letter
     */
    public Quantity(String letter) {
        this.letter = letter;
    }

    /**
     * Letter getter
     * 
     * @return letter the character that abbreviates each type of quantity
     */
    public String getLetter() {
        return this.letter;
    }

    /**
     * This method overrides the default equal method among Quantities.
     * 
     * @param obj. The object to be compared
     * @return true if both Quantities are equal.
     */
    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }
        if (!(obj instanceof Quantity)) {
            return false;
        }
        Quantity that = (Quantity) obj;
        if (!this.letter.contentEquals(that.getLetter())) {
            return false;
        }
        return true;
    }

}
