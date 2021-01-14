package part6.ads.assignment3;

/**
* These are the functions and variables that define the Television objects, the Television class.
*/
public class Television extends Appliance{
    private double screen;
    
    /**
     * Constructor of this class.
     *
     * @param brand 
     * @param model 
     * @param bprice
     * @param energeticp
     * @param screen
     */
    public Television(String brand, String model, double bprice, EnergyEfficiency energeticp, double screen) {
        super(brand, model, bprice, energeticp);
        this.screen=screen;
    }
    
    /**
     * Function that calculates the shipping price of a television.
     * @return Shipping extra price.
     */
    @Override
    public double shippingPrice(){
    	if(this.screen<=40 && super.getBasePrice()>500){
    		return 0.0;
    	}else if(this.screen<=40 && super.getBasePrice()<500){
    		return super.shippingPrice();
    	}else{
    		return super.shippingPrice() + (this.screen-40);
    	}
    }

}

