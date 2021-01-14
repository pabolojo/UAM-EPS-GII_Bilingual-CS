package ads.p2.billing;

/**
* These are the functions and variables that define the Article objects, the Article class.
*
*/

public abstract class Article {
	private long identifier;
	private String description;
	private double unitPrice;

	/**
     * Constructor of this class
     *
     * @param id identifier.
     * @param desc description.
     * @param price The units price.
     */

	public Article(long id, String desc, double price) {
		identifier = id;
		description = desc;
		unitPrice = price;
	}
	/**
    * Identifier getter.
    * @return identifier.
    */
	public long getIdentifier() { return identifier; }
	/**
    * Description getter.
    * @return description.
    */
	public String getDescription() { return description; }
	/**
    * Unit's Price getter.
    * @return The unit's price.
    */
	public double getUnitPrice() { return unitPrice; }
	/**
    * Description setter.
    * @param desc The description we are going to add.
    */
	public void setDescription(String desc) { description = desc; }
	/**
    * Description setter.
    * @param price The price we are going to set.
    */
	public void setUnitPrice(double price) { unitPrice = price; }
	/**
    * Defines the public VAT.
    * @return TThe calculated VAT.
    */
	public double typeVAT() { return 0.21; }
	/**
    * Calculates the corresponding discount.
    * @param units The amount of articles of the same kind that will recieve the discount.
    */
	public abstract double discount(double units);
	/**
    * Calculates the corresponding discount.
    * @param units The amount of articles of the same kind from which you want to calculate their combined price.
    */
	public double totalPrice(double units) {
		return ((unitPrice * units) - discount(units))
                     * (1.0 + typeVAT());
	}

	/**
    * Outputs all of the information of the class.
    * @return Prints the id, the description and the unit price.
    */
  	public String toString(){
		return "Id: "+ identifier + " " + description + " Price: " + unitPrice;
	}
}
