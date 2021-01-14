package sections_1_to_5.magnitude;
/**
* These are the values which the Quantity can take, the Quantity enum. 
*
*/
public enum  Quantity {
    LENGTH("L"),
    TIME("t");

    private String letter;

    /**
     * Constructor of this enumeration
     * @param letter
     */
    private Quantity(String letter){
        this.letter = letter;
    }
    
    /**
     * Letter getter
     * @return letter the character that abbreviates each type of quantity
     */
    public String getLetter(){
        return this.letter;
    }

}
