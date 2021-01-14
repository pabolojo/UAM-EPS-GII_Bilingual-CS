package part6.ads.assignment3;

import java.util.Locale;
import java.util.*;
/**
 * These are the functions and variables that define the Sale objects, the Sale class.
 */
public class Sale{

	private Appliance returned;
	private Appliance bought;
	private double price;
	private static Stack<Sale> saleStack = new Stack<Sale>();

	/**
	 * Constructor of this class if the customer returns an appliance.
	 *
	 * @param returned Appliance that is bought.
	 * @param bought Appliance that is returned.
	 */
	public Sale(Appliance bought, Appliance returned){
		this(bought);
		this.returned = returned;
		price -= discount(bought.getEfficiency(), returned.getEfficiency());
		
	}

	/**
	 * Constructor of this class.
	 *
	 * @param bought Appliance that is bought.
	 */
	public Sale(Appliance bought){

		this.bought = bought;
		price = bought.getBasePrice();
		saleStack.push(this);
		StockManagement s = StockManagement.getStockManagement();
		if(s.removeUnit(bought)==false) {
			System.out.println("Sale to be done when we recieve appliances in the stock");
		}
	}

	/**
	 * Constructor of this class if the customer returns an appliance and has an extra shipping.
	 *
	 * @param returned Appliance that is bought.
	 * @param bought Appliance that is returned.
	 * @param shipping price added for the home delivery
	 */
	public Sale(Appliance bought , Appliance returned, double shipping){
		this(bought, shipping);
		this.returned = returned;

		price -= discount(bought.getEfficiency(), returned.getEfficiency());
	}

	/**
	 * Constructor of this class if it has an extra shipping.
	 *
	 * @param bought Appliance that is bought.
	 * @param shipping price added for the home delivery
	 */
	public Sale(Appliance bought, double shipping){

		this.bought = bought;
		price = bought.getBasePrice()+shipping;
		saleStack.push(this);
		StockManagement s = StockManagement.getStockManagement();
		if(s.removeUnit(bought)==false) {
			System.out.println("Sale to be done when we recieve appliances in the stock");
		}
	} 

	/**
	 * Bought appliance getter.
	 * @return returned.
	 */
	public Appliance getNewAppliance(){ 
		return this.bought;
	}

	/**
	 * Value price getter.
	 * @return price value.
	 */
	public double getPrice(){ 
		return price; 
	}

	/**
	 * Function that returns the ticket of a sale with information about the prices and discounts.
	 * @return Ticket string.
	 */
	public String getTicket(){    

		return "--------------------------------------------\n" +
			   soldProduct() +
			   "\n--------------------------------------------\n" +
			   bPrice() +
			   shippingDiscount() +
			   total(this.price);
	}

	/**
	 * Function that returns a string with information about an appliance.
	 * @return Sold product string.
	 */
	protected String soldProduct(){
		return "Sold product: " + bought;
	}

	/**
	 * Function that returns a string with information about the base price.
	 * @return Base price string.
	 */
	protected String bPrice(){
		return "Product price: " + String.format(Locale.ROOT, "%17.2f", bought.getBasePrice()) + " Euros\n";
	}

	/**
	 * Function that returns a string with information about the discount of a product.
	 * @return Shipping discount string.
	 */
	protected String shippingDiscount(){
		double discount;

		if(returned != null){
			discount = discount(bought.getEfficiency(), returned.getEfficiency());
		}
		else{
			discount = 0.00;
		}
		return "Shipping discount: " + String.format(Locale.ROOT, "%13.2f",discount) + " Euros\n";
	}

	/**
	 * Function that returns a string with information about the total price of a product.
	 * @return Total price string.
	 */
	protected static String total(double price){

		return "TOTAL: " + String.format(Locale.ROOT, "%25.2f", price) + " Euros\n";
	}
	
	/**
	 * Calculation of the discount considering the energy efficiency
	 * @param newer energy efficiency of the appliance that the client has bought.
	 * @param old energy efficiency of the appliance that the client has returned.
	 * @return the discount that is going to be applied.
	 */   
	private static double discount(EnergyEfficiency newer, EnergyEfficiency old){

		if(old == newer){
			return 25;
		}else if(old == EnergyEfficiency.UNKNOWN){
			return 10;
		}else if(old.ordinal()>newer.ordinal()){
			return 25 + 15*(old.ordinal() - newer.ordinal());
		}else if(old.ordinal()<newer.ordinal()){
			return 25 - 5*(newer.ordinal()-old.ordinal());
		}
		return 0.00;
	}
	
	/**
	 * Function that returns a string with the summary of all sales .
	 * @return Sales summary string.
	 */
	public static String salesSummary(){

		String summary = "\nSALES SUMMARY\n";
		for(Sale s:saleStack ) {  		
			summary=summary.concat(total(s.price));
		}

		return summary;
	}
	
	/**
	 * Function that returns a string with the summary of all sales that are greater than the minimum parameter.
	 * @param minimum price limit.
	 * @return Sales summary string.
	 */
	public static String salesSummary(double minimum){

		String summary= "\nSALES SUMMARY\n";

		for(Sale s:saleStack ) {
			if(s.price>minimum) {
				summary=summary.concat(total(s.price));
			}
		}
		return summary;
	}
	
	/**
	 * Function that returns a string with the summary of all sales that are from a required brand.
	 * @param brand required.
	 * @return Sales summary string.
	 */
	public static String salesSummary(String brand){

		Appliance a;
		String summary= "\nSALES SUMMARY\n";
		for(Sale s:saleStack ) {
			a=s.getNewAppliance();
			if(a.getBrand().contains(brand)) {
				summary=summary.concat(total(s.price));
			}
		}
		return summary;
	}
	
	/**
	 * Function that deletes the last sale done.
	 * @return Last done sale.
	 */
	public static Sale cancel(){
		Sale s;
		StockManagement stock = StockManagement.getStockManagement();
		if(saleStack.empty()){
			return null;
		}
		s=saleStack.pop();
		Appliance a = s.getNewAppliance();
		stock.addUnit(a);
		return s;
	}
	
	/**
	 * Function that shows without deleting the last sale done.
	 * @return Last done sale.
	 */
	public static Sale last(){
		return saleStack.peek();
	}
}

