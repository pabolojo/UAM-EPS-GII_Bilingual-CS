package ads.assignment3;

import java.util.Locale;
/**
 * These are the functions and variables that define the HomeDeliverySale objects, the HomeDeliverySale class.
 */
public class HomeDeliverySale extends Sale{
	protected double shipping;
	
	/**
	 * Constructor of this class if the customer returns another appliance.
	 *
	 * @param bought Appliance that is bought.
	 * @param returned Appliance that is returned.
	 */
	public HomeDeliverySale(Appliance bought, Appliance returned){
		super(bought, returned, bought.shippingPrice());
		shipping = bought.shippingPrice();
	}
	
	/**
	 * Constructor of this class if the customer just buys a new appliance.
	 *
	 * @param bought Appliance that is bought.
	 */
	public HomeDeliverySale(Appliance bought){
		super(bought, bought.shippingPrice());
		shipping = bought.shippingPrice();
	}
	
	/**
	 * Constructor of this class if the customer just buy a new appliance and has a different shipping.
	 *
	 * @param bought Appliance that is bought.
	 * @param shipping the extra shipping price.
	 */
	public HomeDeliverySale(Appliance bought, double shipping){
		super(bought, shipping);
		this.shipping = shipping;
	}
	
	/**
	 * Function that returns the ticket of a sale with information about the prices and discounts.
	 * @return Ticket string.
	 */
	@Override
	public String getTicket(){

		return "--------------------------------------------\n" +
			   super.soldProduct()+
			   "\n--------------------------------------------\n" +
			   super.bPrice()+
			   super.shippingDiscount()+
		       "Shipping cost: " + String.format(Locale.ROOT,"%17.2f",this.shipping) + " Euros\n"+
			   super.total(super.getPrice());
	}
}
