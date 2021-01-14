package ads.assignment3;
/**
 * This is the class for the Tester 5. It test the CannarySale class and the CurvedTelevision one.
 */
public class Tester5 {
	public static void main(String[] args) {
	    Appliance tv1 = new CurvedTelevision("Loewe", "Art 48 4K Plata", 1699.00,
					EnergyEfficiency.A, 48,new Dimension(60, 65, 201),1500);
	    Appliance tv2 = new Television("LG", "32LF592U", 271.92,
					EnergyEfficiency.C, 32);
	    Appliance wash1 = new Washer("Indesit", "XWE 91483 X", 329.0,
					EnergyEfficiency.A, new Dimension(59.5, 60.5, 85.0), 72, 9.5, 1500);
	    Appliance frigo1 = new Refrigerator("Bosch", "KGN39VW21", 599.0,
					EnergyEfficiency.A, new Dimension(60, 65, 201), 83.0, true);
	    
			
	    Sale[] sales = new Sale[5];
	    sales[0] = new Sale(tv2);
	    sales[1] = new HomeDeliverySale(tv1);
	    /*Sale product with shipping price of Cannary sales*/
	    sales[2] = new CannarySale(wash1); 
	    sales[3] = new HomeDeliverySale(wash1, frigo1);
	    /*Sale product with shipping price of Cannary sales, output should be as in the assignment*/
	    sales[4] = new CannarySale(tv1);
	    for (Sale s : sales) {
	    	System.out.print(s.getTicket());		
	    }
	 }
}

