package ads.assignment3;

import java.lang.Math;

/**
* These are the functions and variables that define the Refrigerator objects, the Refrigerator class.
*
*/
public class Refrigerator extends Appliance {
    private Dimension dimensions;
    private boolean noFrost;
    private double weight;

    /**
     * Constructor of this class.
     *
     * @param brand
     * @param model
     * @param bprice
     * @param energeticp
     * @param dim
     * @param weight
     * @param noFrost
     */
    public Refrigerator(String brand, String model, double bprice, EnergyEfficiency energeticp, Dimension dim, double weight, boolean noFrost) {
        super(brand,model,bprice,energeticp);
        this.weight=weight;
        this.dimensions = dim;
        this.noFrost= noFrost;
    }  
    
    /**
     * Function that calculates the shipping price of a refrigerator.
     * @return Shipping extra price.
     */
    @Override
    public double shippingPrice(){
       double [] dim = dimensions.getDims();

       return Math.round(((dim[0]*dim[1]*dim[2])/1000000)*70);
    }

}

