package ads.assignment3;

/**
* These are the functions and variables that define the CurvedTelevision objects, the CurvedTelevision class.
*/
public class CurvedTelevision extends Television{
	private Dimension dimensions;
	private double weight;

	/**
     * Constructor of this class.
     *
     * @param brand .
     * @param model .
     * @param bprice
     * @param energeticp
     * @param screen
     * @param dim
     * @param weight
     */
    public CurvedTelevision(String brand, String model, double bprice, EnergyEfficiency energeticp, double screen, Dimension dim, double weight) {
        super(brand, model, bprice, energeticp, screen);      
    	this.weight = weight;
    	this.dimensions = dim;
    }
    
    /**
     * Function that calculates the shipping price of a television.
     * @return Shipping extra price.
     */
    @Override
    public double shippingPrice(){
    	double [] dim = dimensions.getDims();

    	return super.shippingPrice()+((dim[0]*dim[1]*dim[2])/1000000)*25;
    }
}

