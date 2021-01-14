package ads.p2.billing;
/**
* These are the functions and variables that define the Food objects, the Food class.
*
*/
public class Food extends Article {
	private boolean promo3x2;
/**
     * Constructor of this class
     *
     * @param id identifier.
     * @param desc description.
     * @param price The units price.
     * @param promo The promotion for which is eligible
     */
	public Food(long id, String desc, double price, boolean promo) {
		super(id, desc, price);
		promo3x2 = promo;
	}
	/**
    * Promotion getter.
    * @return promotion.
    */
	public boolean getPromo3x2() { return promo3x2; }
	/**
    * Promotion setter.
    * @param promo The promotion that will be applied.
    */
	public void setPromo3x2(boolean promo) { promo3x2 = promo; }
	/**
    * Defines the public VAT.
    * @return TThe calculated VAT.
    */
	public double typeVAT() { return 0.10; }
	/**
    * Calculates the corresponding discount.
    * @param units The amount of articles of the same kind that will recieve the discount.
    */
	public double discount(double units) {
		if (promo3x2) return getUnitPrice() * (int) (units / 3);
		else return 0.0;
	}
}
