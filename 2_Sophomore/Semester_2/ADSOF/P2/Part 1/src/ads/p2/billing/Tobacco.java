package ads.p2.billing;
/**
* These are the functions and variables that define the Tobacco objects, the Tobacco class.
*
*/
public class Tobacco extends Article {
	/**
     * Constructor of this class
     *
     * @param id identifier.
     * @param desc description.
     * @param price The units price.
     */
	public Tobacco(long id, String desc, double price) {
		super(id, desc, price);
	}
	/**
    * Calculates the corresponding discount.
    * @param units The amount of articles of the same kind that will recieve the discount.
    * @return 0.
    */
	public double discount(double units) {
    return 0.0;
	}
}
