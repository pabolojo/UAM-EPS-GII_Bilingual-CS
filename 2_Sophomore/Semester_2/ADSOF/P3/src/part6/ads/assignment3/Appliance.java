package part6.ads.assignment3;
/**
 * These are the functions and variables that define the Appliance objects, the Appliance class.
 *
 */
public abstract class  Appliance{
	private String brand;
	private String model;
	private double bprice;
	private EnergyEfficiency efficiency;

	/**
	 * Constructor of this class.
	 *
	 * @param brand brand of the appliance.
	 * @param model .model of said appliance
	 * @param price price of the given appliance
	 * @param letter letter assigned to its power efficiency
	 */
	public Appliance(String brand, String model, double price, EnergyEfficiency letter) {
		this.brand = brand;
		this.model = model;
		this.bprice = price;
		this.efficiency = letter;
		StockManagement s = StockManagement.getStockManagement();
		if(s.addProduct(this, 0)==false) {
			System.out.println("Error, appliance already in the store");
		}
	}
	
	/**
	 * Appliance's brand getter.
	 * @return brand.
	 */
	public String getBrand(){
		return brand;
	}
	
	/**
	 * Appliance's model getter.
	 * @return model.
	 */
	private String getModel(){ 
		return model; 
	}
	
	/**
	 * Appliance's base price getter.
	 * @return price.
	 */
	public double getBasePrice(){ 
		return bprice; 
	}
	
	/**
	 * Appliance's efficiency letter getter.
	 * @return efficiency.
	 */
	public EnergyEfficiency getEfficiency(){ 
		return efficiency; 
	}
	
	/**
	 * This method outputs the brand, model and prize in euros as a message in the screen.
	 * @return String containing all the information of the appliance.
	 */
	@Override
	public String toString() {
		return this.brand + " "+ this.model + ", " + this.bprice+ " Euros";
	}
	
	/**
	 * This method sets the value of the shipping price.
	 * @return Shipping price.
	 */
	public double shippingPrice() { 
		return 35;
	}

	/**
	 * This method overrides the default equal method among Appliances.
	 * @param obj. The object to be compared
	 * @return true if both Appliances are equal.
	 */
	@Override
	public boolean equals(Object obj) {

		if (this == obj) {
			return true;
		}
		if (obj == null) {
			return false;
		}
		if (this.getClass() != obj.getClass()) {
			return false;
		}

		Appliance that = (Appliance) obj;
		if(this.brand.equals(that.getBrand()) && this.model.equals(that.getModel())) {
			return true;
		}

		return false;
	}
}

