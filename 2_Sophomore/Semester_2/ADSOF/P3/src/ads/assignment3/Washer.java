package ads.assignment3;

import java.lang.Math;
/**
* These are the functions and variables that define the Washer objects, the Washer class.
*
*/
public class  Washer extends Appliance{
	private Dimension dimensions;
	private double load;
	private double weight;
	private int revolutions;

    /**
     * Constructor for a washer whose load and revolutions parameters have been specified.
     *
     * @param brand of the appliance.
     * @param model of the appliance
     * @param bprice price of the given appliance
     * @param energeticp letter assigned to its power efficiency
     * @param dim dimensions of the washer.
     * @param weight of the washer
     * @param load of the washer
     * @param rev max speed which the washer reaches
     */
    public Washer(String brand, String model, double bprice, EnergyEfficiency energeticp, Dimension dim, double weight,double load, int rev) {
		this(brand, model, bprice, energeticp,dim,weight);
	    this.load = load;
	    this.revolutions = rev;
		this.weight = weight;
	}
    
    /**
     * Constructor for a washer whose load and revolutions parameters haven't been specified.
     *
     * @param brand of the appliance.
     * @param model of said appliance
     * @param bprice price of the given appliance
     * @param energeticp letter assigned to its power efficiency
     * @param dim dimensions of the washer.
     * @param weight of the washer
     */
	public Washer(String brand, String model, double bprice, EnergyEfficiency energeticp, Dimension dim, double weight) {
		super(brand, model, bprice, energeticp);
	    this.dimensions = dim;
	}
	
    /**
     * Function that calculates the shipping price of a washer.
     * @return Shipping extra price.
     */
    @Override
    public double shippingPrice() {
    	if(this.weight<=50){
    		return super.shippingPrice();
    	}else{
    		return super.shippingPrice() + (Math.ceil(this.weight-50))/2;
    	}
    }
}
