package part6.ads.assignment3;
/**
* These are the functions and variables that define the Dimension methods, the Dimension class.
*
*/
public class Dimension{
	private double dim[];
    
    /**
     * Constructor for this class.
     *
     * @param x x dimension of the appliance
     * @param y y dimension of the appliance
     * @param z z dimension of the appliance
     */
    public Dimension(double x, double y, double z){
        dim = new double[]{x, y, z};
    }
    
    /**
     * X,Y and Z dimensions getter.
     * @return Dimension array with the three dimension parameters.
     */
    public double[] getDims(){
        return dim;
    }
}

